#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>
#include <errno.h>
#include <vector>

using namespace std;

vector < pid_t > pid_list ;  
int cnt ; 
int programNumber ; 

void print_signal( int termsig ); 
void mySignal( pid_t childPid ) ; 
void process_dfs( int step, char *argv[], vector <pid_t > &v ) ; 

	
int main( int argc , char *argv[] ){
	programNumber = argc ;
	process_dfs( 0 , argv, pid_list ) ;  

	return 0 ; 
}

void process_dfs( int step , char *argv[], vector < pid_t > &v  ){
	if( step == programNumber - 1 ){	
		printf("****************************************\n\n");
		printf("Here is relationship between processes!!\n\n");
		v.push_back( getpid() ) ; 
		for(int i = 0; i < pid_list.size() - 1; i++ )
			printf("%d -> ",pid_list[i]);
		printf("%d\n\n", pid_list[pid_list.size()-1] ) ;  
		printf("*****************************************\n");
	}
	else{	 	
		v.push_back( getpid() ) ; 
		pid_t pid = fork() ; 
		
		if( pid < 0 ){
			printf("fork error\n");
			exit( -1 ) ;
		}
		else if( pid == 0 ){
			
			process_dfs( step + 1 , argv, v ) ; 

			printf("\n=================================================\n");
			printf("=================================================\n\n");
			printf("process fork!!\n") ; 		
			printf("child process execute test program!!\n") ; 	
			printf("hello! i'm parent, my pid is %d\n\n",getppid() ) ; 

			execl( argv[step+1], NULL );
			exit( 1 ) ;
		}
		else{	
			mySignal( pid ) ; 
		}
	}
}


void mySignal( pid_t childPid  ){
	int status; 
	waitpid( childPid, &status, 0  ) ; 	

	printf("\nReceving the SIGCHLD signal\n\n") ; 
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

}


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
		default:
			printf("Undefined signal\n");
			break; 
    }
}

