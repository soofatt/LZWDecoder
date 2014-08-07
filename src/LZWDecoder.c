#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "LZWDecoder.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256
#define bitSize     8

//Throw when end of stream
void lzwDecode(InStream *in, Dictionary *dict, OutStream *out){
  int inputCode, dictIndex = 0;
  char *currentString, *translation, *newDictEntry;
  
  inputCode = streamReadBits(in, 8);
  emitCode(dict, inputCode, out);
  translation = codeNewAndAppend("", getAsciiTranslation(inputCode));
  currentString = translation;
  
  while(inputCode != -1){
    inputCode = streamReadBits(in, 9);
    if(inputCode < 256)
      translation = codeNewAndAppend("", getAsciiTranslation(inputCode));
    else if(inputCode >= 256)
      translation = getDictTranslation(dict, inputCode);
    
    if(translation == NULL)
      translation = codeNewAndAppend(currentString, currentString[0]);
    else{}
    
    newDictEntry = codeNewAndAppend(currentString, translation[0]);
    
    if(dictionaryAdd(dict, newDictEntry, dictIndex) == 1){
      dictIndex++;
    }
    else{}
      //fail to add to dict. error
      
    emitCode(dict, inputCode, out);
    currentString = translation;
  }
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