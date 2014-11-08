#include "MyWidget.h"

void MyWidget::setPosition(){
	repaint() ;
	x = x + 10 ;
	if( x >= 1366 ) x = -400 ;  
	emit timeout() ; 
}

void MyWidget::paintEvent( QPaintEvent *event ){
	QPixmap pixImg( "onion.png" ) ; 
	QPainter painter( this ) ; 
	painter.drawPixmap( x , y , pixImg ) ; 
}

MyWidget::MyWidget( QWidget *parent ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ;	 	
	x = y = 0 ;
	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 10 ) ;     
}

MyWidget::MyWidget( int _x, int _y , QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ;	 	
	x = _x , y = _y ; 
	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 7 ) ;     
}

