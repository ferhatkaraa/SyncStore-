#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "child1.h"
#include "child2.h"
#include "child3.h"
#include "sinyal.h"
#include "storage.h"

int main() {

    pid_t pid;


    //Test signal function
    signal_function();


    
    printf("C Programi Baslatiliyor...\n");
    
    for (int i = 1; i <= 3; i++)
    {
        pid = fork();
        
        if (pid < 0) {
            perror("Fork basarisiz");
            exit(1);
        }
        else if  (pid==0){

        if (i == 1) {
            child1_function(i);
        } else if (i == 2) {
            child2_function(i);
        } else if (i == 3) {
            child3_function(i);
        }

        exit(0);
        }

    }
    
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }


    


    printf("Program Bitti.\n");


    return 0;
}


