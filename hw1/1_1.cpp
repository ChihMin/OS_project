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


	pid_t childPid = wait( &status ) ; 	

	if( WIFEXITED( status ) ){
	//	printf("The child is terminated success!!\n"); 
		printf("Child %d exited with exit code %d.\n", (int)childPid, WEXITSTATUS(status));
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
		
	signal( SIGCHLD, mySignal ) ; 
	pid_t pid = fork() ; 
	signal( SIGALRM, sayHello ) ; 

	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
		execl( argv[1], NULL );
		exit( 1 ) ;
	}

	while( check ) ; 
	return 0 ; 
}
