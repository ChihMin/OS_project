#ifndef MIKU_H
#define MIKU_H 

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
#include <QKeyEvent>
#include "MyWidget.h"

class Miku : public QWidget{

Q_OBJECT 
public : 	
	Miku( QWidget *parent = 0 ) ; 	
	void keyPressEvent( QKeyEvent* ) ;  
public slots :
	void setPosition() ; 
signals :
	void clicked() ; 
	void timeout() ;

protected : 
	void paintEvent( QPaintEvent* ) ; 

private : 
	int x , y ;  
	QTimer *timer ;
	MyWidget *woods[20] ;  
} ; 

#endif
