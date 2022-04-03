#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int serv_sock, client_sock;
    int kor[BUF_SIZE];
    int eng[BUF_SIZE];
    int math[BUF_SIZE];
    int tot;
    float avg;
    char grade;
    int str_len;
    
    struct sockaddr_in serv_addr, client_addr;
    soclen_t client_addr_size;
    
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
    
    for(int i = 0; i < 5 i++) {
        client_sock = accept(serv_sock, (struct sockaddr*) &client_addr, &client_addr_size);
        if(client_sock == -1)
            error_handling("accept error");
        else
            printf("연결된 클라이언트 : %d\n", i+1);
        
        while((str_len = read(client_sock, kor, BUF_SIZE)) != 0)
            while((str_len = read(client_sock, eng, BUF_SIZE)) != 0)
                while((str_len = read(client_sock, math, BUF_SIZE)) != 0)
                    write(client_sock, (char*) &grade, str_len);
        
        for(int i = 0; i < 1; i++) {
            tot = kor[i] + eng[i] + math[i];
            avg = (float)tot / 3.0;
            printf("총점 : %d\n", tot);
            printf("평균 : %f\n", avg);
        }
        
        if(avg >= 90) {
            grade = 'A';
            printf("A", grade);
        }
        
        else if(avg >= 80) {
            grade = 'B';
            printf("B", grade);
        }
        
        else if(avg >= 70) {
            grade = 'C';
            printf("C", grade);
        }
        
        else if (avg >= 60) {
            grade = 'D';
            printf("D", grade);
        }
        
        else {
            grade = 'F';
            printf("F", grade);
        }
        
        close(client_sock);
    }
    
    close(serv_sock);
    
    return 0;
}

void error_handling(char* grade) {
    fputs(grade, stderr);
    fputc('\n', stderr);
    exit(1);
}
