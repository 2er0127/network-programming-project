// connected UDP socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;
    
    struct sockaddr_in serv_adr, from_adr;
    
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    
    // connect 함수 호출. 타겟의 주소 정보가 미리 등록되어 있다
    connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
    
    while(1) {
        fputs("메세지를 입력하세요 (그만두려면 q) : ", stdout);
        fgets(message, sizeof(message), stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        /*
         sendto(sock, message, strlen(message), 0, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
         */
        write(sock, message, strlen(message)); // connect 함수를 사용했기 때문에 write 함수 사용 가능
        
        /*
         adr_sz = sizeof(from_adr);
         str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*) &from_adr, &adr_sz);
         */
        str_len = read(sock, message, sizeof(message) -1); // connect 함수를 사용했기 때문에 read 함수 사용 가능
        
        message[str_len] = 0;
        printf("Message from server : %s", message);
    }
    
    close(sock);
    
    return 0;
 }

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
