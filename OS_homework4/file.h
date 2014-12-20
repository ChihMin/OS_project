#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define STORAGE_SIZE 1085440
#define MAX_FILE_SIZE 1048576
#define MAX_FILE_NUMBER 1024
#define FCB_SIZE 36864
#define NAME_LENGTH 24

typedef uint32_t u32 ;
typedef unsigned char uchar ;  
const u32 INF = (u32)1e9 ; 

typedef struct METADATA{
	int fp ;
	u32 time ;
	u32 size ;
	uchar fileName[24] ;
} Meta ;

extern __device__ __managed__ uchar *volume ;
extern __device__ __managed__ Meta *metadata ; 

void init_volume() ; 

__device__ u32 open( const char *fileName, int mode ) ; 

int load_binaryFile( const char *DATAFILE, uchar *input, int input_size ) ; 

void write_binaryFile( const char *OUTFILE, uchar *results, int output_size ) ; 

#endif 
