#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status;
    pid_t pid = fork();
    
    if(pid == 0)
        return 3;
    else {
        printf("Child PID : %d\n", pid);
        pid = fork();
        if(pid == 0)
            exit(7);
        else {
            printf("Child PID : %d\n", pid);
            wait(&status); // 종료된 프로세스 관련 정보는 status에 담기고 해당 정보의 프로세스는 완전히 소멸된다.
            /* WIFEXITED : 자식 프로세스가 정상 종료한 경우 '참(True)'을 반환
             WEXITSTATUS : 자식 프로세스의 전달 값을 반환
             */
            if(WIFEXITED(status)) // 정상 종료되었을 때
                printf("Child send one : %d\n", WEXITSTATUS(status)); // 반환된 값
            
            wait(&status);
            if(WIFEXITED(status))
                printf("Child send two : %d\n", WEXITSTATUS(status));
            sleep(30);
        }
    }
    
    return 0;
}
