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
	int getLogCount() ;   
protected : 
	void keyPressEvent( QKeyEvent* ) ; 

private :
	int logCount ; 


} ; 

#endif
