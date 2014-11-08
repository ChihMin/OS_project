#include "Miku.h"

void Miku::setPosition(){
	repaint() ;
	x = x + 4 ; 
	emit timeout() ; 
}

void Miku::paintEvent( QPaintEvent *event ){
	QPixmap pixImg( "miku.png" ) ; 
	QPainter painter( this ) ; 
	painter.drawPixmap( x, y  , pixImg ) ; 
}

void Miku::keyPressEvent( QKeyEvent *event ){
	char c = char( event->key() ) ;
	printf("%c ",c) ;  
	if( c < 95 ) c += 32 ; 
	
	if( c == 'w' ) y -= 50 ; 
	else if( c == 'd' ) x += 50; 
	else if( c == 'a' )	x -= 50 ; 
	else if( c == 's' ) y += 50 ; 
	else if( c == 'q' ){
	}
	 
	repaint() ; 
}

Miku::Miku( QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ; 
	x = 0, y = 0 ;
	
	widget = new MyWidget( this ) ; 	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 10 ) ;     
}
