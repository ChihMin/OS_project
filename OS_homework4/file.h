#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <thrust/sort.h>
#include <thrust/execution_policy.h>

#define STORAGE_SIZE 1085440
#define MAX_FILE_SIZE 1048576
#define MAX_FILE_NUMBER 1024
#define FCB_SIZE 36864
#define NAME_LENGTH 24

#define RM 0

#define LS_S 1

#define LS_D 2

typedef uint32_t u32 ;
typedef unsigned char uchar ;  
const u32 INF = (u32)1e9 ; 

typedef struct METADATA{
	int fp ;
	u32 time ;
	u32 size ;
	u32 created_time ; 
	char fileName[20] ;
} Meta ;

extern __device__ __managed__ uchar *volume ;
extern __device__ __managed__ Meta *metadata ; 

void init_volume() ; 

__device__ void strcpy( const char *A, char *B ) ; 

__device__ bool isMatched( const char *A, const char *B ) ; 
__device__ bool sizeCmp( const Meta &A, const Meta &B ) ;

__device__ bool timeCmp( const Meta &A, const Meta &B ) ;

__device__ bool filePointerCmp( const Meta &A, const Meta &B );

__device__ void sortBySize() ; 

__device__ void sortByTime() ; 

__device__ void sortByFilePointer() ; 

__device__ u32 open( const char *fileName, int mode ) ; 

__device__ void read( uchar *output, int size, u32 fp ) ; 

__device__ u32 write( uchar *input, int size, u32 fp ) ;

__device__ void gsys( u32 ins, const char *fileName );

// overloading
__device__ void gsys( u32 ins ) ;

__device__ void freeSpace() ; 

__device__ void debug() ;  

int load_binaryFile( const char *DATAFILE, uchar *input, int input_size ) ; 

void write_binaryFile( const char *OUTFILE, uchar *results, int output_size ) ; 

#endif 
