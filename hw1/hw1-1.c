#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
pid_t pid;
int errno;
int check;

void getSignal(int signo){
	int status;
	pid = wait(&status);
	
	
	int i,j =0;
	int k,l =0;
	printf("YAYA!! status is %d\n",WUNTRACED ) ; 
	
	i = WIFEXITED(status);
	l = WTERMSIG(status);
	
		
	printf("termsig = %d\n",l);
printf("terminal signal : %d\n",i);
	if(i>0){
		
		 printf("-------- CHILD PROCESS END --------\n");
		 printf("Receive a SIGCHLD signal\n\n");

		 printf("Normal termination with exit status = %d \n",WEXITSTATUS(status));
		 check = 1;	

	}
	else{
		
		k = WIFSIGNALED(status);

		if(k>0){
			printf("Receive a SIGCHLD signal\n\n");
			
			printf("------ERROR DETECTED-------\n");
			l = WTERMSIG(status);
			switch(l){
				
				case 1: printf("CHILD PROCESS Hangup detected on controlling termainal\nor death of controlling process");break;
				case 2: printf("CHILD PROCESS Interrupt from keyboard\n");break;
				case 3: printf("CHILD PROCESS Quit from keyboard\n");break;
				case 4: printf("CHILD PROCESS Illegal Instruction\n");break;
				case 6: printf("CHILD PROCESS Abort signal from abort(3)\n");break;
				case 8: printf("CHILD PROCESS Floating point exception)\n");break;
				case 9: printf("CHILD PROCESS Kill signal\n");break;
				case 11: printf("CHILD PROCESS Invaild memory reference\n");break;
				case 13: printf("CHILD PROCESS Broken pipe: write to pipe with no readers\n");break;
				case 14: printf("CHILD PROCESS Timer signal from alarm(2)\n");break;
				case 15: printf("CHILD PROCESS Termination signal\n");break;
			}
			printf("CHILD PROCESS EXECUTION FAILED\n");
			check = 1;
		}



	}	
}

void alarm_test( int sig ){
	printf("Yes!! I got it !!\n" ) ;
}


int main(int argc,char *argv[]){
	
	printf("process fork!!\n");
	printf("Child process executes This program!\n");
	printf("Hello I'm parent process ,my pid = %d\n\n",pid);
	signal(SIGCHLD,getSignal);
	pid_t pid = fork() ; 	
	if( pid == 0 ){
		printf("-------process begin-------\n");
		signal( SIGALRM, alarm_test ) ; 
		execl(argv[1],0);
		//exit( 0 ) ;
	}

	while(check!=1){}
	exit( 0 ) ;
}	
