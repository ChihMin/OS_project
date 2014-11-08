#include "Miku.h"
#include "MyWidget.h"
#include "windows.h"
#include <pthread.h>

Windows::Windows( QWidget *parent ) : QWidget( parent ) {
	setFixedSize( 1366, 768 ) ;	
	
	for(int i = 1;i <= 5; ++i )	
		woods[i] = new MyWidget( 0, i * 100, this ) ; 

	miku = new Miku( this ) ; 
}

void Windows::keyPressEvent( QKeyEvent *event ){
	miku->keyPressEvent( event ) ; 
}
