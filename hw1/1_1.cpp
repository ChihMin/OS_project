#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>
#include <errno.h>
using namespace std;


bool check = true; 

void mySignal( int sig ){
	int status; 


    printf("Hello! I'm parent, my pid is %d\n\n",getpid() ) ; 
	pid_t childPid = wait( &status ) ; 	
    printf("Receving the SIGSHLD signal\n\n") ; 

	if( WIFEXITED( status ) ){
		printf("Normal terminationwith exit status %d.\n", WEXITSTATUS(status));
	}
	else if( WIFSIGNALED( status ) ){
		int termsig = WTERMSIG( status ) ;
		printf("termsig = %d\n", termsig ) ; 
	}
	else if( WIFSTOPPED( status ) ){
		printf("Child %d was stopped by signal %d.\n", (int)childPid, WSTOPSIG(status));
	}
	
	check = false ; 
}


void sayHello( int sig ){
	printf("It's time to say hello !!\n") ; 
}

int main( int argc , char *argv[] ){
    printf("Process fork!!\n") ; 		
	signal( SIGCHLD, mySignal ) ; 
	pid_t pid = fork() ; 
	//signal( SIGALRM, sayHello ) ; 

	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
	    printf("Child process execute Test program!!\n") ; 	
		execvp( argv[1], NULL );
		exit( 1 ) ;
	}

	while( check ) ; 
	return 0 ; 
}
