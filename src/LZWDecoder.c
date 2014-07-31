#include "LZWDecoder.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256

void LZWDecode(Dictionary *dict){
}

Dictionary *dictionaryNew(int length){
	Dictionary *dictionary = malloc(sizeof(Dictionary));
	dictionary->entries = calloc(length, sizeof(DictionaryEntry));
	dictionary->length = length;
	
	return dictionary;
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

char *codeNewAndAppend(char *oldCode, char codeToAppend){
	char *newCode = malloc((strlen(oldCode)) + 1 + 1); 
	int codeLen = strlen(oldCode);
	
	newCode = strcpy(newCode, oldCode);
	
	newCode[codeLen] = codeToAppend;
	newCode[codeLen+1] = '\0';
	
	return newCode;
}

//0 = fail to add, 1 = add successful
int dictionaryAdd(Dictionary *dict, char *code, int index){
  
  if(index >= dict->length || index < 0){
    return 0;
  }
  else{
    dict->entries[index].code = code;
    return 1;
  }
}

void dictionaryDel(Dictionary *dict){
	int i;
	
	for(i = 0; i < dict->length; i++){
		if(dict->entries[i].code != NULL)
      free(dict->entries[i].code);
	}
  
  free(dict);
}