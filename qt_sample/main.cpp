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
#include <QMessageBox>
#include "MyWidget.h"
#include "Miku.h"
#include "windows.h"

Windows *win ; 
bool isFinished ; 
int exitType = 0 ; 

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
				exitType = 1 ;
				win->setMikuSpeed( 0 ) ; 
			}
			else{
				printf("\n=================\n");
				printf("You Lose!!!\n"); 
				isFinished = true ; 
				printf("==================\n");
				exitType = 2 ;
				win->setMikuSpeed( 0 ) ; 
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
	  
	app.exec();
	if( exitType == 1 ){
		QMessageBox::warning( win , "Warning",
	            "Oh! <b>You Win!!!!!!</b>",
				            QMessageBox::Yes, QMessageBox::Yes);
	}
	else if( exitType == 2 ){
	QMessageBox::warning( win , "Warning",
	            "Oh! <b>You Lose!!!!!</b>",
				            QMessageBox::Yes, QMessageBox::Yes);}
	return  0 ;
}	
