#include "unity.h"
#include "CException.h"
#include "Dictionary.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"
#include "LZWDecoder.h"

char *(*oldGetDictTranslation)(Dictionary *dict, int inputIndex);

void setUp(void){
  oldGetDictTranslation = _getDictTranslation;
  _getDictTranslation = newGetDictTranslation;
}
void tearDown(void){
  _getDictTranslation = oldGetDictTranslation;
}

char *newGetDictTranslation(Dictionary *dict, int inputIndex){
  char *translation = "";

  if((dict->length) < inputIndex)
    Throw(ERR_EXCEEDING_DICTIONARY_SIZE);

  translation = dict->entries[inputIndex].code;
  
  return translation;
}

void updateDictionary(Dictionary *dict, char code, int index){
  char *codeToAdd = codeNewAndAppend("", code);
  int temp;
  
  temp = dictionaryAdd(dict, codeToAdd, index);
}

void test_lzwDecode(){
	CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(20);
  InStream in;
  OutStream out;
  char *result;
  
	updateDictionary(dictionary, 'a', 0);
	updateDictionary(dictionary, 'b', 1);
	updateDictionary(dictionary, 'c', 2);
	updateDictionary(dictionary, 'd', 3);
  
  Try{
    lzwDecode(&in, dictionary, &out);
	}Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
  }
}