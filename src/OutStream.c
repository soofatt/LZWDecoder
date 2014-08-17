#include "CException.h"
#include "OutStream.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <malloc.h>

/*To open a file with write method for writing
 *
 *Input: *fileName -> the file name.
 *       *openMethod -> open method ("w" for write, "r" for read)
 *
 *Output:outStream -> pointer to OutStream struct
 *
 *Throw:  -
 *
 */
OutStream *openOutStream(char *fileName, char *openMethod){
	OutStream *outStream = calloc(1, sizeof(OutStream));

	outStream->file = fopen(fileName, openMethod);
	outStream->filename = fileName;
	outStream->currentByte = 0;
	outStream->bitIndex = 0;

  return outStream;
}

/*To write bytes into the file
 *
 *Input: *out -> pointer to OutStream struct
 *       bitsToWrite -> the bits to be written to the file
 *       bitSize -> number of bits to be written
 *
 *Output: -
 *
 *Throw:  -
 *
 */
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

/*To write a bit to currentByte member of OutStream struct
 *
 *Input: *out -> pointer to OutStream struct
 *       bitToWrite -> the bit to be written to currentByte
 *
 *Output: -
 *
 *Throw:  -
 *
 */
void streamWriteBit(OutStream *out, uint8 bitToWrite){
  out->currentByte = out->currentByte | bitToWrite;
  out->bitIndex++;
  if(out->bitIndex == 8)
    out->bitIndex = 0;
}

/*To flush out remaining bits in currentByte member of OutStream struct
 *
 *Input: *out -> pointer to OutStream struct
 *
 *Output: -
 *
 *Throw:  -
 *
 */
void streamFlush(OutStream *out){
  fputc(out->currentByte, out->file);
}

/*To close the file and free the OutStream struct
 *
 *Input: *out -> pointer to OutStream struct
 *
 *Output: -
 *
 *Throw:  -
 *
 */
void closeOutStream(OutStream *out){
  fclose(out->file);
  free(out);
}