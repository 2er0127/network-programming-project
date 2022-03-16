#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void error_handling(char* message);

int main() {
    int fd;
    char buf[] = "My name is seona\n";
    
    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if(fd == -1)
        error_handling("open() error");
    printf("파일 디스크립터(번호) : %d\n", fd);
    
    if(write(fd, buf, sizeof(buf)) == -1)
        error_handling("write() error");
    
    close(fd);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
