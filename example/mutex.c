#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 100

void *thread_inc(void *arg);
void *thread_des(void *arg);

long long num = 0;
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
    pthread_t thread_id[NUM_THREAD];
    
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NUM_THREAD; i++) {
        if(i % 2)
            pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
        else
            pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
    }

    for(int i = 0; i < NUM_THREAD; i++)
        pthread_join(thread_id[i], NULL);

    printf("result : %lld\n", num);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

void *thread_inc(void *arg) {
    pthread_mutex_lock(&mutex); // 실행 시간이 오래 걸리지 않는다면, 아래 방법도 괜찮다.
    for(int i = 0; i < 50000000; i++)
        num += 1;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_des(void *arg) {
    for(int i = 0; i < 50000000; i++) {
        pthread_mutex_lock(&mutex); // lock&unlock이 오래 걸린다면, 위 방법이 더 낫다.
        num -= 1;
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}
