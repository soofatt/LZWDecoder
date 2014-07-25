#include "LZWDecoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256

Dictionary *dictionaryNew(int length){
	Dictionary *dictionary = malloc(sizeof(Dictionary));
	dictionary->entries = calloc(length, sizeof(DictionaryEntry));
	dictionary->length = length;
	
	return dictionary;
}

char *getDictTranslation(Dictionary *dict, int input){
  char *translation = "";
  int index = getIndex(input);
  
  translation = dict->entries[index].code;
  
  return translation;
}

char getAsciiTranslation(int input){
	char asciiTranslation;
	
	asciiTranslation = input;
	
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

void dictionaryDel(Dictionary *dict){
	int i;
	
	for(i = 0; i < dict->length; i++){
		if(dict->entries[i].code != NULL)
      free(dict->entries[i].code);
	}
  
  free(dict);
}