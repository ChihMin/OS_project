#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main(){

	alarm( 2 ) ;   
	int x = 0 ;
	int cnt = 0 ; 
	while( x < 1e8 ){
		if( x == (1e8) - 1 ){	
			if( cnt < 3 )	x = 0, cnt++  ;
		}
		x++ ; 
	}
	return 0; 
}
