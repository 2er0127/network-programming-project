#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char* message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char* argv[]) {
    int serv_sock, client_sock;
    char opinfo[BUF_SIZE];
    int result, opnd_cnt;
    int recv_cnt, recv_len;
    
    struct sockaddr_in serv_adr, client_adr;
    socklen_t client_adr_sz;
    
    if(argc != 2) {
        printf("%s <port> 형식을 사용해보세요.\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind error");
    if(listen(serv_sock, 5) == -1)
        error_handling("listen error");
    client_adr_sz = sizeof(client_adr);
    
    for(int i = 0; i < 5; i++) {
        opnd_cnt = 0;
        client_sock = accept(serv_sock, (struct sockaddr*) &client_adr, &client_adr_sz);
        read(client_sock, &opnd_cnt, 1);
        
        recv_len = 0;
        while((opnd_cnt * OPSZ+1) > recv_len) {
            recv_cnt = read(client_sock, &opinfo[recv_len], BUF_SIZE-1);
            recv_len += recv_cnt;
        }
        
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
        write(client_sock, (char*) &result, sizeof(result)); // result 결과값 형 맞추어 클라이언트에게 보내기
        
        close(client_sock);
    }
    
    close(serv_sock);
    
    return 0;
}

int calculate(int opnum, int opnds[], char op) { // opnds[]는 실제 숫자가 들어있는 배열
    int result = opnds[0];
    
    switch(op) {
        case '+':
            for(int i = 0; i < opnum; i++)
                result += opnds[i];
            break;
        case '-':
            for(int i = 0; i < opnum; i++)
                result -= opnds[i];
            break;
        case '*':
            for(int i = 0; i < opnum; i++)
                result *= opnds[i];
            break;
    }
    
    return result;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
