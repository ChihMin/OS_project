#ifndef MY_WIDGET_H
#define MY_WIDGET_H 

#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QLCDNumber>
#include <QSlider>
#include <QVBoxLayout>
#include <QPainter>
#include <QBitmap>

class MyWidget : public QWidget{

Q_OBJECT 
public : 	
	MyWidget(  QWidget *parent = 0 ) ; 	
	MyWidget(  int _x , int _y, int _length , QWidget *parent = 0 ) ; 	
	QPushButton *quit ;
	int getX() ; 
	int getY() ; 
	int getSpeed() ; 
	void setSpeed( int _speed ) ;  
public slots :
	void setPosition() ; 
signals :
	void clicked() ; 
	void timeout() ;

protected : 
	void paintEvent( QPaintEvent* ) ; 
private :
	int speed , length ;  
	int x , y  ; 
	QTimer *timer ;
} ; 

#endif
