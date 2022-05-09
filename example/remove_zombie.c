#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void read_childproc(int);

int main(int argc, char *argv[]) {
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);
    
    pid = fork();
    if(pid == 0) { // 자식 프로세스 실행 영역
        puts("나는 자식 프로세스~");
        sleep(10);
        
        return 12;
    }
    else { // 부모 프로세스 실행 영역
        printf("Child proc id : %d\n", pid);
        pid = fork();
        if(pid == 0) { // 또다른 자식 프로세스 실행 영역
            puts("나는 자식 프로세스~");
            sleep(10);
            
            exit(24);
        }
        else {
            printf("Child proc id : %d\n", pid);
            for(int i = 0; i < 5; i++) {
                puts("wait...");
                sleep(5);
            }
        }
    }
    
    return 0;
}

void read_childproc(int sig) {
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status)) {
        printf("Removed proc id : %d\n", id);
        printf("Child send : %d\n", WEXITSTATUS(status));
    }
}
