#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QBitmap>
#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include "MyWidget.h"
#include "Miku.h"
#include "windows.h"

Windows *win ; 
bool isFinished ; 

void *liveDetect( void *t ){
	while( !isFinished ){
		int x , y  ; 
		x = win->getMikuX() ; 
		y = win->getMikuY() ;  
		if( win->isInRange( x , y ) ){
			win->setMikuSpeed( 10 ) ;  
		}
		else	win->setMikuSpeed( 0 ) ; 
	}
	QCoreApplication::exit() ; 
	pthread_exit( NULL ) ; 
}

int main( int argc , char **argv ){

	QApplication app( argc , argv ) ; 

	pthread_t thread ; 
	win = new Windows() ; 
	pthread_create( &thread, NULL , liveDetect, NULL ) ;   
	
	win->show() ;   	
	return app.exec(); 
}	
