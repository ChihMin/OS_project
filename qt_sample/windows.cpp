#include "Miku.h"
#include "MyWidget.h"
#include "windows.h"
#include <pthread.h>
#include <unistd.h>
Windows::Windows( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 1366, 768 ) ;
	logCount = 5 ; 
	for(int i = 1;i <= logCount; ++i ){	
		woods[i] = new MyWidget( 0 , i * 100 ,  this ) ; 
	}
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
