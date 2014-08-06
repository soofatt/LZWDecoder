#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "LZWDecoder.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256
#define bitSize     8

//Throw when end of stream
void LZWDecode(InStream *in, Dictionary *dict, OutStream *out){
}

char *getDictTranslation(Dictionary *dict, int inputIndex){
  char *translation = "";
  int index = getIndex(inputIndex);
  
  translation = dict->entries[index].code;
  
  return translation;
}

char getAsciiTranslation(int inputIndex){
	char asciiTranslation;
	
	asciiTranslation = inputIndex;
	
	return asciiTranslation;
}

//find translation and output code
void emitCode(Dictionary *dict, int index, OutStream *out){
  char *translation;
  int i;
  
  if(index < 256){
    streamWriteBits(out, index, bitSize);
  }
  else if(index >= 256){
    translation = getDictTranslation(dict, index);
    for(i = 0; i < strlen(translation); i++){
      streamWriteBits(out, translation[i], bitSize);
    }
  }
}