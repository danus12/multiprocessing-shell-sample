/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void child_function(int data[2]){
    int c;
    int rc;
    close(data[1]);
    while((rc=read(data[0],&c,1))>0){
        printf("Fils-> Lecture de données : ");
        putchar(c);
        printf("\n");
    }
    exit(0);
}
void parent_function(int data[2]){
    int c;
    int rc;
    close(data[0]);
    printf("Parent-> Entrez les données à envoyer : ");
    while((c=getchar())>0){
        rc=write(data[1],&c,1);
        if(rc==-1){
            perror("Parent erreur en écrite...");
        }
    }
    close(data[1]);
    exit(0);
}
int main()
{
    int pipe_data[2];
    int pid;
    int rc;

    rc = pipe(pipe_data);
    if(rc==-1){
            perror("pipe");exit(1);
    }
    pid = fork();
    switch(pid){
        case -1 :
            perror("fork");exit(1);
        case 0 :
            child_function(pipe_data);
        default :
            parent_function(pipe_data);
    }

}
