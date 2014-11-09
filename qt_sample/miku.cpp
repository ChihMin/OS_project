#include "Miku.h"

void Miku::setSpeed( int _speed ){
	speed = _speed ; 
}

void Miku::changeMiku( int _x , int _y ){
	x = _x, y = _y ; 
	repaint() ; 
}

void Miku::setPosition(){
	repaint() ;
	x = x + speed  ;
	if( x >= 1367 )	x = -265;  
	emit timeout() ; 
}

void Miku::paintEvent( QPaintEvent *event ){
	QPixmap pixImg( "miku.png" ) ; 
	QPainter painter( this ) ; 
	painter.drawPixmap( x, y  , pixImg ) ; 
}

int Miku::getX(){
	return x ; 
}

int Miku::getY(){
	return y ; 
}	

void Miku::keyPressEvent( QKeyEvent *event ){
	char c = char( event->key() ) ;
	int dis = 100 ; 
	printf("%c ",c) ;  
	if( c < 95 ) c += 32 ; 
	
	if( c == 'w' ) y -= dis ; 
	else if( c == 'd' ) x += dis; 
	else if( c == 'a' )	x -= dis ; 
	else if( c == 's' ) y += dis ; 
	else if( c == 'q' ){
		QCoreApplication::exit() ;  
	}
	 
	repaint() ; 
}

Miku::Miku( QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ; 
	x = 500 , y = 400  ;
	speed = 0 ;
	repaint() ; 

	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 20 ) ;     
}
