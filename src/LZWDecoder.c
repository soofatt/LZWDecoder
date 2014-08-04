#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "LZWDecoder.h"
#include "CException.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256

//Throw when end of stream
void LZWDecode(InStream *in, Dictionary *dict, OutStream *out){
}

//find translation and output code
void emitCode(Dictionary *dict, int index, OutStream *out){
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
