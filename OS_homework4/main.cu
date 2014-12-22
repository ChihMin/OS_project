#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "file.h"

// 1000 KB in global memory
#define STORAGE_SIZE 1085440

// 36 KB file control block
#define FCB_SIZE 36864

// file's maximum size 
#define MAX_FILE_SIZE 1048576

// maximum file number
#define MAX_FILE_NUMBER 1024

// file name at most 24(20) chars
#define NAME_LENGTH 24 

// G_READ mode is 0
#define G_READ 0 

// G_WRITE mode is 1
#define G_WRITE 1

// RM instruction = 0
#define RM 0

// list all file by size order 
#define LS_S 1

// list all file by modified time order
#define LS_D 2

#define DATAFILE "./data.bin"
#define OUTFILE "./snapshot.bin"

typedef unsigned char uchar ; 
typedef uint32_t u32 ; 
/*
typedef struct METADATA{
	u32 fp ; 
	u32 time ; 
	u32 size ;
	uchar fileName[24] ; 
} Meta ; 
*/

//secondary memory
__device__ __managed__ uchar *volume ; 
__device__ __managed__ Meta *metadata ; 
__device__ __managed__ u32 updated_at = 0 ; 
__device__ __managed__ u32 file_num = 0 ;
__device__ __managed__ u32 last_pos = 0 ;


#define FILE_OPEN_ERROR -1 ; 


__global__ void mykernel( uchar *input, uchar *output ){
	//####kernel start####i

/*
	u32 fp ; 
	printf("max = %d\n",MAX_FILE_NUMBER ) ; 
	for(int i = 0; i < MAX_FILE_NUMBER; ++i){
		int tmp = i ;
		char s[30] ;
		int len = 0 ;
		do{
			s[len++] = tmp % 10 + '0' ; 
			tmp /= 10 ; 
		}while( tmp != 0 );
		

		s[len] = s[len+1] = '\0'  ; 
		fp = open( s, G_WRITE ) ; 
		fp = write( input, 1024, fp ) ; 
		//printf("%d -> %s\n", , s ) ; 
	}
	for(int i = 0; i < MAX_FILE_NUMBER; ++i){
		int tmp = i ;
		char s[30] ;
		int len = 0 ;
		do{
			s[len++] = tmp % 10 + '0' ; 
			tmp /= 10 ; 
		}while( tmp != 0 );
		

		s[len] = s[len+1] = '\0'  ; 
		gsys( RM , s ) ; 
		
		//printf("%d -> %s\n", , s ) ; 
	}
	

	printf("%d\n", fp) ;
	gsys( LS_S ) ;
*/	
	 
	//Sample TA Test Case 
	fp = open("t.txt\0", G_WRITE ) ;
	write(input, 64, fp ) ;
	
	fp = open("b.txt\0", G_WRITE ) ;
	write(input + 32, 32, fp ) ;

	fp = open("t.txt\0", G_WRITE); 
	write(input + 32, 32, fp );

	freeSpace() ; 
	
	fp = open("t.txt\0", G_READ) ;
	read(output, 32, fp ); 

	gsys(LS_D);
	gsys(LS_S);

	fp = open("b.txt\0", G_WRITE );
	write( input + 64, 12, fp );
	gsys(LS_S);
	gsys(LS_D);

	gsys(RM, "t.txt\0");
	gsys(LS_S) ;

	//####kernel end####
}

int main(){
	
	cudaMallocManaged( &metadata, FCB_SIZE ) ; 
	cudaMallocManaged( &volume, MAX_FILE_SIZE ) ; 
	init_volume() ; 

	uchar *input, *output ; 
	cudaMallocManaged( &input, MAX_FILE_SIZE ) ; 
	cudaMallocManaged( &output, MAX_FILE_SIZE ) ; 
	
	for(int i = 0; i < MAX_FILE_SIZE; ++i)
		output[i] = 0 ; 

	load_binaryFile( DATAFILE, input, MAX_FILE_SIZE ) ;

	cudaSetDevice( 5 ) ; 	

	mykernel<<<1, 1>>>( input, output )  ;
	cudaDeviceSynchronize() ; 
	write_binaryFile(OUTFILE, output, MAX_FILE_SIZE ) ;  
	cudaDeviceReset() ;

	
	return 0 ; 
}
