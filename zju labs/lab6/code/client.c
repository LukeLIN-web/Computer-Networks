#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


int connected = 0;
const char *hint[2] = {
    "Menu:\n"
    "0 - connect to server\n"
    "6 - quit\n",
    "Menu:\n"
    "1 - close current connection\n"
    "2 - get server time\n"
    "3 - get server name\n"
    "4 - get client list\n"
    "5 - send message to client\n"
    "6 - quit\n"
};

int server_fd;
int client_id;
pthread_t tid;

struct mqueue_t {
    char queue[256][65536];
    int ql, qr;
} mqueue;

void mqueue_init(struct mqueue_t *q) {
    q->ql = 0;
    q->qr = 0;
}

int mqueue_empty(struct mqueue_t *q) {
    return q->ql == q->qr;
}

char *mqueue_front(struct mqueue_t *q) {
    return q->queue[q->ql];
}

void mqueue_push(struct mqueue_t *q, char *str, int count) {
    memset(q->queue[q->qr], 0, 65536);
    memcpy(q->queue[q->qr], str, count);
    ++q->qr;
    if (q->qr == 256) {
        q->qr = 0;
    }
}

void mqueue_pop(struct mqueue_t *q) {
    ++q->ql;
    if (q->ql == 256) {
        q->ql = 0;
    }
}

void *process_input(void *args) {
    char buf[65536], info[65536];
    int len;
    short len_short;
    // 更新一下发包时间.

    while (1) {
        memset(buf, 0, sizeof(buf));
        memset(info, 0, sizeof(info));

        read(server_fd, buf, 2);
        if(buf[1] == 0){
            printf("Error in server! Please close this client!\n ");
            exit(0);
        }
        if (buf[1] == 21) { // connection ACK
            read(server_fd, buf, 1);
            client_id = buf[0];
            connected = 1;
            sprintf(buf, "Connection is established, client ID is %d\n", client_id);
            mqueue_init(&mqueue);
            mqueue_push(&mqueue, buf, strlen(buf));
        } else if (buf[1] == 1) { // close ACK
            break;
        } else if (buf[1] == 2) { // time
            read(server_fd, buf, 1);
            len = buf[0];
            len = read(server_fd, info, len);
            info[len] = 0;
            sprintf(buf, "Server time is '%s'\n", info);
            mqueue_push(&mqueue, buf, strlen(buf));
        } else if (buf[1] == 3) { // server name
            read(server_fd, buf, 2);
            memcpy(&len_short, buf, 2);
            len = len_short;
            read(server_fd, info, len);
            info[len] = 0;
            sprintf(buf, "Server name is '%s'\n", info);
            mqueue_push(&mqueue, buf, strlen(buf));
        } else if (buf[1] == 4) { // client list
            read(server_fd, buf, 2);
            short len_short;
            memcpy(&len_short, buf, 2);
            len = len_short;
            read(server_fd, info, len);
            info[len] = 0;
            sprintf(buf, "All clients connected to the server:\n%s", info);
            mqueue_push(&mqueue, buf, strlen(buf));
        } else if (buf[1] == 5) { // send msg ACK
            read(server_fd, buf, 1);
            int receiver_client_id = buf[0];
            read(server_fd, buf, 1);
            char ret = buf[0];
            if (ret == 0) {
                sprintf(buf, "Message is sent to client %d successfully\n", receiver_client_id);
            } else {
                sprintf(buf, "Failed to send message to client %d\n", receiver_client_id);
            }
            mqueue_push(&mqueue, buf, strlen(buf));
        } else if (buf[1] == 6) { // msg from another client
            read(server_fd, buf, 1);
            int sender_client_id = buf[0];
            read(server_fd, buf, 2);
            memcpy(&len_short, buf, 2);
            len = len_short;
            read(server_fd, info, len);
            info[len] = 0;
            sprintf(buf, "Client %d sent message '%s'\n", sender_client_id, info);
            mqueue_push(&mqueue, buf, strlen(buf));
        }
    }
    return NULL;
}

void connect_to_server() {
    char ip_str[16];
    memset(ip_str, 0, sizeof(ip_str));
    printf("server ip: ");
    scanf("%s", ip_str);

    int port;
    printf("server port: ");
    scanf("%d", &port);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_aton(ip_str, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);
    if (connect(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Failed to call 'connect'\n");
        close(server_fd);
        return;
    }

    pthread_create(&tid, NULL, process_input, NULL);

    while (connected == 0) {}
}

void close_connection() {
    char buf[2];
    buf[0] = client_id;
    buf[1] = 1;
    send(server_fd, buf, 2, 0);
    
    close(server_fd);
    server_fd = 0;
    connected = 0;
    
    tid = 0;
    printf("Connection is closed.\n");
}

void get_server_time() {
    char buf[2];
    buf[0] = client_id;
    buf[1] = 2;
    send(server_fd, buf, 2, 0);
}

void get_server_name() {
    char buf[2];
    buf[0] = client_id;
    buf[1] = 3;
    send(server_fd, buf, 2, 0);
}

void get_client_list() {
    char buf[2];
    buf[0] = client_id;
    buf[1] = 4;
    send(server_fd, buf, 2, 0);
}

void send_message() {
    char buf[65536];

    buf[0] = client_id;
    buf[1] = 5;

    int receiver_client_id;
    printf("Receiver client ID: ");
    scanf("%d", &receiver_client_id);
    buf[2] = receiver_client_id;

    printf("Message: ");
    fgets(buf + 5, sizeof(buf) - 5, stdin);
    fgets(buf + 5, sizeof(buf) - 5, stdin);
    short len = strlen(buf + 5);
    buf[len + 4] = 0;

    memcpy(buf + 3, &len, 2);

    send(server_fd, buf, len + 5, 0);
}

char receive_message_stop = 0;
void *receive_message(void *args) {
    while (!receive_message_stop) {
        int ret = mqueue_empty(&mqueue);
        if (!ret) {
            char *msg = mqueue_front(&mqueue);
            mqueue_pop(&mqueue);
            printf("[Message] %s", msg);
        }
    }
    return NULL;
}

char heart_stop = 0;
void * heart(void *args){
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;// 5.0 sec
    while (!heart_stop) {
        int err = select(0,NULL,NULL,NULL,&tv);
        char buf[2];
        buf[0] = client_id;
        buf[1] = 7;
        send(server_fd, buf, 2, 0);
    }
    return NULL;
}

int main() {
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to call 'socket'\n");
        return -1;
    }

    pthread_t receive_tid;
    pthread_create(&receive_tid, NULL, receive_message, NULL);

    printf("Client begins to run\n");
    pthread_t heart_tid;
    pthread_create(&heart_tid, NULL, heart, NULL);
    while (1) {
        char line[65536];
        printf("=========================\n%s", hint[connected]);
        int op;
        int ret = scanf("%d", &op);
        fgets(line, sizeof(line), stdin);
        if (ret == 0) {
            continue;
        }
        if (op == 0 && !connected) {
            connect_to_server();
        } else if (op == 1 && connected) {
            close_connection();
        } else if (op == 2 && connected) {
            get_server_time();
        } else if (op == 3 && connected) {
            get_server_name();
        } else if (op == 4 && connected) {
            get_client_list();
        } else if (op == 5 && connected) {
            send_message();
        } else if (op == 6) {
            if (connected) {
                close_connection();
            }
            break;
        } else {
            printf("Unkown operation\n");
        }
    }

    receive_message_stop = 1;
    pthread_join(receive_tid, NULL);
    heart_stop = 1;
    pthread_join(heart_tid, NULL);

    return 0;
}
