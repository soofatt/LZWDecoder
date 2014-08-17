#include "CException.h"
#include "InStream.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <malloc.h>

InStream *openInStream(char *fileName, char *openMethod){
	InStream *inStream = calloc(1, sizeof(InStream));

	inStream->file = fopen(fileName, openMethod);

  if(inStream->file == NULL)
    Throw(ERR_CANNOT_OPEN_FILE);

	inStream->filename = fileName;
	inStream->currentByte = 0;
	inStream->bitIndex = 0;
  
  return inStream;
}

int streamReadBits(InStream *in, int bitSize){
  int i, inputByte, outputWhole = 0, bitCount = 0, byteCount = 0;
  uint8 byteToRead, tempBitRead = 0;
  
  if(feof(in->file) != 0)
    Throw(END_OF_STREAM);
  
  while(byteCount <= (bitSize/8)){
    if(in->currentByte != 0)
      byteToRead = in->currentByte;
    else{
      if((inputByte = fgetc(in->file)) == EOF)
        break;
      byteToRead = inputByte;
    } 
    
    for(i = in->bitIndex; i < 8; i++){
      outputWhole = outputWhole << 1;
      tempBitRead = streamReadBit(byteToRead);
      outputWhole = outputWhole | tempBitRead;
      byteToRead = byteToRead << 1;
      in->bitIndex++;
      if(in->bitIndex == 8)
        in->bitIndex = 0;
      if(bitCount == (bitSize - 1))
        break;
      else
        bitCount++;
    }
    if(i == 8){
      byteCount++;
      in->currentByte = byteToRead;
    }
    else if(bitCount == (bitSize - 1)){
      in->currentByte = byteToRead;
      break;
    }
  }
  
  return outputWhole;
}

int streamReadBit(uint8 byteToRead){
  int mask = 0x80, bitRead = 0;

  bitRead = (byteToRead & mask) >> 7;

  return bitRead;
}

void closeInStream(InStream *in){
  fclose(in->file);
  free(in);
}