
//void (*signal(int signo, void (*func)(int)))(int);

// signal(int signo, void(*func)(int)) signal是要接受一个int和一个指向void (int)这样子的函数指针
// 他的返回值是void (int)函数指针
//void (*p)(int) p 是一个函数指针指向void (int)
//typedef void(*signalhandler_t)(int)
// signalhandler_t signal(int signum, sighandler_t handler)
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
    if(sig == SIGALRM)
    puts("time out!");
    alarm(2);
}

void keycontrol(int sig){
    if(sig == SIGINT)
    puts("CTRL+C pressed ");
}

int main(int argc, char*argv[]){
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for(int i = 0; i < 3; i++){
        puts("wait...");
        sleep(100);
    }
    return 0;
    
}