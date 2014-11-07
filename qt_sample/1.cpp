#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QBitmap>
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
/*	
	QVBoxLayout *layout = new QVBoxLayout( ) ;
	layout->addWidget( quit ) ;
	setLayout( layout ) ;
*/
}

MyWidget::MyWidget( QWidget *parent  ) : QWidget( parent ){
	setFixedSize( 1366, 768 ) ; 
	pos = 0 ; 
	quit = new QPushButton( tr("Quit") , this ) ;
	quit->setGeometry( 100, 100, 200 ,200 ) ; 
	quit->setFont( QFont("Times", 18, QFont::Bold  ) );
	
	timer = new QTimer() ; 
	connect( timer, SIGNAL( timeout() ), this, SLOT( setPosition() ) ) ;
	timer->start( 7 ) ;     
}

int main( int argc , char **argv ){

	QApplication app( argc , argv ) ; 

	MyWidget window ; 
	window.show() ; 	
	return app.exec(); 
}	
