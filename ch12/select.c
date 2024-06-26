#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 30

int main(int argc, char* argv[]){
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    
    FD_ZERO(&reads);
    FD_SET(0, &reads); //0号表示标准输入 监视标准输入

    /*
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;
    */

   while(1){
    temps = reads; //复制是因为select之后，除了发生变化以外的位置，其他都会变为0，这样是为了记住初始值
    timeout.tv_sec = 5;
    timeout.tv_usec=0;
    //fd最大值加一
    result = select(1, &temps, 0, 0, &timeout);
    if(result == -1){
        puts("select() error!");
        break;
    }
    else if(result == 0){
        puts("Time-out!");
    }
    else{
        if(FD_ISSET(0, &temps)){
            str_len = read(0, buf, BUF_SIZE);
            buf[str_len] = 0;
            printf("message from console: %s", buf);
        }
    }
   }
}