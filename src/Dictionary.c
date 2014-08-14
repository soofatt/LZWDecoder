#include "Dictionary.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

/*To create a new custom dictionary.
 *
 *Input: length -> the length dictionary.
 *
 *Output:dictionary -> the dictionary.
 *
 *Throw:  -
 *
 */
Dictionary *dictionaryNew(int length){
	Dictionary *dictionary = malloc(sizeof(Dictionary));
	dictionary->entries = calloc(length, sizeof(DictionaryEntry));
	dictionary->length = length;
  dictionary->size = 256;
	
	return dictionary;
}

/*To append a character to a string
 *
 *Input: *oldCode -> the old string
 *       codeToAppend -> the character to be appended to the old string.
 *
 *Output:newCode -> the new string with the appended character.
 *
 *Throw:  -
 *
 */
char *codeNewAndAppend(char *oldCode, char codeToAppend){
	char *newCode = malloc((strlen(oldCode)) + 1 + 1); 
	int codeLen = strlen(oldCode);
	
	newCode = strcpy(newCode, oldCode);
	
	newCode[codeLen] = codeToAppend;
	newCode[codeLen+1] = '\0';
	
	return newCode;
}

/*To add an entry into the custom dictionary.
 *
 *Input: *dict -> the dictionary.
 *       *code -> the string(entry) to be added into the custom dictionary.
 *       index -> the index where the new entry should be inserted at.
 *
 *Output:1 -> if entry was successfully added.
 *       0 -> if entry failed to be added into custom dictionary.
 *
 *Throw:  -
 *
 */
int dictionaryAdd(Dictionary *dict, char *code, int index){
  
  if(index >= dict->length || index < 0){
    return 0;
  }
  else{
    dict->entries[index].code = code;
    dict->entries[index].length = strlen(code);
    dict->size++;
    return 1;
  }
}

/*To delete the dictionary.
 *
 *Input: *dict -> the dictionary.
 *
 *Output: -
 *
 *Throw:  -
 *
 */
void dictionaryDel(Dictionary *dict){
	int i;
	
	for(i = 0; i < dict->length; i++){
		if(dict->entries[i].code != NULL)
      free(dict->entries[i].code);
	}
  
  free(dict);
}