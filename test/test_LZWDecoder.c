#include "unity.h"
#include "Dictionary.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"
#include "LZWDecoder.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_LZWDecode(){}

void test_getAsciiTranslation_given_ASCII_a_should_return_char_a(){
	char result;
	
	result = getAsciiTranslation(97);
	
	TEST_ASSERT_EQUAL('a', result);
}

void test_getDictTranslation_given_256_index_0_should_return_ba(){
	Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[0].code = "ba";
  char *result;
	
	result = (char *)getDictTranslation(dictionary, 256);
	
	TEST_ASSERT_EQUAL_STRING("ba", result);
}

void test_getDictTranslation_given_257_index_1_should_return_na(){
	Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[1].code = "na";
  char *result;
	
	result = (char *)getDictTranslation(dictionary, 257);
	
	TEST_ASSERT_EQUAL_STRING("na", result);
}

