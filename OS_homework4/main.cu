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


const u32 FILE_OPEN_ERROR = (u32)-1 ; 


__global__ void mykernel( uchar *input, uchar *output ){
	//####kernel start####
	for(int i = 0; i < 10; ++i )
		volume[i] = 1 ; 
	
	u32 fp = open("a.txt\0", G_WRITE ) ; 
	fp = open("a.txt\0", G_READ ) ; 
	if( fp == FILE_OPEN_ERROR )
		printf("file open error\n") ; 
	read( output + 1, 10, fp ) ;  
	for(int i = 0; i < 14; ++i )
		printf("%d\n",output[i] ) ;
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
