#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define NUM_THREAD 3

int isPrime ;	  
int isFinished = 0 ;
int lastPrime = 2 ;
int lastThread = -1;
int p = 2 ; 
pthread_mutex_t count_mutex ; 
pthread_cond_t count_threshold_cv ; 
int *visit ; 
int TCOUNT, COUNT_LIMIT ; 
int Signal = 0 ;

void *inc_count( void *t ){
	int i , j ; 
	int my_id = (int)t ; 
	int result ; 
	//int visit[100] ; 
	
	//memset( visit, 0 , sizeof( visit ) ) ; 

	while( p < TCOUNT ){
		pthread_mutex_lock( &count_mutex ) ;  
		if( isFinished ){	
			pthread_mutex_lock( &count_mutex ) ; 
			pthread_exit( NULL ) ; 
		}	  
		
		if( isPrime	)	lastPrime = p ; 
		p++;
		
		// If p is prime, then isPrime = 1
		isPrime = 1 ;
		for(int i=2;i < p ;++i ){
			if( !( p % i )){
				isPrime = 0 ; 
				break; 
			}
		}

		printf("prime_count() : thread %d, p = %d\n",my_id, p ) ; 
		if( isPrime )	printf("prime_count() : thread %d, find prime %d\n",my_id, p);
		
		if( !Signal && isPrime && p >= COUNT_LIMIT ){
			printf("prime_count() : thread %d, prime = %d prime reached!\n", my_id, p) ;

			pthread_cond_signal( &count_threshold_cv ) ; 
			printf("Just send signal!!!\n") ;  
			Signal = 1 ;
		}

		if( p >= TCOUNT ){
			isFinished = 1 ;
			pthread_mutex_unlock( &count_mutex ) ; 
			for( j = 0; j < 100000; ++j ) result += (double)rand() ;   
			continue ; 
		} 
		pthread_mutex_unlock( &count_mutex ) ; 	
		for( j = 0; j < 100000; ++j ) result += (double)rand() ;   

	}
	pthread_exit( NULL ) ; 
}

void *watch_count( void *t ){
	int i , j ; 
	int my_id = (int)t ;
	
	printf("Starting Watch_count() : thread %d, p = %d Going to wait...\n",my_id,p ) ; 
	pthread_mutex_lock( &count_mutex ) ; 
	if( p < COUNT_LIMIT ){
		printf("watch_count() : thread %d going into wait... \n", my_id) ; 
		
		pthread_cond_wait( &count_threshold_cv, &count_mutex ) ; 
		
		printf("watch_count() : thread %d Conditional signal received. p = %d\n",my_id ,p);
		printf("watch_count() : thread %d Updating the value of p....\n", my_id ) ;
		printf("the lastest prime found before p = %d\n", lastPrime ) ;  
		printf("watch_count() : thread %d count p now = %d\n", my_id, p = p + lastPrime ) ;
		
		if( p >= TCOUNT )	isFinished = 1 ;
	}
	pthread_mutex_unlock( &count_mutex ) ;
	pthread_exit( NULL ) ;  
}

int main( int argc, char *argv[] ){
	
	TCOUNT = atoi( argv[1] ) ; 
	COUNT_LIMIT = atoi( argv[2] ) ; 

	pthread_t threads[NUM_THREAD] ; 
	int rc ; 
	int t1 = 1 , t2 = 2 , t3 = 3 ; 
	
	pthread_mutex_init( &count_mutex, NULL ) ;
	pthread_cond_init( &count_threshold_cv , NULL ) ; 

	pthread_create( &threads[1], NULL, inc_count, (void*)t1 ) ; 
	pthread_create( &threads[2], NULL, inc_count, (void*)t2 ) ; 
	pthread_create( &threads[0], NULL, watch_count, (void*)t3 ) ; 
	
	int i ;  
	for(i = 0; i < NUM_THREAD; ++i ){
		pthread_join( threads[i], NULL ) ; 
	}
	printf("Main() : Waited and joined with %d threads. Final value of count = %d\n", NUM_THREAD, p ) ; 
	
	pthread_mutex_destroy( &count_mutex) ;
	pthread_cond_destroy( &count_threshold_cv ) ; 
	pthread_exit( NULL ) ;
}
