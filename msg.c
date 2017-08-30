#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/msg.h>

typedef struct msgbuf{
    long mtype;
    char buf[256];

}MSG;

#define LENSIZE (sizeof(MSG)-sizeof(LENSIZE))
int main(){
    key_t key = ftok(".",'g');
    if(key<0){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int msgid = msgget(key,0666|IPC_CREAT);
    if(msgid<0){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    //通过消息队列来通信

    MSG msg;
    msg.mtype = TYPER;//消息发送给谁
    fgets(msg,buf,256,stdin);//消息正文
    if(msgget(msgid,&msg,LENSIZE,0)<0){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    //接受消息
    MSG msg1;
    if(msgrcv(msgid,&msg1,TYPER,LEN,0)<0){
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    //删除消息队列
    //那个进程
    msgctl()

   

}
