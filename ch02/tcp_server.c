#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage : %s <port>\n, argv[0]");
        exit(1);
    }
    // PF_INET ipv4 sockstream创建一个基于tcp的流式套接字
    /*
        arg: 1.协议族 ipv4 
        2.传输类型信息 SOCK_STREAM 面向连接的套接字（无数据边界） 有缓冲区，假如缓冲区满了会停止发送 可靠 
        SOCK_DGRAM 快， 不可靠 数据有边界
        3.计算机间通信中使用的协议信息 一般为0
    */ 
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");
    // 机器可能是小端序，有的是大端序，这样同一在网络表示
    //h: host n:network s :short l:long
    //s：端口号 l：ip地址
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; //ipv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//监听所有网络接口的连接请求 htonl将主机字节序转化成网络字节序
    serv_addr.sin_port = htons(atoi(argv[1]));// 设置端口号 atoi将传入的argv1转换成整数，然后用htos将端口号从主机字节序转化成网络字节序

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    //第二个参数表示 backlog，请求等待队列，最多多少个请求进入队列
    if(listen(serv_sock, 5)== -1)
    error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
    error_handling("accept() error");

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}