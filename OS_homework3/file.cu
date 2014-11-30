#include "file.h"

extern __device__ __managed__ int PAGEFAULT ; 
extern __device__ __managed__ int inTime ; 
extern __device__ __managed__ uchar storage[] ; 

__device__ u32 paging( uchar *buffer, u32 frame_num, u32 offset ){

	u32 target ; 
	int pt_entries = PT_ENTRIES ;
	 
	for(int i = 0; i < pt_entries; ++i ){
		int mask = ( (1<<13) - 2 ) ; 
		int pageNum = ( pt[i] & mask ) >> 1 ; 
		 
		if( ( pt[i] & 1 )  && pageNum == frame_num ){
			int tmpTime = inTime++ ; 	
			pt[i] = ( tmpTime << 13 ) | ( frame_num << 1 ) | 1 ; 
			return i * 32 + offset ;
		}
	}
	
	for(int i = 0; i < pt_entries; ++i ){
		if( pt[i] ^ 1 )	{	// if is invalid
			PAGEFAULT++ ;
			int tmpTime = inTime++ ; 
			pt[i] = ( tmpTime << 13 ) | ( frame_num << 1 ) | 1 ; 
			return i * 32 + offset  ; 
		}
	}

	int timeRange = -1 ; 
	for(int i = 0; i < pt_entries; ++i ){
		int mask = -1 ; 
		int tmpTime  = (( mask << 13 ) &  pt[i] ) >> 13 ;
		int tmp = inTime - tmpTime ; 

		if( tmp > timeRange  ){
			target = i ;
			timeRange = tmp ;  
		}
	}
	
	PAGEFAULT++ ;

	// move the data from shared memory to global memory 
	int mask = ( 1 << 13 ) - 2 ; 
	u32 tarFrame = ( pt[target] & mask) >> 1 ;
	int beginAddress = tarFrame * 32; 
	for(int i = beginAddress, j = 0; j < 32; ++i , ++j){
		int sharedAddress = target * 32 + j ;
		int curAddress = frame_num * 32 + j ; 
		 
		storage[i] = buffer[sharedAddress] ; 
		buffer[sharedAddress] = storage[curAddress]; 
	}
	pt[target] = ((inTime++) << 13 ) | ( frame_num << 1 ) | 1 ;
	return target * 32 + offset ;
}

__device__ void init_pageTable( int pt_entries ){
	for(int i = 0; i < pt_entries; ++i ){
		pt[i] = 0  ; 
	}
}

int load_binaryFile( const char *DATAFILE, uchar *input, int STORAGE_SIZE ){
	int size = 0 ; 
	uchar in ; 
	FILE *R = fopen( DATAFILE, "rb" ) ; 
	
	while( fread( &in, sizeof( uchar ), 1, R ) )	
		input[size++] = in ; 
	fclose( R )  ;
	
	return size ;  
}

void write_binaryFile( const char *OUTFILE, uchar *results, int input_size ){
	FILE *W = fopen( OUTFILE, "wb" ) ; 
	for(int i = 0; i < input_size; ++i ){
		fwrite( &results[i], sizeof( uchar ), 1, W ) ;
	}
	fclose( W ) ; 
}
