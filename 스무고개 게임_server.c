#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char* argv[]) {
    int serv_sock, client_sock;
    int random, getNum;
    char hint[BUF_SIZE];
    int str_len;
    
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_addr_size;
    
    if(argc != 2) {
        printf("Usage : %s <PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");
    
    client_addr_size = sizeof(client_addr);
    client_sock = accept(serv_sock, (struct sockaddr*) &client_addr, &client_addr_size);
    if(client_sock == -1)
        error_handling("accept error");
    
    srand(time(NULL));
    random = (rand() % 50) + 1; // 1~50사이의 랜덤 숫자를 생성하여 random 변수에 저장한다.
    printf("%d", random);
    
    write(client_sock, random, sizeof(random));
    
    // 클라이언트에서 입력한 숫자를 받아오기
    read(client_sock, getNum, BUF_SIZE);
    
    if(getNum > random)
        hint[1] = "입력하신 값보다 작습니다.\n";
    else if(getNum < random)
        hint[2] = "입력하신 값보다 큽니다.\n";
    else
        hint[0] = "정답입니다!\n";
    
    
    
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
