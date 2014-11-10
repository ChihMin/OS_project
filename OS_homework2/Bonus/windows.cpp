#include "Miku.h"
#include "MyWidget.h"
#include "windows.h"
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime> 
#include <QMessageBox>

Windows::Windows( QWidget *parent ) : QWidget( parent ) {
	
	setFixedSize( 1366, 768 ) ;
	logCount = 5 ;
	
	mikuSpeed = 0 ;	
	speed = 10 ; 

	srand( time( 0 )  )  ; 
	for(int i = 1; i <= logCount; ++i )	
			length[i] = rand() % 5 + 4 ;  
	
	for(int i = 1;i <= logCount; ++i ){	
		woods[i] = new MyWidget( 0 , i * 100 , length[i],  this ) ; 
	}
	
	miku = new Miku( this ) ;  
	slider = new QSlider( Qt::Horizontal, this ) ;
	slider->setRange( 10 , 40 ) ; 
	slider->setValue( 10 ) ; 
	slider->setGeometry( 20 , 730 , 400, 30 ) ; 
	
	connect(slider , SIGNAL( valueChanged( int ) ), this, SLOT( speedChanges( int ) ) ); 
}

void Windows::paintEvent( QPaintEvent *event ){	
	QPixmap pixImg("background.jpg"); 
	QPainter painter( this ) ; 
	painter.drawPixmap( 0, 0, pixImg )  ; 
}

void Windows::speedChanges( int n_speed ){
	if( n_speed != speed ){
		speed = n_speed ;
		for( int i = 1; i <= logCount; ++i ){
			woods[i]->setSpeed( n_speed ) ;  
		}
		emit valueChanged( n_speed ) ;  
	}
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

int Windows::getWoodSpeed( int pos ){
	return woods[pos]->getSpeed() ; 
}

void Windows::setMikuSpeed( int _speed ){
	mikuSpeed = _speed ; 
	miku->setSpeed( _speed ) ; 
}

int Windows::isInRange( int x , int y ){
	y += 200 ;
	int lx = x + 200 ;  
	int rx = x + 165 ; 
	for( int i = 1 ; i <= logCount; ++i) {
		int nx = woods[i]->getX() ; 
		int ny = woods[i]->getY() ; 
	//	printf("( %d , %d ) ", nx, ny ) ; 	
		if( y == ny ){
			if( lx >= nx && lx <= nx + 100 * length[i] )	return i ;
			else if( rx >= nx && rx <= nx + 100 * length[i] )	return i ; 
		 }
	}//printf(" miku : ( %d ,%d )\n", x, y ) ; 
	return false ; 
}
