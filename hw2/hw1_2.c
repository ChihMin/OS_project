#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define NUM_THREAD 3

pthread_mutex_t count_mutex ;	// thread mutex  
pthread_cond_t count_threshold_cv ; // thread condition variable 
//pthread_mutex_lock( &mutex ) ; 
//pthread_mutex_unlock( &mutex ) ; 
//pthread_cond_signal( &count_threshold_cv, &mutex  ) ; 
//pthread_cond_wait( &count_threshold_cv, &mutex ) ;

int main( int argc, char *argv[] ){
	
	TCOUNT = atoi( argv[1] ) ;	// trans string to num TCOUNT
	COUNT_LIMIT = atoi( argv[2] ) ; 

	pthread_t threads[NUM_THREAD] ; 
	
	pthread_mutex_init( &count_mutex, NULL ) ;
	pthread_cond_init( &count_threshold_cv , NULL ) ; 

	pthread_create( &threads[0], NULL, watch_count, (void*)t1 ) ; 
	usleep( 200 ) ; 	//delay let thread 1 to listen signal of thread 2 3
	pthread_create( &threads[1], NULL, inc_count, (void*)t2 ) ; 
	pthread_create( &threads[2], NULL, inc_count, (void*)t3 ) ; 

	
	pthread_mutex_destroy( &count_mutex) ;	// destroy mutex
	pthread_cond_destroy( &count_threshold_cv ) ; // destroy condition 
	pthread_exit( NULL ) ;	//exit 
}
