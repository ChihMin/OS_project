#include <stdio.h>

int main(){

	char buf[511];
	FILE *fp = fopen("/dev/example", "w+");
	if( fp == NULL ){
		printf("can't open device!\n");
		return 0;
	}

	fread(buf, sizeof(buf), 1, fp);
	fclose( fp );

	int i ;
	for(i = 0; i < 12; ++i)
		printf("%c\n", buf[i]);

	return 0; 
}
