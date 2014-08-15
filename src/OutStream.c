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

void streamWriteBit(OutStream *out, int bitToWrite){
  
}

void closeOutStream(OutStream *out){
  fclose(out->file);
  free(out);
}