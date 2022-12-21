#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
char message[25] = "Cela provient d'un tube"; 
int main() 
{ 
    /* 
       * communication PERE --> FILS par pipe 
     */  
    int p[2];  
    if (pipe(p) == -1) { 
        fprintf(stderr, "erreur ouverture pipe\n"); 
        exit(1); 
    } 
    if (fork() == 0) {          /* fils */ 
        char c; 
        close(p[1]); 
		printf("hello from child\n");
        while (read(p[0], &c, 1) != 0) 
            printf("%c|", c); 
        close(p[0]); 
		printf("hello again from child\n");
        exit(0); 
    } else {
		/* suite pere */ 
		char	*str[] = {"/bin/bash", "-c", "ls -al", NULL};
        close(p[0]); 
        //execve(str[0], str, 0);
		printf("hello from parent\n");
		close(p[1]); 
        exit(0); 
    } 
}
