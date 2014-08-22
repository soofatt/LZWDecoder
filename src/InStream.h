#ifndef InStream_H
#define InStream_H

#include <stdio.h>
#include "Utils.h"

typedef struct InStream{
	FILE *file;
	char *filename;
	uint8 currentByte;
	// uint32 length;
	uint32 byteIndex;
	uint32 bitIndex;
}InStream;

int streamReadBits(InStream *in, int bitSize);
int streamReadBit(uint8 byteToRead);
InStream *openInStream(char *filename, char *openMethod);
void closeInStream(InStream *in);

#endif // InStream_H
