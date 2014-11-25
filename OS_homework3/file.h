#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


typedef uint32_t u32 ;
typedef unsigned char uchar ;  

__device__ u32 paging( uchar *buffer, u32 frame_num, u32 offset ) ;

__device__ void init_pageTable( int pt_entries ) ; 

int load_binaryFile( const char *DATAFILE, uchar *input, int STORAGE_SIZE ) ; 

void write_binaryFile( const char *OUTFILE, uchar *results, int input_size ) ; 

#endif 
