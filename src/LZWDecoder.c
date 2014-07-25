#include "LZWDecoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) x - 256

Dictionary *dictionaryNew(int length){
	Dictionary *dictionary = malloc(sizeof(Dictionary));
	dictionary->entry = calloc(length, sizeof(DictionaryEntry));
	dictionary->length = length;
	
	return dictionary;
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