#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>
#include <errno.h>
using namespace std;


int main( int argc , char *argv[] ){
	int status ; 

	printf("Process fork!\n");
	printf("Child Process executes Test program!!\n");
	
	pid_t mypid = getpid() ; 
	printf("Hello! I'm parent process! My pid is %d\n",mypid);
	pid_t pid = fork() ;	
	

	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
		printf("---------CHILD PROCESS BEGIN---------\n");
		execl( argv[1] ,NULL );
		exit( 1 ) ;
	}
	else{
		pid_t x ; 
		x = wait( &status ); 
		//printf("Signal: %d\nStatus: %d\nEXITED: %d\nx: %d\n", WIFSIGNALED( x ), status, WIFEXITED( x ) ,x) ;
		int ifSig = WIFSIGNALED( status ) ; 
		int term = WTERMSIG( status );

		printf("%d %d\n",ifSig, term) ; 

		printf("---------CHILD PROCESS END---------\n");
		printf("Receiving the SIGCHLD signal\n\n");
		printf("Get the status is %d\n",status ) ;
		exit( 0 ) ;
	}
	//for(int i=0;i<10;++i)	printf("=");

	return 0 ; 
}
