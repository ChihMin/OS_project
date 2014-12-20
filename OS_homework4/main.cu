#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "file.h"

//1000 KB in global memory
#define STORAGE_SIZE 1085440

#define MAX_FILE_SIZE 1048576

#define DATAFILE "./data.bin"
#define OUTFILE "./snapshot.bin"

typedef unsigned char uchar ; 
typedef uint32_t u32 ; 

//secondary memory
__device__ __managed__ uchar *volume ; 

__global__ void mykernel( uchar *input, uchar *output ){
	//####kernel start####

	

	//####kernel end####
}

int main(){
	
	cudaMallocManaged( &volume, STORAGE_SIZE ) ; 
	init_volume() ; 	

	for(int i = 0; i < STORAGE_SIZE; ++i)	
		printf("%d\n", volume[i] )  ; 
	
	uchar *input, *output ; 
	cudaMallocManaged( &input, MAX_FILE_SIZE ) ; 
	cudaMallocManaged( &output, MAX_FILE_SIZE ) ; 
	
	for(int i = 0; i < MAX_FILE_SIZE; ++i)
		output[i] = 0 ; 

	load_binaryFile( DATAFILE, input, MAX_FILE_SIZE ) ;

	cudaSetDevice( 5 ) ; 	

	mykernel<<<1, 1>>>( input, output )  ;
	cudaDeviceSynchronize() ; 
	write_binaryFile(OUTFILE, output, MAX_FILE_SIZE ) ; // i change here ~  
	cudaDeviceReset() ;

	
	return 0 ; 
}
