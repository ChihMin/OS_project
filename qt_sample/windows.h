#ifndef WINDOWS_H
#define WINDOWS_H

#include <QObject>
#include "Miku.h"
#include "MyWidget.h"

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
	int getLogCount() ;   
	bool isInRange( int x , int y ) ;
	void changeMiku( int x , int y ) ;  
	void setMikuSpeed( int speed ) ; 	
protected : 
	void keyPressEvent( QKeyEvent* ) ; 

private :
	int logCount ; 
	int mikuSpeed ; 
	int length[20] ; 
} ; 

#endif
