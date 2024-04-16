#include <arpa/inet.h>
#include <stdio.h>
//char* to long
int main(int argc, char *argv[]){
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr==INADDR_NONE)
    printf("Error occured \n");
    else
    printf("NEtword orderd interger addr: %#lx \n", conv_addr);

    conv_addr=inet_addr(addr2);
        if(conv_addr==INADDR_NONE)
    printf("Error occured \n");
    else
    printf("NEtword orderd interger addr: %#lx \n", conv_addr);

}