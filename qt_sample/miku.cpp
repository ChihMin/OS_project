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
	x = 0, y = 0 ;

	repaint() ; 
/*	
	for(int i = 0; i < 5 ; ++i ){
		woods[i] = new MyWidget( 0, i * 100 , this ) ; 
	}
*/	
	//widget = new MyWidget( this ) ; 	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	//timer->start( 10 ) ;     
}
