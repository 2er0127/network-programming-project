#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void timeout(int);
void keycontrol(int);

int main(int argc, char *argv[]) {
    signal(SIGALRM, timeout); // 시그널 핸들러
    signal(SIGINT, keycontrol); // 시그널 핸들러
    alarm(2); // 시그널 발생을 2초 뒤로 예약
    
    for(int i = 0; i < 3; i++) {
        puts("wait...");
        sleep(100); // 100초 자고 있지만, 시그널 발생 시 깬다.
    }
    
    return 0;
}

void timeout(int sig) {
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2); // 2초 간격으로 시그널 반복 발생을 위해 호출
}

void keycontrol(int sig) {
    if(sig == SIGINT)
        puts("CTRL+C pressed");
}
