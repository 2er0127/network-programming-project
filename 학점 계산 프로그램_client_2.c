#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    int kor;
    int eng;
    int math;
    int tot;
    float avg;
    char grade;
    int str_len;
    
    struct sockaddr_in serv_addr;
    
    if(argc != 3) {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect error");
    else
        puts("연결하는 중입니다........");
    
    fputs("국어 점수를 입력해주세요 : ", stdout);
    fgets(kor, BUF_SIZE, stdin);
    write(sock, kor, strlen(kor));
        
    fputs("영어 점수를 입력해주세요 : ", stdout);
    fgets(eng, BUF_SIZE, stdin);
    write(sock, eng, strlen(eng));
        
    fputs("수학 점수를 입력해주세요 : ", stdout);
    fgets(math, BUF_SIZE, stdin);
    write(sock, math, strlen(math));
        
    read(sock, (char*) &grade, BUF_SIZE);
        
    printf("당신의 학점은 : %c 입니다.\n", grade);
    
    close(sock);
    
    return 0;
}

void error_handling(char* grade) {
    fputs(grade, stderr);
    fputc('\n', stderr);
    exit(1);
}
