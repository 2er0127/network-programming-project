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
    int count = 0;
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
    
    // 서버로 부터 정답 숫자를 읽어와 변수에 저장
    if(read(sock, &random, sizeof(random)) == -1)
        error_handling("c-random read error");
    
    // 반복문 시작
    for(int i = 0; i < 20; i++) {
        printf("%d 번째 시도\n", i + 1);
        printf("1에서 50사이의 숫자를 입력하세요 : ");
        scanf("%d", &getNum);
    
        if(write(sock, &getNum, sizeof(getNum)) == -1)
            error_handling("c-getNum write error");
    
        // 입력한 값과 정답 매칭
        if(read(sock, &hint, BUF_SIZE) == -1)
            error_handling("c-hint read error");
        printf("%s\n", hint);

        if(getNum == ntohl(random)) {
            if(read(sock, &count, sizeof(count)) == -1)
                error_handling("c-count read error");
            printf("%d 번만에 맞추셨습니다.\n", ntohl(count));
            break;
        }
    }
    
    printf("정답은 %d 입니다 !!\n", ntohl(random));
    printf("게임이 종료됩니다.\n");
    
    close(sock);
    
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
