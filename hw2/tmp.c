#include <stdio.h>
#include <stdlib.h>

int main(){
	int x , y ; 
	while( ~scanf("%d %d",&x, &y ) ){
		printf("\033[%d;%dH",x,y);
		printf("123456789");
	}

	return 0; 
}	
