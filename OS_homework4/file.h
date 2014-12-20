#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define STORAGE_SIZE 1085440


typedef uint32_t u32 ;
typedef unsigned char uchar ;  

extern __device__ __managed__ uchar *volume ;

void init_volume() ; 

int load_binaryFile( const char *DATAFILE, uchar *input, int input_size ) ; 

void write_binaryFile( const char *OUTFILE, uchar *results, int output_size ) ; 

#endif 
