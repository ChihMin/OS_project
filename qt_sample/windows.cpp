#include "Miku.h"
#include "MyWidget.h"
#include "windows.h"
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime> 

Windows::Windows( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 1366, 768 ) ;
	logCount = 5 ;
	mikuSpeed = 0 ;	
	srand( time( 0 )  )  ; 
	for(int i = 1; i <= logCount; ++i )	
			length[i] = rand() % 5 + 4 ;  
	
	for(int i = 1;i <= logCount; ++i ){	
		woods[i] = new MyWidget( 0 , i * 100 , length[i],  this ) ; 
	}
	
	logCount = 7 ; 
	for(int i = 6 ; i <= logCount; ++i )
		length[i] = rand() % 10 + 4 ; 
	for( int i = 6; i <= logCount; ++i)
		woods[i] = new MyWidget( length[i-5] * 100 + 100 , ( i - 5 ) * 100 , length[i],  this ) ; 
	
	miku = new Miku( this ) ;  
}

int Windows::getLogCount(){
	return logCount ; 
}

void Windows::keyPressEvent( QKeyEvent *event ){
	miku->keyPressEvent( event ) ; 
}

int Windows::getMikuX(){
	return miku->getX() ; 
}

int Windows::getMikuY(){
	return miku->getY() ; 
}

int Windows::getWoodX( int pos ){
	return woods[pos]->getX() ; 
}

int Windows::getWoodY( int pos ){
	return woods[pos]->getY() ; 
}

void Windows::changeMiku( int x , int y){
	miku->changeMiku( x , y ) ; 
}

void Windows::setMikuSpeed( int _speed ){
	mikuSpeed = _speed ; 
	miku->setSpeed( _speed ) ; 
}

bool Windows::isInRange( int x , int y ){
	y += 200 ;
	int lx = x + 200 ;  
	int rx = x + 165 ; 
	for( int i = 1 ; i <= logCount; ++i) {
		int nx = woods[i]->getX() ; 
		int ny = woods[i]->getY() ; 
	//	printf("( %d , %d ) ", nx, ny ) ; 	
		if( y == ny ){
			if( lx >= nx && lx <= nx + 100 * length[i] )	return true ;
			else if( rx >= nx && rx <= nx + 100 * length[i] )	return true ; 
		 }
	}//printf(" miku : ( %d ,%d )\n", x, y ) ; 
	return false ; 
}
