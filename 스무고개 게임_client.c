#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char* argv[]) {
    int sock;
    int getNum; // 클라이언트가 입력받는 숫자
    int random;
    char hint[BUF_SIZE];
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
        printf("숫자 맞추기 스무고개 게임에 오신 것을 환영합니다!\n");
        printf("GAME START!\n");
    }
    
    // 서버로 부터 정답 숫자를 읽어와 변수에 저장해두기.
    read(sock, random, sizeof(random));
    
    printf("1에서 50사이의 숫자를 입력하세요 : ");
    scanf("%d", &getNum);
    
    // 입력한 값과 정답 매칭
    read(sock, hint, BUF_SIZE);
    printf("%c\n", hint);
    
    
    
    
    
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
