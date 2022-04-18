// 2019100991 이선아
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    int str_len;
    struct sockaddr_in serv_adr;
    char bingo[25];
    int a, b, c = 0;
    char cho[10] = {0, };
    int fin[25] = {0, };
    int garo, sero;

    if (argc != 3) {
        printf("%s IP PORT 순으로 입력해보세요.\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    srand(time(NULL));

    if (connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    for (a = 0; a < 25; a++) {
        bingo[a] = rand() % 25 + 1;
        for (b = 0; b < a; b++) {
            if (bingo[a] == bingo[b]) {
                --a;
                break;
            }
        }
    }

    printf("신나는 빙고 게임\n\n");

    for (c = 0; c < 25; c++) {
        printf("%d\t", bingo[c]);
        if ((c + 1) % 5 == 0)
            printf("\n");
    }

    for (a = 0; a < 10; a++) {
        sleep(2);
        cho[(a * 2)] = (rand() % 25 + 1);
        for (b = 0; b < (a * 2); b++) {
            if (cho[(a * 2)] == cho[b]) {
                cho[(a * 2)] = (rand() % 25 + 1);
                b--;
            }
        }

        printf("\n%d. 클라이언트 선택 : %d\n\n", (a * 2) + 1, cho[(a * 2)]);

        for (b = 0; b < 25; b++) {
            if (bingo[b] == cho[(a * 2)]) {
                bingo[b] = 'O';
                fin[(a*2)] = b;
            }
        }

        for (b = 0; b < 25; b++) {
            for (c = 0; c < (a * 2) + 1; c++) {
                if (b == fin[c] && c < (a * 2) + 1) {
                    printf("%c\t", bingo[b]);
                    if ((b + 1) % 5 == 0)
                        printf("\n");
                    break;
                }
                else if (b != fin[c] && c == (a * 2)) {
                    printf("%d\t", bingo[b]);
                    if ((b + 1) % 5 == 0)
                        printf("\n");
                }
                else if (b != fin[c] && c < (a * 2) + 1) {
                    continue;
                }
            }
        }
        printf("\n");

        for (b = 0; b < 5; b++) {
            garo = 0;
            if (bingo[b * 5] == 'O') {
                for (c = 1; c < 5; c++) {
                    if (bingo[b * 5] == bingo[b * 5 + c])
                        garo++;
                    if (garo == 4)
                        break;
                }
            }
            if (garo == 4)
                break;
        }
        
        if (garo == 4) {
            printf("\n빙고!\n");
            cho[(a + 2)] = 99;
            write(sock, cho, BUF_SIZE);
            break;
        }

        for (b = 0; b < 5; b++) {
            sero = 0;
            for (c = 1; c < 5; c++) {
                if (bingo[b] == 'O') {
                    if (bingo[b] == bingo[b + 5 * c])
                        sero++;
                    if (sero == 4)
                        break;
                }
            }
            if (sero == 4)
                break;
        }
        
        if (sero == 4) {
            printf("\n빙고!\n");
            cho[(a + 2)] = 99;
            write(sock, cho, BUF_SIZE);
            break;
        }

        write(sock, cho, BUF_SIZE);
        read(sock, cho, BUF_SIZE);

        if (cho[(a * 2) + 1] == 99)
            break;

        printf("%d. 서버 선택 : %d\n\n", (a + 1) * 2, cho[(a * 2) + 1]);

        for (b = 0; b < 25; b++) {
            if (bingo[b] == cho[(a * 2) + 1]) {
                bingo[b] = 'O';
                fin[(a * 2) + 1] = b;
            }
        }

        for (b = 0; b < 25; b++) {
            for (c = 0; c < (a * 2) + 2; c++) {
                if (b == fin[c] && c < (a * 2) + 2) {
                    printf("%c\t", bingo[b]);
                    if ((b + 1) % 5 == 0)
                        printf("\n");
                    break;
                }
                else if (b != fin[c] && c == (a * 2) + 1) {
                    printf("%d\t", bingo[b]);
                    if ((b + 1) % 5 == 0)
                        printf("\n");
                }
                else if (b != fin[c] && c < (a * 2) + 2) {
                    continue;
                }
            }
        }

        for (b = 0; b < 5; b++) {
            garo = 0;
            if (bingo[b * 5] == 'O') {
                for (c = 1; c < 5; c++) {
                    if (bingo[b * 5] == bingo[b * 5 + c])
                        garo++;
                    if (garo == 4)
                        break;
                }
            }
            if (garo == 4)
                break;
        }
        
        if (garo == 4) {
            printf("\n빙고!\n");
            cho[(a + 1) * 2] = 99;
            write(sock, cho, BUF_SIZE);
            break;
        }

        for (b = 0; b < 5; b++) {
            sero = 0;
            for (c = 1; c < 5; c++) {
                if (bingo[b] == 'O') {
                    if (bingo[b] == bingo[b + 5 * c])
                        sero++;
                    if (sero == 4)
                        break;
                }
            }
            if (sero == 4)
                break;
        }
        
        if (sero == 4) {
            printf("\n빙고!\n");
            cho[(a + 1) * 2] = 99;
            write(sock, cho, BUF_SIZE);
            break;
        }
    }

    close(sock);
    
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
