#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    pid_t pid = fork(); 
    if(pid == -1){
        printf("Error : Fork() is failed ");
        exit(1);
    }
    if(pid == 0){
        printf("Child process is running...\n");
        while(1){
            printf("child is working....");
            sleep(1);
        }
    }
    else{
        printf("Parent process started\n");
        sleep(2);
        if(kill(pid,SIGSTOP)==-1){
             perror("Failed to suspend child process");
            exit(1);
        }

        printf("Parent has suspended the child process\n");
        sleep(2);
        if(kill(pid,SIGCONT)==-1){
            perror("Failed to resume child process");
            exit(1);
        }

        printf("Parent has resumed the child process\n");
        sleep(2);

        if(kill(pid,SIGKILL)==-1){
            perror("Failed to terminate the child process");
        }
        printf("Parent has Terminated the child\n");

        if(wait(NULL)==-1){
            printf("failed to wait for child..");
        }

        printf("Parent process is finished");


    }
    
return 0;
}