#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt;
    
    struct sockaddr_in serv_adr;
    
    if(argc != 3) {
        printf("%s <IP> <port> 를 입력해보세요.\n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect error");
    else
        printf("연결 중입니다......\n");
    
    fputs("계산할 숫자의 갯수를 입력하세요 : ", stdout);
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt; // 배열에 저장하기 위해 (char)로 형을 맞춰준다.
    
    for(int i= 0; i < opnd_cnt; i++) {
        printf("%d, 숫자를 입력하세요 : ", i+1);
        scanf("%d", (int*) &opmsg[i * OPSZ+1]); // [0] 한 바이트에 이미 opnd_cnt가 들어있기 때문에 +1을 해주어 다음부터 채워준다.
    }
    
    fgetc(stdin); // 버퍼에 남아 있는 '\n'을 읽어들임.
    fputs("연산자를 입력하세요 : ", stdout);
    scanf("%c", &opmsg[opnd_cnt * OPSZ+1]);
    
    write(sock, opmsg, opnd_cnt * OPSZ+2);
    read(sock, &result, RLT_SIZE);
    
    printf("결과값입니다 : %d\n", result);
    
    close(sock);
    
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
