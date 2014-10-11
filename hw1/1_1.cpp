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

void print_signal( int termsig ){
    printf("--------------- ERROR DETECTION ---------------\n") ; 
    printf("CHILD PROCESS ") ; 
    switch( termsig ){
        case SIGHUP:
            printf("Hangup detected on controlling terminal or death of controlling process\n");
            break; 
        case SIGINT:
            printf("Interrupt from keyboard\n");
            break ;
        case SIGQUIT:
            printf("Quit from keyboard\n");
            break;
        case SIGILL:
            printf("Illegal Instruction\n");  
            break ; 
        case SIGABRT:
            printf("Abort signal from abort(3)\n") ; 
            break ;
        case SIGFPE:
            printf("Floating point exception\n");
            break; 
        case SIGKILL:
            printf("Kill signal\n");
            break;
        case SIGSEGV:
            printf("Segmentation fault\n") ; 
            break;
        case SIGALRM:
            printf("Timer signal from alarm(2)\n");
            break ;
        case SIGTERM:
            printf("Termination signal\n");
            break;
        case SIGUSR1:
            printf("User-defined signal 1\n") ; 
            break; 
        case SIGUSR2:
            printf("User-defined signal 2\n") ; 
            break; 
        case SIGCONT:
            printf("Continue if stopped\n") ; 
            break; 
        case SIGSTOP:
            printf("Stop process\n") ; 
            break; 
        case SIGTSTP:
            printf("Stop typed at tty\n") ; 
            break; 
        case SIGTTIN:
            printf("tty input for background process\n") ;
            break; 
        case SIGTTOU:
            printf("tty output for background process\n") ; 
            break ; 
    }
}

void mySignal( int sig ){
	int status; 


	pid_t childPid = wait( &status ) ; 	
    printf("\nReceving the SIGSHLD signal\n\n") ; 

	if( WIFEXITED( status ) ){
		printf("Normal terminationwith exit status %d.\n", WEXITSTATUS(status));
	}
	else if( WIFSIGNALED( status ) ){
		int termsig = WTERMSIG( status ) ;
        print_signal( termsig ) ;
	    if( WCOREDUMP( status ) )
	        printf("CHILD PROCESS FAILED\n") ; 
	}
	else if( WIFSTOPPED( status ) ){
		printf("CHILD PROCESS  was stopped by signal %d\n", WSTOPSIG(status));
	}
    else{
        printf("Unexpected signal condition!!\n") ; 
    }

	check = false ; 
}

int main( int argc , char *argv[] ){
    printf("Process fork!!\n") ; 		
	printf("Child process execute Test program!!\n") ; 	
	
	signal( SIGCHLD, mySignal ) ; 
	pid_t pid = fork() ; 


	if( pid < 0 ){
		printf("fork error\n");
		exit( -1 ) ;
	}
	else if( pid == 0 ){
		execvp( argv[1], NULL );
		exit( 1 ) ;
	}
    else{ 
        printf("Hello! I'm parent, my pid is %d\n\n",getpid() ) ; 
    }

	while( check ) ; 
	return 0 ; 
}
