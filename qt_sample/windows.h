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
protected : 
	void keyPressEvent( QKeyEvent* ) ; 

} ; 

#endif
