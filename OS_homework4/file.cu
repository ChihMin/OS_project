#include "file.h"

void init_volume(){
	for(int i = 0; i < MAX_FILE_SIZE; ++i)
		volume[i] = 0 ; 
	
	for(int i = 0; i < MAX_FILE_NUMBER; ++i){
		metadata[i].fp = -1 ;
		metadata[i].time = 0 ;
		metadata[i].size = 0 ; 
		
		for(int j = 0; j < NAME_LENGTH; ++j)
			metadata[i].fileName[j] = '\0' ;
	}
}

int load_binaryFile( const char *DATAFILE, uchar *input, int input_size ){
	int size = 0 ; 
	uchar in ; 
	FILE *R = fopen( DATAFILE, "rb" ) ; 
	
	while( size < input_size && fread( &in, sizeof( uchar ), 1, R ) )	
		input[size++] = in ; 
	fclose( R )  ;
	
	return size ;  
}

void write_binaryFile( const char *OUTFILE, uchar *results, int output_size ){
	FILE *W = fopen( OUTFILE, "wb" ) ; 
	for(int i = 0; i < output_size; ++i ){
		fwrite( &results[i], sizeof( uchar ), 1, W ) ;
	}
	fclose( W ) ; 
}
