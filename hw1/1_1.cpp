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
		printf("The child is terminated success!!\n"); 
	}
	else{
		if( WIFSIGNALED( status ) ){
			int termsig = WTERMSIG( status ) ;
			printf("termsig = %d %d\n",status, termsig ) ;  
		}
	}
	check = false ; 
}


int main( int argc , char *argv[] ){
		
	signal( SIGCHLD, mySignal ) ; 
	pid_t pid = fork() ; 


	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
		execl( argv[1], NULL );
		exit( 0 ) ;
	}

	while( check ) ; 
	return 0 ; 
}
