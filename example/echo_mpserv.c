#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30

void read_childproc(int);
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
    
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind error");
    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");
    
    while(1) {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &adr_sz);
        if(clnt_sock == -1)
            continue;
        else
            puts("new client connected...");
        
        pid = fork();
        if(pid == -1) {
            close(clnt_sock);
            continue;
        }
        if(pid == 0) { // 자식 프로세스 실행 영역
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
                write(clnt_sock, buf, str_len);
            
            close(clnt_sock);
            puts("client disconnected");
            
            return 0;
        }
        else // 부모 프로세스 실행 영역
            close(clnt_sock);
    }
    
    close(serv_sock);
    
    return 0;
}

void read_childproc(int sig) { // 시그널 핸들러 함수
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id : %d\n", pid);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


