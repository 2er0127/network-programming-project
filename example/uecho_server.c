// uecho_server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    
    struct sockaddr_in serv_adr, clnt_adr;
    
    if(argc != 2) {
        printf("%s <port>를 사용하세요.\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0); // UDP
    if(serv_sock == -1)
        error_handling("UDP socket creation error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    while(1) {
        clnt_adr_sz = sizeof(clnt_adr);
        // recvfrom(소켓의 파일 디스크립터, 버퍼의 주소 값 전달, 수신할 최대 바이트 수, 옵션 지정(지정할 옵션이 없다면 0), 발신지 주소 정보 구조체 포인터, 전달된 주소 값의 구조체 변수의 크기 전달(포인터)
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*) &clnt_adr, &clnt_adr_sz);
        // sendto(소켓의 파일 디스크립터, 버퍼의 주소 값 전달, 수신할 최대 바이트 수, 옵션 지정(지정할 옵션이 없다면 0), 목적지 주소 정보 구조체 포인터, 전달된 주소 값의 구조체 변수의 크기 전달
        sendto(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*) &clnt_adr, clnt_adr_sz);
    }
    
    close(serv_sock);
    
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
