#include "CException.h"
#include "OutStream.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <malloc.h>

OutStream *openOutStream(char *fileName, char *openMethod){
	OutStream *outStream = calloc(1, sizeof(OutStream));

	outStream->file = fopen(fileName, openMethod);
	outStream->filename = fileName;
	outStream->currentByte = 0;
	outStream->bitIndex = 0;

  return outStream;
}

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize){
  int i, bitsToOutput, mask = 0x80;
  uint8 tempBitsToWrite, bitToWrite;
  
  tempBitsToWrite = bitsToWrite;
  
  for(i = 0; i < bitSize; i++){
    out->currentByte = out->currentByte << 1;
    bitToWrite = (tempBitsToWrite & mask) >> 7;
    streamWriteBit(out, bitToWrite);
    tempBitsToWrite = tempBitsToWrite << 1;
  }
  
  fputc(out->currentByte, out->file);
}

void streamWriteBit(OutStream *out, uint8 bitToWrite){
  out->currentByte = out->currentByte | bitToWrite;
  out->bitIndex++;
  if(out->bitIndex == 8)
    out->bitIndex = 0;
}

void closeOutStream(OutStream *out){
  fclose(out->file);
  free(out);
}