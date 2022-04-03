#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char* grade);

int main(int argc, char* argv[]) {
    int sock;
    char score[BUF_SIZE];
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
    else {
        printf("연결하는 중입니다........\n");
        printf("...............\n");
    }
    
    printf("학점 계산 프로그램입니다.\n");
    printf("국어 점수를 입력하세요 : ");
    scanf("%d", (int*) &score[0]);
    printf("영어 점수를 입력하세요 : ");
    scanf("%d", (int*) &score[1]);
    printf("수학 점수를 입력하세요 : ");
    scanf("%d", (int*) &score[2]);
    
    write(sock, score, strlen(score));
    
    read(sock, &grade, 1);
    
    printf("당신의 학점은 %c 입니다.\n", grade);
    
    close(sock);
    
    return 0;
}

void error_handling(char* grade) {
    fputs(grade, stderr);
    fputc('\n', stderr);
    exit(1);
}
