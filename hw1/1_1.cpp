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
	pid_t pid = fork() ;	
	pid_t mypid = getpid() ; 
	
	for(int i=0;i<10;++i)	printf("=");
	printf("\n");
	printf("I'm parent!! My pid is %d\n",mypid);
	printf("And my child's pid = %d\n",pid);

	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
		printf("=====\n");
		execl( argv[1] ,NULL );
		exit( 1 ) ;
	printf("=====\n");
	}
	else{
		wait( &status ); 
		//printf("Child Complete\n");
		printf("Signal: %d\nStatus: %d\nEXITED: %d\n", WIFSIGNALED(status), status, WIFEXITED( status ) ) ;
		 
		exit( 0 ) ;
	}
	for(int i=0;i<10;++i)	printf("=");

	return 0 ; 
}
