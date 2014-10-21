#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define NUM_THREAD 3

int count = 0 ; 
pthread_mutex_t count_mutex ; 
pthread_cond_t count_threshold_cv ; 
int visit[1000] ; 

void *inc_count( void *t ){
	int i , j ; 
	int my_id = (int)t ; 
	int result ; 
	//int visit[100] ; 
	
	//memset( visit, 0 , sizeof( visit ) ) ; 

	for(i=0;i<20;++i){
		pthread_mutex_lock( &count_mutex ) ; 
		if( !visit[i] ){
			count++ ; 
			visit[i] = 1 ; 
		}
		
		if( count == 12 ){
			printf("inc_count() : thread %d, count = %d Threshold reached!\n", my_id, count) ;
			pthread_cond_signal( &count_threshold_cv ) ; 
			printf("Just send signal!!!\n") ;  
		}

		printf("inc_count() : thread %d, count = %d, i = %d, unlocking mutex\n",my_id, count, i ) ; 
		pthread_mutex_unlock( &count_mutex ) ; 

		//for( j = 0; j < 1000000; ++j ) result += (double)rand() ;  
	}
	pthread_exit( NULL ) ; 
}

void *watch_count( void *t ){
	int i , j ; 
	int my_id = (int)t ;
	
	printf("Starting Watch_count() : thread %d\n",my_id ) ; 
	pthread_mutex_lock( &count_mutex ) ; 
	if( count < 12 ){
		printf("watch_count() : thread %d going into wait... \n", my_id) ; 
		pthread_cond_wait( &count_threshold_cv, &count_mutex ) ; 
		printf("watch_count() : thread %d receive signal\n",my_id);
		//count += 125 ; 
		printf("watch_count() : thread %d, count now = %d\n", my_id, count ) ; 
	}
	pthread_mutex_unlock( &count_mutex ) ;
	pthread_exit( NULL ) ;  
}

int main( int argc, char *argv[] ){
	
	memset( visit , 0 ,sizeof( visit )  ) ; 

	pthread_t threads[NUM_THREAD] ; 
	int rc ; 
	int t1 = 1 , t2 = 2 , t3 = 3 ; 
	
	pthread_mutex_init( &count_mutex, NULL ) ;
	pthread_cond_init( &count_threshold_cv , NULL ) ; 

	pthread_create( &threads[0], NULL, inc_count, (void*)t1 ) ; 
	pthread_create( &threads[1], NULL, inc_count, (void*)t2 ) ; 
	pthread_create( &threads[2], NULL, watch_count, (void*)t3 ) ; 
	
	int i ;  
	for(i = 0; i < NUM_THREAD; ++i ){
		pthread_join( threads[i], NULL ) ; 
	}
	printf("Main() : Wait on %d threads, and count result is %d\n", NUM_THREAD, count ) ; 
	
	pthread_mutex_destroy( &count_mutex) ;
	pthread_cond_destroy( &count_threshold_cv ) ; 
	pthread_exit( NULL ) ;
}
