#include "MyWidget.h"
#include <ctime>
#include <cstdlib>

void MyWidget::setSpeed( int _speed ){
	speed = _speed ; 
}

int MyWidget::getSpeed(){
	return speed ; 
}

int MyWidget::getX(){
	return x; 
}

int MyWidget::getY(){
	return y ; 
}

void MyWidget::setPosition(){
	repaint() ;
	x = x + speed  ;
	if( x >= 1366 ) x = -length ;  
	emit timeout() ; 
}

void MyWidget::paintEvent( QPaintEvent *event ){
	QPixmap pixImg( "onion.png" ) ; 
	QPainter painter( this ) ;
	painter.drawPixmap( x , y , length  , 100 , pixImg ) ; 
}

MyWidget::MyWidget( QWidget *parent ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ;	 	
	x = y = 0 ;
	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 10 ) ;     
}

MyWidget::MyWidget( int _x, int _y, int _length , QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ;	 	
	x = _x , y = _y ; 
	speed = 10 ; 
	length = _length * 100 ; 
	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;

	timer->start( 20 ) ;     
}

