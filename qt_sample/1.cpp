#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QBitmap>
#include "MyWidget.h"
#include "Miku.h"
#include "windows.h"


int main( int argc , char **argv ){

	QApplication app( argc , argv ) ; 

	MyWidget window ; 
	Miku parse ;
	
	Windows *win = new Windows()  ;  
	win->show() ;   	
	return app.exec(); 
}	
