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
		int x , y  , speed ;
		x = win->getMikuX() ; 
		y = win->getMikuY() ;  
		
		int pos = win->isInRange( x , y ) ;
		if( pos ){	
			speed = win->getWoodSpeed( pos ) ;  
			win->setMikuSpeed( speed ) ;  
		}
		else{	
			if( y + 200 > 500 )  win->setMikuSpeed( 0 ) ; 
			else if( y + 200 < 100 ){
				printf("\n=================\n");
				printf("You Win!!!\n"); 
				printf("==================\n");
				isFinished = true ; 
			}
			else{
				printf("\n=================\n");
				printf("You Lose!!!\n"); 
				isFinished = true ; 
				printf("==================\n");
			}
		}
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
