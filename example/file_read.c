#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 100

void error_handling(char* message);

int main() {
    int fd;
    char buf[BUF_SIZE];
    
    fd = open("data.txt", O_RDONLY);
    if(fd == -1)
        error_handling("open() error");
    printf("파일 디스크립터(번호) : %d\n", fd);
    
    if(read(fd, buf, sizeof(buf)) == -1)
        error_handling("read() error");
    
    printf("파일 내용 : %s", buf);
    
    close(fd);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
