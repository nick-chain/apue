#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(void){
    pid_t child1,child2,child;

    child1 = fork();
    if(child1<0){
        perror("child1 fork");
        exit(-1);
    }
    else if(child1 == 0){
        printf("In child1 porcess\n");
        if((execlp("ls","ls","-hl",NULL))<0){
            perror("execlp fail:");
            exit(-1);
        }
    }
    
    else{
        child2 = fork();
        if(child2<0){
            perror("fork child2");
            exit(-1);
        }
        else if(child2 == 0){
            printf("In child2 process,sleep 5 second and then exit\n");
            sleep(5);
            exit(0);
        }

        else{
            printf("In father process\n");
            child = waitpid(child1,NULL,0);
            //阻塞式等待
            if(child == child1){
                printf("child1 exit now\n");
            }
            else{
                printf("some error occured\n");
            }

            do{
                child = waitpid(child2,NULL,WNOHANG);
                //非阻塞式等待
                if(child == 0){
                    printf("Child2 has not exited\n");
                    sleep(1);
                }
            }while(child==0);

            if(child == child2){
                printf("child2 exit now\n");
            }
            else{
                printf("some error occured\n");
            }
        }
    }

    exit(0);
}
