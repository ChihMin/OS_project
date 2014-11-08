#include "MyWidget.h"

void MyWidget::setPosition(){
	repaint() ;
	pos = pos + 4 ; 
	emit timeout() ; 
}

void MyWidget::paintEvent( QPaintEvent *event ){
	QPixmap pixImg( "miku.png" ) ; 
	QPainter painter( this ) ; 
	painter.drawPixmap( pos, 0  , pixImg ) ; 
}

MyWidget::MyWidget( QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ;	 	
	pos = 0 ; 
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 7 ) ;     
}
