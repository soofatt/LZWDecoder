#ifndef InStream_H
#define InStream_H

typedef struct InStream{
	FILE *file;
	char *filename;
	char *buffer;
	int length;
	char byteIndex;
	char bitIndex;
}InStream;

int streamReadBits(InStream *in, int bitSize);

#endif // InStream_H
