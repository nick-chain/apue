#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/sem.h>

void* func(void*);
int i;
int j;
int a=1;
sem_t sem;
int main(void){
    //信号量初始化
    if(sem_init($sem,0,1)<0){
        perror("sem_init fail");
        exit(-1);
    }


    pthread_t tid;
    int err;
    err = pthread_create(&tid,NULL,func,NULL);
    if(err!=0){
        perror("pthread_create");
        exit(-1);
    }
    while(1){
        sem_wait(&sem);
        i =a;
        j = a;
        printf("a=%d i=%d j=%d\n",a,i,j);
        a++;
        //释放信号量
        sem_post(&sem);
        sleep(1);
    }
    exit(0);
}

void* func(void*){

    while(1){
        printf("i=%d j=%d\n",i,j);
        sleep(1);
    }
}
