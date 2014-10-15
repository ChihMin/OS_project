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
	
	sleep( 3 ) ;

	return 0; 
}
