#ifndef WINDOWS_H
#define WINDOWS_H

#include <QObject>
#include "Miku.h"
#include "MyWidget.h"
#include <QSlider>
#include <QPushButton>

class Windows : public QWidget{

	Q_OBJECT 

public : 
	Windows( QWidget *parent = 0 ) ;
	MyWidget *woods[20] ;
	Miku *miku ;
	int getMikuX() ; 
	int getMikuY() ;
	int getWoodX( int pos ) ; 
	int getWoodY( int pos ) ;
	int getWoodSpeed( int pos ) ;   
	int getLogCount() ;   
	int isInRange( int x , int y ) ;
	void changeMiku( int x , int y ) ;  
	void setMikuSpeed( int speed ) ; 	
	//static void showExitStatus( int type ) ; 

public slots: 
	void speedChanges( int ) ; 

signals : 
	void valueChanged( int ) ; 

protected : 
	void keyPressEvent( QKeyEvent* ) ; 
	void paintEvent( QPaintEvent* ) ; 
private :
	int logCount ; 
	int mikuSpeed ; 
	int length[20] ;
	int speed ; 
	QSlider *slider ; 
} ; 

#endif
