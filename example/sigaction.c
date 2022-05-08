#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int);

int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);
    
    alarm(2);
    
    for(int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100);
    }
    
    return 0;
}

void timeout(int sig) {
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2); // 2초 간격으로 시그널 반복 발생을 위해 호출
}
