#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char* message);

int main(int argc, char* argv[]) { // 명령형 인자.
    int serv_sock; // 서버 소켓
    int client_sock; // 클라이언트 소켓 (데이터 통신용)
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;
    
    char message[] = "Hello World!";
    
    if(argc != 2) { // argc가 2가 아니면 실패. ex) ./hserver 9190 (2개)
        printf("Usage : %s <port>\n", argv[0]); // ex) argv[0] = ./hserver, Usage : ./hserver 9190 이런식으로 시도해라- 가이드를 주는 것.
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 서버 소켓 생성
    if(serv_sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 자동으로 서버의 IP 주소를 가지고 온다.
    serv_addr.sin_port = htons(atoi(argv[1])); // ex)./hserver 9190 에서 9190을 의미
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");
    
    // ---------------------------------- 연결을 받을 준비 완료. 대기 상태
    
    client_addr_size = sizeof(client_addr); // accept 함수에서 크기를 넘겨야할 때 무조건 주소값을 넘겨야하기 때문에 포인터 사용
    
    client_sock = accept(serv_sock, (struct sockaddr*) &client_addr, &client_addr_size);
    if(client_sock == -1)
        error_handling("accept error");
    
    write(client_sock, message, sizeof(message));
    close(client_sock); // 클라이언트 소켓을 먼저 닫기
    close(serv_sock);
    
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
