#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "LZWDecoder.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) (x - 256)
#define bitSize     8

char *(*_getDictTranslation)(Dictionary *dict, int inputIndex) = getDictTranslation;

/*To decode a given stream of inputs
 *
 *Input: *in -> the input stream from file.
 *       *dict -> the dictionary.
 *       *out -> the output stream to file.
 *
 *Output: -
 *
 *Throw:  ERR_INVALID_INDEX -> Thrown when given input code is <0.
 *        ERR_EXCEEDING_DICTIONARY_SIZE -> Thrown when attempting to add another
 *                                         entry to a full custom dictionary
 *
 */
void lzwDecode(InStream *in, Dictionary *dict, OutStream *out){
  int inputCode, dictIndex = 0, bitLimit, bitsToRead, counter = 0;
  char *currentString, *translation, *newDictEntry;
  
  bitsToRead = getBitsToRead(dict);
  
  inputCode = streamReadBits(in, (bitsToRead - 1));
  
  if(inputCode >= dict->length || inputCode < 0)
    Throw(ERR_INVALID_INDEX);
    
  emitCode(dict, inputCode, out);
  translation = codeNewAndAppend("", getAsciiTranslation(inputCode));
  currentString = translation;
  bitLimit = 1 << (bitsToRead - 1);
  
  while(inputCode != -1){
    inputCode = streamReadBits(in, bitsToRead);
    if(inputCode < 256 && inputCode >= 0)
      translation = codeNewAndAppend("", getAsciiTranslation(inputCode));
    else if(inputCode >= 256)
      translation = _getDictTranslation(dict, inputCode);
    else if(inputCode == -1)
      Throw(END_OF_STREAM);
    else
      Throw(ERR_INVALID_INDEX);
    
    if(translation == NULL)
      translation = codeNewAndAppend(currentString, currentString[0]);
    else{}//Do nothing
    
    newDictEntry = codeNewAndAppend(currentString, translation[0]);
    
    if(dictionaryAdd(dict, newDictEntry, dictIndex) == 1){
      dictIndex++;
    }
    else{
      Throw(ERR_EXCEEDING_DICTIONARY_SIZE);
    }
    
    emitCode(dict, inputCode, out);
    currentString = translation;
    
    counter++;
    if(counter == bitLimit){
      bitsToRead++;
      bitLimit = 1 << (bitsToRead - 1);
    }
  }
}

/*To find the number of bits to be read by streamReadBits function.
 *
 *Input: *dict -> the dictionary.
 *
 *Output:i -> the number of bits that is to be read.
 *
 *Throw:  -
 *
 */
int getBitsToRead(Dictionary *dict){
  int i;
  
  for(i = 0; i < dict->size; i++){
    if((1 << i) > dict->size){
      return i;
    }
  }
}

/*To find the translation of a given code if it is within the custom dictionary
 *
 *Input: *dict -> the dictionary.
 *       inputIndex -> input code.
 *
 *Output:translation -> the translation of the input code.
 *
 *Throw:  -
 *
 */
char *getDictTranslation(Dictionary *dict, int inputIndex){
  char *translation = "";
  int index = getIndex(inputIndex);//To find the corresponding index for the custom dictionary

  if((dict->length) < index)
    Throw(ERR_EXCEEDING_DICTIONARY_SIZE);

  translation = dict->entries[index].code;
  
  return translation;
}

/*To find the translation of a given code if it is within the ASCII table (0 - 255)
 *
 *Input: inputIndex -> input code.
 *
 *Output:asciiTranslation -> the translation of the input code.
 *
 *Throw:  -
 *
 */
char getAsciiTranslation(int inputIndex){
	char asciiTranslation;
	
	asciiTranslation = inputIndex;
	
	return asciiTranslation;
}

/*To find the translation of a given code and output through streamWriteBits function.
 *
 *Input: *dict -> the dictionary.
 *       inputIndex -> input code (which is also the dictionary index to be searched).
 *       *out  -> output stream to file.
 *
 *Output: -
 *
 *Throw:  ERR_INVALID_INDEX -> Thrown if index is <0.
 *
 */
void emitCode(Dictionary *dict, int inputIndex, OutStream *out){
  char *translation;
  int i;
  
  if(inputIndex < 256 && inputIndex > 0){
    streamWriteBits(out, inputIndex, bitSize);
  }
  else if(inputIndex == 0){}//Do Nothing
  else if(inputIndex >= 256){
    translation = _getDictTranslation(dict, inputIndex);
    for(i = 0; i < strlen(translation); i++){
      streamWriteBits(out, translation[i], bitSize);
    }
  }
  else{
    Throw(ERR_INVALID_INDEX);
  }
}