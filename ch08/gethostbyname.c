#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
void error_handling(char *message);


int main(int argc, char* argv[]){
    int i;
    struct hostent *host;
    
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    host = gethostbyname(argv[1]);
    if(!host)
    error_handling("gethost... error");

    printf("official name: %s \n", host->h_name);
    for(i = 0; host->h_aliases[i]; i++){
        printf("Aliases %d: %s \n", i + 1, host->h_aliases[i]);
    }
    printf("Address type : %s \n",
        (host->h_addrtype==AF_INET)?"AF_INET":"AF_INET6");
    for(i=0; host->h_addr_list[i];i++)
    printf("IP addr %d: %s \n", i + 1,
     inet_ntoa(*(struct in_addr*)host->h_addr_list[i])); //inet_ntoa是吧ipv4地址从二进制转化成点分字符串 这个h_addr_list[i]是char*但是指向的其实是in_addr结构体
     //in_addr其实是uint32_t 这么做是为了通用性，可以存储ipv6
     //host->h_addr_list[i]);
     return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}