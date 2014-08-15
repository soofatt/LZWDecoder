#ifndef OutStream_H
#define OutStream_H

#include <stdio.h>
#include "Utils.h"

typedef struct OutStream{
	FILE *file;
	char *filename;
	uint8 currentByte;
	// uint32 length;
	// uint32 byteIndex;
	 uint32 bitIndex;
}OutStream;

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize);
void streamWriteBit(OutStream *out, int bitToWrite);
OutStream *openOutStream(char *filename, char *openMethod);
void streamFlush(OutStream *out);
void closeOutStream(OutStream *out);

#endif // OutStream_H
