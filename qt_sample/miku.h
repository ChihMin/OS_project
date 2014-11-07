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

class MyWidget : public QWidget{

Q_OBJECT 
public : 	
	MyWidget( QWidget *parent = 0 ) ; 	
public slots :
	void setPosition() ; 
signals :
	void clicked() ; 
	void timeout() ; 

protected : 
	void paintEvent( QPaintEvent* ) ; 

private : 
	int pos ; 
	QTimer *timer ; 
} ; 

#endif
