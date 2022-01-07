#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#define MAX_CONNECT_CLIENTS 255


struct client_info {
    pthread_t tid;
    int id;
    int fd;
    struct sockaddr_in addr;
};

int curr_max_client_id = 0;
struct client_info *connected_clients;

int get_client_list_s(char *s, int client_id) {
    int p = 0;
    memcpy(s, "  ID IP address      Port\n", 26);
    p += 26;
    for (int i = 0; i < curr_max_client_id; i++) {
        if (connected_clients[i].id == 0) {
            continue;
        }
        if (connected_clients[i].id == client_id) {
            s[p++] = '*';
        } else {
            s[p++] = ' ';
        }
        p += sprintf(s + p, "%3d", connected_clients[i].id) ;
        //如果成功，则返回写入的字符总数，不包括字符串追加在字符串末尾的空字符。如果失败，则返回一个负数。
        p += sprintf( s+p, " ");
        char str[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &connected_clients[i].addr.sin_addr, str, INET_ADDRSTRLEN) == NULL) {
            printf("failed\n");
            return -1 ;
        }
        printf("client %d IP address = %s\n", i+1, str);
        printf("port = %05hu\n",  connected_clients[i].addr.sin_port);
        p += sprintf(s + p, "%s", str);//sprintf()会自动在字符串的尾部补充'\0'，如果目标长度和原长度相等，就会导致越界
        p += sprintf(s + p, "%7hu\n",  connected_clients[i].addr.sin_port );
    }
    return p;
}

void *process_client(void *args) {
    int index = *(int *) args;
    struct client_info info = connected_clients[index];

    int len;
    char buf[65536];
    memset(buf, 0, sizeof(buf));

    // tell client that connection is established and its id
    buf[0] = 0;
    buf[1] = 21;
    buf[2] = info.id;
    send(info.fd, buf, 3, 0);

    while (1) {
        memset(buf, 0, sizeof(buf));
        read(info.fd, buf, 2);

        // check package
        buf[0] = 0;
        if (buf[1] == 1) { // close connection
            if (send(info.fd, buf, 2, 0) != -1)
                printf("Client %d closed the connection\n", info.id);
            break;
        } else if (buf[1] == 2) { // time
            printf("Client %d requests time\n", info.id);
            time_t curr_time = time(NULL);
            buf[2] = strftime(buf + 3, sizeof(buf) - 3, "%c", gmtime(&curr_time));
            if (send(info.fd, buf, buf[2] + 3, 0) != -1 )
                printf("successfully sent time \n");
        } else if (buf[1] == 3) { // server name
            printf("Client %d requests name\n", info.id);
            gethostname(buf + 4, sizeof(buf) - 4);
            short hostname_len = strlen(buf + 4);
            memcpy(buf + 2, &hostname_len, 2);
            if(send(info.fd, buf, hostname_len + 4,0) != -1 )
                printf("successfully sent name \n");
        } else if (buf[1] == 4) { // client list
            printf("Client %d requests client list\n", info.id);
            short list_len = get_client_list_s(buf + 4, info.id);
            if( list_len == -1){
                printf("error in get get_client_list_s");
            }
            else{
                memcpy(buf + 2, &list_len, 2);
                if( send(info.fd, buf, list_len + 4,0) != -1 )
                    printf("successfully sent client list\n");
            }

        } else if (buf[1] == 5) { // send msg to client
            read(info.fd, buf + 2, 1);
            int dst_id = buf[2];
            printf("Client %d wants to send message to %d\n", info.id, dst_id);
            if (dst_id < 0 || dst_id >= MAX_CONNECT_CLIENTS || connected_clients[dst_id - 1].fd == 0) {
                buf[3] = -1;
                send(info.fd, buf, 4,0);
            } else {
                read(info.fd, buf + 3, 2);
                short msg_len;
                memcpy(&msg_len, buf + 3, 2);
                read(info.fd, buf + 5, msg_len);                
                // to dst client
                buf[1] = 6;
                buf[2] = info.id;
                len = send(connected_clients[dst_id - 1].fd, buf, msg_len + 5, 0);
                // to src client
                buf[1] = 5;
                buf[2] = dst_id;
                buf[3] = len < 0 ? -1 : 0;
                if (len < 0)
                    printf("send to dst  failed!\n ");
                else
                    printf("successfully sent to destination client\n ");
                if (send(info.fd, buf, 4, 0) != -1 )
                    printf("notified source client\n ");
            }
        }
    }

    connected_clients[index].id = 0;
    close(info.fd);

    return NULL;
}

void *listen_new_client(void *args) {
    int server_fd = *(int *) args;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd == -1) {
            fprintf(stderr, "Failed to call 'accept'\n");
            break;
        }

        int id = -1;
        for (int i = 0; i < MAX_CONNECT_CLIENTS; i++) {
            if (connected_clients[i].id == 0) {
                id = i;
                connected_clients[i].tid = 0;
                connected_clients[i].id = i + 1;
                connected_clients[i].fd = client_fd;
                connected_clients[i].addr = client_addr;
                if (i + 1 > curr_max_client_id) {
                    curr_max_client_id = i + 1;
                }
                break;
            }
        }

        printf("Client %d connected to the server\n", connected_clients[id].id);
        pthread_create(&connected_clients[id].tid, NULL, process_client, &id);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to call 'socket'\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;// 置为0.0.0.0
    server_addr.sin_port = htons(3721);
    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Failed to call 'bind'\n");
        close(server_fd);
        return -1;
    }

    connected_clients = (struct client_info *) calloc(MAX_CONNECT_CLIENTS, sizeof(struct client_info));
    if (!connected_clients) {
        fprintf(stderr, "Failed to call 'calloc'\n");
        close(server_fd);
        return -1;
    }
    listen(server_fd, MAX_CONNECT_CLIENTS);

    printf("Server begins to run ... (Enter 'q' to quit)\n");
    pthread_t listen_tid;
    pthread_create(&listen_tid, NULL, listen_new_client, &server_fd);
    
    while (1) {
        char buf[65536];
        fgets(buf, sizeof(buf), stdin);
        if (strcmp(buf, "q\n") == 0) {
            break;
        }
    }

    close(server_fd);

    return 0;
}
