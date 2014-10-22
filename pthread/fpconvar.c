#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define NUM_THREAD 3

int isPrime ; // If a number is prime, let isPrime = 1	  
int isFinished = 0 ;	// If count is finished, isFinished = 1 ; 
int lastPrime = 2 ;	// lastprime is used to record last prime < p appearing. 
int p = 2 ; 
pthread_mutex_t count_mutex ;	// thread mutex  
pthread_cond_t count_threshold_cv ; // thread condition variable 
int TCOUNT, COUNT_LIMIT ; // TCOUNT is the limit of p   
int Signal = 0 ;	// Signal is used to record whether signal is sent or not

void *inc_count( void *t ){
	int i , j ; 
	int my_id = (int)t ; // Thread ID 2 3 
	int result ; // Is used to delay. 
	

	while( p < TCOUNT ){ 
		pthread_mutex_lock( &count_mutex ) ;  
		if( isFinished ){							// if while loop is finished
			pthread_mutex_unlock( &count_mutex ) ;	// unlock p 
			pthread_exit( NULL ) ;					// exit thread 
		}	  
		
		if( isPrime	)	lastPrime = p ;		// if lastnumber is prime, lastprime = p  
		p++;							// let p add 1 first 
		
		isPrime = 1 ;					// If p is prime, then isPrime = 1
		for(int i=2;i < p ;++i ){		// Judge whether p is prime 
			if( !( p % i )){
				isPrime = 0 ; 
				break; 
			}
		}

		printf("prime_count(): thread %d, p = %d\n",my_id, p ) ; 
		if( isPrime )	printf("prime_count(): thread %d, find prime = %d\n",my_id, p);
		
		if( !Signal && isPrime && p >= COUNT_LIMIT ){
			// if signal is not sent and p is prime and p >= COUNT_LIMIT 
			printf("prime_count(): thread %d, prime = %d prime reached.\n", my_id, p) ;

			pthread_cond_signal( &count_threshold_cv ) ; // sent signal to watch() ;  
			usleep( 1000 ) ; 
			printf("Just send signal.\n") ;  
			Signal = 1 ;	// Signal has been sent 
		}	

		if( p >= TCOUNT ){	
			isFinished = 1 ;	// is p is finished 
			pthread_mutex_unlock( &count_mutex ) ; // unlock  p 
			usleep( 200 ) ;						//delay
			continue ;							// continue 
		} 
		pthread_mutex_unlock( &count_mutex ) ; // unlock 	
		usleep( 200 ) ; 
	}
	usleep( 1000 ) ; 
	pthread_exit( NULL ) ; 
}

void *watch_count( void *t ){
	int i , j ; 
	int my_id = (int)t ;	// my_id = 1
	
	printf("Starting Watch_count(): thread %d, p = %d Going to wait...\n",my_id,p ) ; 
	pthread_mutex_lock( &count_mutex ) ;	// lock
	if( p <= COUNT_LIMIT ){	
		pthread_cond_wait( &count_threshold_cv, &count_mutex ) ; // wait signal 
															// let mutex unlock	
		printf("watch_count(): thread %d Conditional signal received. p = %d\n",my_id ,p);
		printf("watch_count(): thread %d Updating the value of p...\n", my_id ) ;
		printf("the lastest prime found before p = %d\n", lastPrime ) ;  
		printf("watch_count(): thread %d count p now = %d\n", my_id, p = p + lastPrime ) ;
		
		if( p >= TCOUNT )	isFinished = 1 ;	// if p >= TCOUNT after adding 
	}
	pthread_mutex_unlock( &count_mutex ) ;	//unlock 
	pthread_exit( NULL ) ;  
}

int main( int argc, char *argv[] ){
	
	TCOUNT = atoi( argv[1] ) ;	// trans string to num TCOUNT
	COUNT_LIMIT = atoi( argv[2] ) ; 

	pthread_t threads[NUM_THREAD] ; 
	int rc ; 
	int t1 = 1 , t2 = 2 , t3 = 3 ; 
	
	pthread_mutex_init( &count_mutex, NULL ) ;
	pthread_cond_init( &count_threshold_cv , NULL ) ; 

	pthread_create( &threads[0], NULL, watch_count, (void*)t1 ) ; 
	usleep( 200 ) ; 	//delay let thread 1 to listen signal of thread 2 3
	pthread_create( &threads[1], NULL, inc_count, (void*)t2 ) ; 
	pthread_create( &threads[2], NULL, inc_count, (void*)t3 ) ; 

	
	int i ;  
	for(i = 0; i < NUM_THREAD; ++i ){
		pthread_join( threads[i], NULL ) ;	 // join the pthread 
	}
	printf("Main() : Waited and joined with %d threads. Final value of count = %d\n", NUM_THREAD, p ) ; 
	
	pthread_mutex_destroy( &count_mutex) ;	// destroy mutex
	pthread_cond_destroy( &count_threshold_cv ) ; // destroy condition 
	pthread_exit( NULL ) ;	//exit 
}
