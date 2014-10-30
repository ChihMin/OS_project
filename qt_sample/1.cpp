#include <QApplication>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QSlider>
#include <QLCDNumber>
#include <QWidget>
#include <QPainter>
#include <QBitmap>
#include <QtGui> 
#include <QtCore>
#include <QGraphicsItem>
#include <signal.h>
#include <sys/times.h>


class SuperItem : public QGraphicsItem{

public:
	SuperItem( QGraphicsItem *parent = NULL ) ; 	
		
protected:
	void paint( QPainter *painter, 
				const QStyleOptionGraphicsItem *option, 
				QWidget *widget ) ; 			
	
	QRectF boundingRect() const ; 
	virtual void keyPressEvent( QKeyEvent *event ) ;
} ; 

SuperItem::SuperItem( QGraphicsItem *parent ) : QGraphicsItem( parent ){
	setFlag( QGraphicsItem::ItemIsFocusable ) ; 
}
void SuperItem::keyPressEvent( QKeyEvent *event ){
	switch( event->key() ){
		case Qt::Key_D :{
			moveBy( 100, 0 ) ;
			break;  
		}
		case Qt::Key_A :{ 
			moveBy( -100, 0 ) ;  
			break ; 
		}
		case Qt::Key_W : {
			moveBy( 0 , -100 ) ; 
			break ; 
		}
		case Qt::Key_S : {
			moveBy( 0 , 100 ) ; 
			break ; 
		
		}
		case Qt::Key_Right : {
			moveBy( 100, 0 ) ; 
			break ;
		}
		case Qt::Key_Left : {
			moveBy( -100 , 0 ) ; 
			break; 
		}
		case Qt::Key_Up:{
			moveBy( 0, -100 ) ; 
			break ; 
		}
		case Qt::Key_Down : {
			moveBy( 0 , 100 ) ; 
			break ; 
		}
	}
	update() ; 	
}

 
QRectF SuperItem::boundingRect() const{	
	return QRectF( 0, 0 ,400, 400 ) ;  
}

void SuperItem::paint( QPainter *painter, 
				const QStyleOptionGraphicsItem *option, 
						QWidget *widget ){
	QPixmap pixImg("miku.png") ; 
	painter->drawPixmap( 0 , 0 , 200 , 200  , pixImg ) ; 	
}

int main(int argc, char *argv[]) {
	QApplication app( argc, argv ) ; 
	
	QGraphicsView view;
	QGraphicsScene *scene = new QGraphicsScene( -50 , -50 , 1366, 768 , &view ) ; 
	view.setScene( scene ) ; 
	
	QGraphicsRectItem *rect = new QGraphicsRectItem( 0, 0, 100, 100 ) ; 
	scene->addItem( rect ) ; 
	
	QGraphicsRectItem *rect2 = new QGraphicsRectItem( 0 , 0, 50, 50 ) ; 
	scene->addItem( rect2 ) ; 
	rect2->rotate( 20 ) ; 
	rect->translate( 10, 10 ) ;
		
	scene->addText("Ya Ya Ka Wa ii~~~") ; 
	
	SuperItem *superItem = new SuperItem() ; 
	superItem->setFocus( ) ; 
	scene->addItem( superItem ) ; 
	view.resize( 1366, 768 ) ; 
	view.show() ; 


	return app.exec();
}
