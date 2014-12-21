#include "file.h"

extern __device__ __managed__ u32 updated_at; 
extern __device__ __managed__ u32 file_num;
extern __device__ __managed__ u32 last_pos;

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

__device__ bool isMatched( const char *A, const char *B ){
	int i = -1; 
	do{
		i++ ; 
		if( A[i] != B[i] )
			return false ; 
	} while( A[i] != 0 && B[i] != 0 ) ; 
	return true ; 
}

__device__ void strcpy( const char *A, char *B ){
	int i = 0 ; 
	do{
		B[i] = A[i] ; 
	} while( A[i++] != '\0' ) ; 
}

__device__ void debug(){
	printf("========DEBUG PRINT START=======\n"); 
	for(int i = 0; i < file_num; ++i ){
		Meta *cur = &metadata[i] ; 
		printf("filename : %s\n", cur->fileName ) ;
		printf("size : %d\n", cur->size ); 
		printf("time : %d\n", cur->time ); 
		printf("fp : %d\n", cur->fp ); 
		printf("\n"); 
	}

	printf("=========  E  N  D   =========\n"); 
}

__device__ u32 open( const char *fileName, int mode ){
	u32 fp = 0;
	for(int i = 0; i < file_num; ++i){
		// Find file is whether exist or not
		if( isMatched( fileName, metadata[i].fileName ) ){
			return i ; 
		}
	}

	if( mode ){
		// Create a new file
		if( file_num == 1024 )	// If more than 1024 files
			return (u32)-1 ; 
		metadata[file_num].size = 0; 
		metadata[file_num].time = updated_at++ ; 
		metadata[file_num].fp = last_pos ;
		strcpy( fileName, metadata[file_num].fileName ) ;
		fp = file_num++ ;
		
		return fp ;      
	}
	
	return (u32)-1 ; 
}

__device__ bool sizeCmp( const Meta &A, const Meta &B ){
	if( A.size != B.size )	
		return A.size > B.size ;
	return A.time < B.time ; 
}


__device__ bool timeCmp( const Meta &A, const Meta &B ){
	return A.time > B.time ; 
}

__device__ bool filePointerCmp( const Meta &A, const Meta &B ){
	return A.fp > B.fp ; 

}

__device__ void read( uchar *output, int size, u32 fp){
	for(int i = 0, j = metadata[fp].fp ; i < size; ++i, ++j ){
		output[i] = volume[j] ; 
	}
}

__device__ u32 write( uchar *input, int size, u32 fp){
	Meta *cur = &metadata[fp] ;
	
	cur->fp = last_pos ; 
	cur->time = updated_at++ ; 
	cur->size = size ;
	
	for(int i = 0; i < size; ++i)
		volume[last_pos++] = input[i] ; 
	return last_pos ;   	
}

__device__ void sortBySize(){	
	for(int i = 0; i < file_num; ++i){
		for(int j = i + 1; j < file_num; ++j ){
			if( sizeCmp( metadata[j] , metadata[i] ) ){
				// swapping 
				Meta tmp = metadata[i] ; 
				metadata[i] = metadata[j] ; 
				metadata[j] = tmp ;  			
			}
		}
	}
}

__device__ void sortByTime(){
	for(int i = 0; i < file_num; ++i){
		for(int j = i + 1; j < file_num; ++j ){
			if( timeCmp( metadata[j] , metadata[i] ) ){
				// swapping 
				Meta tmp = metadata[i] ; 
				metadata[i] = metadata[j] ; 
				metadata[j] = tmp ;  			
			}
		}
	}
}

__device__ void sortByFilePointer(){
	for(int i = 0; i < file_num; ++i){
		for(int j = i + 1; j < file_num; ++j ){
			if( filePointerCmp( metadata[i] , metadata[j] ) ){
				// swapping 
				Meta tmp = metadata[i] ; 
				metadata[i] = metadata[j] ; 
				metadata[j] = tmp ;  			
			}
		}
	}
}

__device__ void gsys( u32 ins, const char *fileName ){
	// Here is used to Remove File 
	u32 tar ; 
	for(int i = 0; i < file_num; ++i)
		if( isMatched( fileName, metadata[i].fileName ) ){
			tar = i ; 
			break ; 
		}

	for(int i = tar + 1; i < file_num; ++i)
		metadata[i-1] = metadata[i] ; 
	file_num-- ; 
}

__device__ void gsys( u32 ins ){
	if( ins == LS_S ){
		sortBySize() ; 
		printf("===sort by file size===\n") ;
	}
	else if( ins == LS_D ){
		sortByTime() ; 	
		printf("===sort by modified time===\n"); 
	}

	for(int i = 0; i < file_num; ++i){
		Meta *cur = &metadata[i]; 
		if( ins == LS_S )	
			printf("%s %d\n", cur->fileName, cur->size ) ;
		else
			printf("%s\n", cur->fileName ); 
	}

}

__device__ void freeSpace(){
	
	sortByFilePointer() ;
	last_pos = 0 ; 
	for(int i = 0; i < file_num; ++i){
		int fp = metadata[i].fp ;
		metadata[i].fp = last_pos ;	// update fp    
		u32 size = metadata[i].size ; 
		for(int j = 0; j < size; ++j){
			volume[last_pos++] =  volume[fp++] ; 
		}
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
