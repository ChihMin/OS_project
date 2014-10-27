#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <termios.h>
#include <fcntl.h>
#define ROW 15
#define COLUMN 50 
#define NUM_THREAD 20

struct Node{
	int x , y; 
	Node( int _x , int _y ) : x( _x ) , y( _y ) {}; 
	Node(){} ; 
} frog ; 

pthread_mutex_t map_mutex ;	// thread mutex  
pthread_cond_t map_cond ; // thread condition variable 
//pthread_mutex_lock( &mutex ) ; 
//pthread_mutex_unlock( &mutex ) ; 
//pthread_cond_signal( &count_threshold_cv, &mutex  ) ; 
//pthread_cond_wait( &count_threshold_cv, &mutex ) ;
char map[ROW+10][COLUMN] ; 
int woods[ROW+10] ;
int speed[ROW+10] ; 


int kbhit(void){
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);

	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}
void *wood_move( void *t ){
	int my_id = *((int*)&t) ; 
	while( 1 ){

		if( my_id % 2 )	woods[my_id] = ( woods[my_id] + 1 ) % (COLUMN - 1) ; 
		else{
			woods[my_id] = woods[my_id] - 1 ;  ;
			if( woods[my_id] < 0 )	woods[my_id] += (COLUMN - 1 ) ; 
		}
		pthread_mutex_lock( &map_mutex ) ; 
		
		if( kbhit() ){
			char dir = getchar() ; 
			if( dir == 'w' || dir == 'W' )	frog.x-- ;
			else if( dir == 'a' || dir == 'A' )	frog.y-- ;
			else if( dir == 'd' || dir == 'D' )	frog.y++ ; 
			else if( dir == 's' || dir == 'S' )	frog.x++ ;  
			//else if( dir == 'q' || dir == 'Q' )	isRunngin = false ;
		}

		int i , j ; 
		for(j = 0; j < COLUMN - 1; ++j ) map[my_id][j] = ' ' ;
		map[my_id][COLUMN-1] = 0 ;    	
		for(i = 0, j = woods[my_id]; i < 7; ++i, ++j){
			map[my_id][ j % (COLUMN - 1) ] = '=' ; 
		}
		 
		for( j = 0; j < COLUMN - 1; ++j )	
			map[ROW][j] = map[0][j] = '|' ;
		
		printf("\033[0;0H\033[2J");
		
		usleep( 1000 ) ;
		
		map[frog.x][frog.y] = '0' ;  
		for( i = 0; i <= ROW; ++i)	puts( map[i] );
		
		pthread_mutex_unlock( &map_mutex ) ; 
		usleep(  speed[my_id] * 3000 ) ;
	}
	pthread_exit( NULL ) ; 
}

int main( int argc, char *argv[] ){
	srand( time( 0 ) ) ; 
	pthread_t threads[NUM_THREAD+2] ; 
	
	pthread_mutex_init( &map_mutex, NULL ) ;
	pthread_cond_init( &map_cond , NULL ) ; 
	memset( map , 0, sizeof( map ) ) ;
	
	printf("\e[?25l") ; 
	int i , j ; 
	for( i = 1; i < ROW; ++i ){	
		for( j = 0; j < COLUMN - 1; ++j )	map[i][j] = ' ' ;  
		woods[i] = i ;
		speed[i] = rand() % 20 + 10  ;  
	}
	
	frog = Node( ROW, (COLUMN-1) / 2 ) ; 
	for( j = 0; j < COLUMN - 1; ++j )	
		map[ROW][j] = map[0][j] = '|' ;
	puts( map[ROW] ) ;  
	
	//Here is used to create frog control thread and woods thread !!
	int tfrog = NUM_THREAD ; 
	//pthread_create( &threads[NUM_THREAD], NULL, frog_control, (void*)tfrog ) ; 
	for(i = 1; i < NUM_THREAD; ++i ){
		pthread_create( &threads[i], NULL, wood_move, (void*)i ) ;  
		usleep( 200 ) ; 
	}
	
	pthread_mutex_destroy( &map_mutex) ;	// destroy mutex
	pthread_cond_destroy( &map_cond ) ; // destroy condition 
	pthread_exit( NULL ) ;	//exit 
}
