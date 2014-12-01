#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar ; 

int main(){

	FILE *Rb = fopen( "./data.bin", "rb" ) ;
	
	uchar a , b ; 

	int i = 0 ; 	
	while( fread( &a, sizeof( uchar ), 1, Rb ) ){
		printf("%d -> %d\n", i++ ,a   ) ;
	}

	return 0 ; 
}
