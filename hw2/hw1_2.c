#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#define ROW 15
#define COLUMN 50 
#define NUM_THREAD 15

pthread_mutex_t map_mutex ;	// thread mutex  
pthread_cond_t map_cond ; // thread condition variable 
//pthread_mutex_lock( &mutex ) ; 
//pthread_mutex_unlock( &mutex ) ; 
//pthread_cond_signal( &count_threshold_cv, &mutex  ) ; 
//pthread_cond_wait( &count_threshold_cv, &mutex ) ;
char map[ROW][COLUMN] ; 
int woods[ROW];

void *wood_move( void *t ){
	int my_id = (int)t ; 
	while( 1 ){

		if( my_id % 2 )	woods[my_id] = ( woods[my_id] + 1 ) % (COLUMN - 1) ; 
		else{
			woods[my_id] = woods[my_id] - 1 ;  ;
			if( woods[my_id] < 0 )	woods[my_id] += (COLUMN - 1 ) ; 
		}
		pthread_mutex_lock( &map_mutex ) ; 
		printf("\033[0;0H\033[2J");
		
		int i , j ; 
		for(j = 0; j < COLUMN - 1; ++j ) map[my_id][j] = ' ' ;
		map[my_id][COLUMN-1] = 0 ;    	
		for(i = 0, j = woods[my_id]; i < 7; ++i, ++j){
			map[my_id][ j % (COLUMN - 1) ] = '=' ; 
		}
		 
		for( i = 0; i < ROW; ++i)	puts( map[i] ); 
		pthread_mutex_unlock( &map_mutex ) ; 
		usleep(  (rand() % 20 ) * 10000 ) ;
	}
	pthread_exit( NULL ) ; 
}

int main( int argc, char *argv[] ){
	srand( time( 0 ) ) ; 
	pthread_t threads[NUM_THREAD] ; 
	
	pthread_mutex_init( &map_mutex, NULL ) ;
	pthread_cond_init( &map_cond , NULL ) ; 
	memset( map , 0, sizeof( map ) ) ;
	
	printf("\e[?25l") ; 
	int i , j ; 
	for( i = 0; i < ROW; ++i ){	
		for(j = 0; j < COLUMN - 1; ++j )	map[i][j] = ' ' ;  
		woods[i] = i ; 
	}

	for(i = 0; i < NUM_THREAD; ++i ){
		pthread_create( &threads[i], NULL, wood_move, (void*)i ) ;  
	}
	
	pthread_mutex_destroy( &map_mutex) ;	// destroy mutex
	pthread_cond_destroy( &map_cond ) ; // destroy condition 
	pthread_exit( NULL ) ;	//exit 
}
