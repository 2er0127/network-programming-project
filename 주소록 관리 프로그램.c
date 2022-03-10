#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    char callNum[50];
    char gender[10];
    int age;
} Friend;

typedef struct {
    int count; // 친구 수
    int max; // 최고령
    int min; // 최저령
    int mCount; // 남성
    int fCount; // 여성
} Info;

void initInfo(Info*);
void printMenu();
void inputFriend(Friend*, Info*);
void calculate(Friend*, Info*);
void friendInfo(Info*);

int main() {
    Friend *friend = malloc(sizeof(Friend));
    Info* info = malloc(sizeof(Info));
    int num = 0;
    char findName[30];
    char delName[30];
    
    initInfo(info);
    
    while(1) {
        printMenu();
    
        scanf("%d", &num);
    
        switch(num) {
            case 1 :
                printf("1번 개별 신상 정보 입력을 선택하셨습니다.\n");
                
                inputFriend(friend, info);
                calculate(friend, info);
                
                break;
                
            case 2 :
                printf("2번 전체 신상 정보 출력을 선택하셨습니다.\n");
                for(int i = 0; i < info->count; i++) {
                    printf("이름 : %s, 휴대폰 번호 : %s, 성별 : %s, 나이 : %d\n", friend[i].name, friend[i].callNum, friend[i].gender, friend[i].age);
                }
                
                friendInfo(info);
                
                break;
                
            case 3 :
                printf("3번 개별 신상 정보 조회를 선택하셨습니다.\n");
                printf("조회할 이름 입력 : ");
                scanf("%s", findName);
                
                if (!strcmp(findName, friend->name))
                    printf("이름 : %s, 휴대폰 번호 : %s, 성별 : %s, 나이 : %d\n", friend->name, friend->callNum, friend->gender, friend->age);
                else
                    printf("[%s]을/를 조회할 수 없습니다.\n", findName);
                
                break;
                
            case 4 :
                printf("4번 개별 신상 정보 삭제를 선택하셨습니다.\n");
                printf("삭제할 이름 입력 : ");
                scanf("%s", delName);
                
                if (!strcmp(delName, friend->name))
                    printf("[%s] 학생의 정보를 삭제했습니다.\n", delName);
                else
                    printf("[%s] 학생의 정보가 없습니다.\n", delName);
                
                break;
                
            case 5 :
                printf("프로그램을 종료합니다.\n");
                
                free(friend);
                free(info);
                
                return 0;
        }
    }
}

// 메뉴 보기
void printMenu() {
    printf("------------------\n");
    printf("[메뉴]\n1)개별 신상 정보 입력\n2)전체 신상 정보 출력\n3)개별 신상 정보 조회\n4)개별 신상 정보 삭제\n5)프로그램 종료\n");
    printf("------------------\n");
    printf("원하시는 메뉴를 선택해주세요 ");
}

void initInfo(Info* info) {
    info->count = 0;
    info->max = 0;
    info->min = 99999;
    info->mCount = 0;
    info->fCount = 0;
}

void inputFriend(Friend* friend, Info* info) {
    printf("영문 이름을 입력해 주세요 : ");
    scanf("%s", friend[info->count].name);
    printf("휴대폰 번호를 입력해 주세요 (- 필수 입력) : ");
    scanf("%s", friend[info->count].callNum);
    printf("성별을 입력해주세요 (남자는 'M', 여자는 'F') : ");
    scanf("%s", friend[info->count].gender);
    printf("나이를 입력해주세요 (숫자만 입력) : ");
    scanf("%d", &friend[info->count].age);
    printf("입력이 완료되었습니다.\n");
}

void calculate(Friend* friend, Info* info) {
    if(friend[info->count].age > info->max)
        info->max = friend[info->count].age;
    if(friend[info->count].age < info->min)
        info->min = friend[info->count].age;
    if (strcmp(friend[info->count].gender, "M") == 0)
        info->mCount++;
    if (strcmp(friend[info->count].gender, "F") == 0)
        info->fCount++;
    info->count++;
}

void friendInfo(Info* info) {
    printf("총 %d명\n", info->count);
    printf("남자 : %d명\n", info->mCount);
    printf("여자 : %d명\n", info->fCount);
    printf("최고령 : %d세\n", info->max);
    printf("최저령 : %d세\n", info->min);
}
