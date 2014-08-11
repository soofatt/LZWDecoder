#include "unity.h"
#include "CException.h"
#include "Dictionary.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"
#include "LZWDecoder.h"

char *(*oldGetDictTranslation)(Dictionary *dict, int inputIndex);
// void *(oldLzwDecode)(InStream *in, Dictionary *dict, OutStream *out);

// void newLzwDecode(InStream *in, Dictionary *dict, OutStream *out);
char *newGetDictTranslation(Dictionary *dict, int inputIndex);
void updateDictionary(Dictionary *dict, char code, int index);

void setUp(void){
  oldGetDictTranslation = _getDictTranslation;
  _getDictTranslation = newGetDictTranslation;
  // oldLzwDecode = _lzwDecode;
  // _lzwDecode = newLzwDecode;
}
void tearDown(void){
  _getDictTranslation = oldGetDictTranslation;
  // _lzwDecode = oldLzwDecode;
}

char *newGetDictTranslation(Dictionary *dict, int inputIndex){
  char *translation = "";

  if((dict->length) < inputIndex)
    Throw(ERR_EXCEEDING_DICTIONARY_SIZE);

  translation = dict->entries[inputIndex].code;
  
  return translation;
}

/* void newLzwDecode(InStream *in, Dictionary *dict, OutStream *out){
  int inputCode, dictIndex = 0, bitLimit, bitsToRead, counter = 0;
  char *currentString, *translation, *newDictEntry;
  
  bitsToRead = getBitsToRead(dict);
  inputCode = streamReadBits(in, (bitsToRead - 1));
  emitCode(dict, inputCode, out);
  translation = _getDictTranslation(dict, inputCode);
  currentString = translation;
  bitLimit = 1 << (bitsToRead - 1);
  
  while(inputCode != -1){
    inputCode = streamReadBits(in, bitsToRead);
    
    translation = _getDictTranslation(dict, inputCode);
    
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
} */

void updateDictionary(Dictionary *dict, char code, int index){
  char *codeToAdd = codeNewAndAppend("", code);
  int temp;
  
  temp = dictionaryAdd(dict, codeToAdd, index);
}

/*
 *Input : 0, 1, 2, 3, 4, 2
 *
 *Output : abcdabc
 */
void test_lzwDecode_given_bits_to_read_2_should_increase_to_4(){
	CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(20);
  InStream in;
  OutStream out;
  char *result;
  
  dictionary->size = 0;
	updateDictionary(dictionary, 'a', 0);
	updateDictionary(dictionary, 'b', 1);
	updateDictionary(dictionary, 'c', 2);
	updateDictionary(dictionary, 'd', 3);
  
  streamReadBits_ExpectAndReturn(&in, 2, 0);
  streamWriteBits_Expect(&out, 0, 8);
  streamReadBits_ExpectAndReturn(&in, 3, 1);
  streamWriteBits_Expect(&out, 1, 8);
  streamReadBits_ExpectAndReturn(&in, 3, 2);
  streamWriteBits_Expect(&out, 2, 8);
  streamReadBits_ExpectAndReturn(&in, 3, 3);
  streamWriteBits_Expect(&out, 3, 8);
  streamReadBits_ExpectAndReturn(&in, 3, 4);
  // streamWriteBits_Expect(&out, 0, 8);
  // streamWriteBits_Expect(&out, 1, 8);
  // streamReadBits_ExpectAndReturn(&in, 4, 2);
  // streamWriteBits_Expect(&out, 2, 8);
  // streamReadBits_ExpectAndThrow(&in, 4, END_OF_STREAM);
  
  Try{
    lzwDecode(&in, dictionary, &out);
	}Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
  }
}