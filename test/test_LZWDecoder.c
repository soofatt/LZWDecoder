#include "unity.h"
#include "LZWDecoder.h"

void setUp(void){}

void tearDown(void){}

void test_getTranslation_given_ASCII_a_should_return_char_a(){
	char result;
	
	result = getAsciiTranslation(97);
	
	TEST_ASSERT_EQUAL('a', result);
}

void test_codeNewAndAppend_given_blank_append_a(){
	char *oldCode = "";
	char *result;
	
	result = codeNewAndAppend(oldCode, 'a');
	
	TEST_ASSERT_EQUAL_STRING("a", result);
}

void test_codeNewAndAppend_given_abc_append_d(){
	char *oldCode = "abc";
	char *result;
	
	result = codeNewAndAppend(oldCode, 'd');
	
	TEST_ASSERT_EQUAL_STRING("abcd", result);
}

void test_codeNewAndAppend_given_abc_append_e(){
	char *oldCode = "abc";
	char *result;
	char asciiTranslation;
	
	asciiTranslation = getAsciiTranslation(101);
	result = codeNewAndAppend(oldCode, asciiTranslation);
	
	TEST_ASSERT_EQUAL_STRING("abce", result);
}

void test_dictionaryNew_should_return_dictionary_with_length_4k(){
	Dictionary *dictionary;
	
	dictionary = dictionaryNew(4096);
	
	TEST_ASSERT_NOT_NULL(dictionary);
	TEST_ASSERT_NULL(dictionary->entries[0].code);
	TEST_ASSERT_EQUAL(0, dictionary->entries[0].length);
}