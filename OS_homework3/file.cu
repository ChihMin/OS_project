#include "file.h"

__device__ u32 paging( uchar *buffer, u32 frame_num, u32 offset ){
	u32 t = 0 ; 
	return t ; 
}

__device__ void init_pageTable( int pt_entries ){
	
}

int load_binaryFile( const char *DATAFILE, uchar *input, int STORAGE_SIZE ){
	int size = 0 ; 
	uchar in ; 
	FILE *R = fopen( DATAFILE, "rb" ) ; 
	
	while( fread( &in, sizeof( uchar ), 1, R ) )	input[size++] = in ; 
	return size ;   
}

void write_binaryFile( const char *OUTFILE, uchar *results, int input_size ){


}
