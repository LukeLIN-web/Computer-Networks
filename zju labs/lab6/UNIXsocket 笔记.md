## UNIXsocket 笔记

因为微软doc没有中文版, 那我手动翻译一下. 我是用TCP 协议来进行客户端和服务器.  这是win32 ,不是 unix. 可能也差不多我没有找到 unix 的文档. 

我找到了一些资料

UNIX网络编程卷1：套接字联网API（第3版）.pdf

[The Linux man-pages project (kernel.org)](https://www.kernel.org/doc/man-pages/)

man socket就可以显示, 非常全. 



#### socket 

[AF_INET - Windows drivers | Microsoft Docs](https://docs.microsoft.com/en-us/windows-hardware/drivers/network/af-inet)

第二个参数是选scoket类型. 

TCP应该是用SOCK_STREAM
Supports reliable connection-oriented byte stream communication.

第三个参数是选协议. 我们选择TCP

##### socketaddr_in 结构体

sin_family 必须是AF_INET

sin_addr 是 [IN_ADDR](https://docs.microsoft.com/en-us/previous-versions/windows/hardware/drivers/ff556972(v=vs.85)) structure that contains an IPv4 transport address.

sin_port  = 我们TCP的port号



多线程模式的listen.

```c
    pthread_create(&listen_tid, NULL, listen_new_client, &server_fd);
    //   int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
```

