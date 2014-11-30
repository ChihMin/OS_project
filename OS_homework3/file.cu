#include "file.h"

extern __device__ __managed__ int PAGEFAULT ; 
extern __device__ __managed__ int inTime ; 
extern __device__ __managed__ uchar storage[] ; 

__device__ u32 paging( uchar *buffer, u32 frame_num, u32 offset ){

	u32 target ; 
	int pt_entries = PT_ENTRIES ;
	/* 
		The format of entry :
		1. Bit 0 is used to store valid/invalid bit 
		2. From bit 1 to 12 is used to store logical page number
		3. From bit 13 to 31 is used to store clock time
	*/
	/* 這裡是用來找有沒有重複 hit 的page*/ 
	for(int i = 0; i < pt_entries; ++i ){
		int mask = ( (1<<13) - 2 ) ; 
		int pageNum = ( pt[i] & mask ) >> 1 ; 
		/* pageNum 用來存pt[i]的logic page number */
		
		/* If frame_num(the logic page number want to query) 
			is the same as logical page number in entry   
		*/
		if( ( pt[i] & 1 )  && pageNum == frame_num ){
			int tmpTime = inTime++ ;
			// update hit time  	
			pt[i] = ( tmpTime << 13 ) | ( frame_num << 1 ) | 1 ; 
			return i * 32 + offset ;
		}
	}
	
	for(int i = 0; i < pt_entries; ++i ){
		if( pt[i] ^ 1 )	{	// If find invalid entry( empty entry )
			PAGEFAULT++ ;	// add PageFault
			/*
				update page table
			*/
			int tmpTime = inTime++ ; 
			pt[i] = ( tmpTime << 13 ) | ( frame_num << 1 ) | 1 ; 
			return i * 32 + offset  ; 
		}
	}

	int timeRange = -1 ; 
	// timeRange = CurrentTime - hitPageTime
	// timeRange is used to determine what the least time is 
	// if some time is earlier, the timeRange is wider
	// target variable is used to store the entry
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
	/*
		move the page from shared memory to global memory 
		And move the page form secondary storage to shared memory 
	*/
	int mask = ( 1 << 13 ) - 2 ; 
	u32 tarFrame = ( pt[target] & mask) >> 1 ;	//要被換掉的logical page
	int beginAddress = tarFrame * 32; //要被換掉的page的目標secondary memory 
	for(int i = beginAddress, j = 0; j < 32; ++i , ++j){
		int sharedAddress = target * 32 + j ; // 當前要交換的physical memory address
		int curAddress = frame_num * 32 + j ; // 想要交換到physical memory address 的page
		 
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
