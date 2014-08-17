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
  int i, inputByte, outputWhole = 0;
  unsigned char byteToRead, tempBitRead = 0;
  
  while(in->currentByte <= (bitSize/8)){
    if((inputByte = fgetc(in->file)) == EOF)
      Throw(END_OF_STREAM);
      
    byteToRead = inputByte;
    
    for(i = 0; i < 8; i++){
      outputWhole = outputWhole << 1;
      tempBitRead = streamReadBit(byteToRead);
      outputWhole = outputWhole | tempBitRead;
      byteToRead = byteToRead << 1;
      if(in->bitIndex == (bitSize - 1))
        break;
      else
        in->bitIndex++;
    }
    if(i == 8)
      in->currentByte++;
    else if(in->bitIndex == (bitSize - 1))
      break;
  }
  return outputWhole;
}

int streamReadBit(char byteToRead){
  int mask = 0x80, bitRead = 0;

  bitRead = (byteToRead & mask) >> 7;

  return bitRead;
}

void closeInStream(InStream *in){
  fclose(in->file);
  free(in);
}