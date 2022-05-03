#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// wait()의 블로킹 문제 해결책 waitpid()
int main(int argc, char *argv[]) {
    int status;
    pid_t pid = fork();
    
    if(pid == 0) {
        sleep(15);
        return 24;
    }
    else {
        while(!waitpid(-1, &status, WNOHANG)) {
        // 헤더파일 sys/wait.h에 선언된 상수 WNOHANG을 인자로 전달하면, 종료된 자식 프로세스가 존재하지 않아도 블로킹 상태에 있지 않고 0을 반환하며 함수를 빠져 나온다.
            sleep(3);
            puts("sleep 3sec.");
        }
        
        if(WIFEXITED(status))
            printf("Child send %d\n", WEXITSTATUS(status));
    }
    
    return 0;
}
