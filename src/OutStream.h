#ifndef OutStream_H
#define OutStream_H

#include <stdio.h>

typedef struct OutStream{
	FILE *file;
	char *filename;
	char *buffer;
	int length;
	char byteIndex;
	char bitIndex;
}OutStream;

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize);
void streamFlush(OutStream *out);

#endif // OutStream_H
