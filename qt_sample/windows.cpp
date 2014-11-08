#include "Miku.h"
#include "MyWidget.h"
#include "windows.h"
#include <pthread.h>
#include <unistd.h>
/*
struct ReadParams{
	MyWidget *wood ; 
	Windows *win ; 
	int id ; 
} ; 

void *create_wood( void *context ){
	struct ReadParams *read = (struct ReadParams*)&context ; 
	read->wood = new MyWidget( 0 , read->id * 100 , read->win ) ;  
	pthread_exit( NULL ) ; 
}
*/
Windows::Windows( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 1366, 768 ) ;	
/*
	struct ReadParams params[10] ;
	pthread_t threads[10] ; 
*/
	for(int i = 1;i <= 5; ++i ){	
		woods[i] = new MyWidget( 0 , i * 100 ,  this ) ; 
/*		params[i].wood = woods[i] ;
		params[i].id = i ;  
		params[i].win = this ; 
		pthread_create( &threads[i] , NULL, create_wood, &params );  
*/	
		
	}
	miku = new Miku( this ) ;
//	pthread_exit( NULL ) ;  
}

void Windows::keyPressEvent( QKeyEvent *event ){
	miku->keyPressEvent( event ) ; 
}
