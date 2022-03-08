#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    char callNum[30];
    char gender[10];
    int age;
} Friend;

int main() {
    Friend *aF = malloc(sizeof(Friend));
    int num, h;
    int max = 0, min = 1000;
    int man = 0, fe = 0;
    char comNum[20];
    int count = 0;
    
    while(1) {
        printf("------------------\n");
        printf("[메뉴]\n1)개별 신상 정보 입력\n2)전체 신상 정보 출력\n3)개별 신상 정보 조회\n4)개별 신상 정보 삭제\n5)프로그램 종료\n");
        printf("------------------\n");
        printf("원하시는 메뉴를 선택해주세요 ");
    
        scanf("%d", &num);
    
        switch(num) {
            case 1 :
                printf("1번 개별 신상 정보 입력을 선택하셨습니다.\n");
                printf("몇 명을 추가하시겠습니까? ");
                scanf("%d", &h);
                for(int i = 0; i < h; i++) {
                    printf("영문 이름을 입력해 주세요 : ");
                    scanf("%s", aF[i].name);
                    printf("휴대폰 번호를 입력해 주세요 (- 필수 입력) : ");
                    scanf("%s", aF[i].callNum);
                    printf("성별을 입력해주세요 (남자는 'M', 여자는 'F') : ");
                    scanf("%s", aF[i].gender);
                    printf("나이를 입력해주세요 (숫자만 입력) : ");
                    scanf("%d", &aF[i].age);
                    printf("입력이 완료되었습니다.\n");
                }
                break;
                
            case 2 :
                printf("2번 전체 신상 정보 출력을 선택하셨습니다.\n");
                for(int i = 0; i < h; i++) {
                    printf("이름 : %s, 휴대폰 번호 : %s, 성별 : %s, 나이 : %d\n", aF[i].name, aF[i].callNum, aF[i].gender, aF[i].age);
                }
                for(int i = 0; i < h; i++) {
                    max = aF[0].age;
                    min = aF[0].age;
                    if(aF[i].age > max)
                        max = aF[i].age;
                    if(aF[i].age < min)
                        min = aF[i].age;
                    if (strcmp(aF[i].gender, "M") == 0)
                        man++;
                    if(strcmp(aF[i].gender, "F") == 0)
                        fe++;
                }
                printf("총 %d명\n", h);
                printf("남자 : %d명\n", man);
                printf("여자 : %d명\n", fe);
                printf("최고령 : %d세\n", max);
                printf("최저령 : %d세\n", min);
                break;
                
            case 3 :
                printf("3번 개별 신상 정보 조회를 선택하셨습니다.\n");
                printf("조회할 이름 입력 : ");
                scanf("%s", comNum);
                for(int i = 0; i < h; i++) {
                    if(strcmp(aF[i].name, comNum) == 0) {
                        printf("이름 : %s, 휴대폰 번호 : %s, 성별 : %s, 나이 : %d\n", aF[i].name, aF[i].callNum, aF[i].gender, aF[i].age);
                        count++;
                    }
                }
                if(count == 0)
                    printf("[%s]을/를 조회할 수 없습니다.\n", comNum);
                break;
                
            case 4 :
                printf("4번 개별 신상 정보 삭제를 선택하셨습니다.\n");
                break;
                
            case 5 :
                printf("프로그램을 종료합니다.\n");
                free(aF);
                return 0;
        }
    }
}
