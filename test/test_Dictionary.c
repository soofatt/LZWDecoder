#include "unity.h"
#include "Dictionary.h"

void setUp(){}
void tearDown(){}

void test_codeNewAndAppend_given_blank_append_a(){
	char *oldCode = "";
	char *result;
	
	result = codeNewAndAppend(oldCode, 'a');
	
	TEST_ASSERT_EQUAL_STRING("a", result);
}

void test_codeNewAndAppend_given_d_append_g(){
	char *oldCode = "d";
	char *result;
	
	result = codeNewAndAppend(oldCode, 'g');
	
	TEST_ASSERT_EQUAL_STRING("dg", result);
}

void test_codeNewAndAppend_given_abc_append_d(){
	char *oldCode = "abc";
	char *result;
	
	result = codeNewAndAppend(oldCode, 'd');
	
	TEST_ASSERT_EQUAL_STRING("abcd", result);
}

void test_dictionaryNew_should_return_dictionary_with_length_4k(){
	Dictionary *dictionary;
	
	dictionary = dictionaryNew(4096);
	
	TEST_ASSERT_NOT_NULL(dictionary);
	TEST_ASSERT_NULL(dictionary->entries[0].code);
	TEST_ASSERT_EQUAL(0, dictionary->entries[0].length);
}

void test_dictionaryAdd_given_na_should_add_into_index_0_should_return_1(){
	Dictionary *dictionary = dictionaryNew(100);
  int result;
	
	result = dictionaryAdd(dictionary, "na", 0);
	
	TEST_ASSERT_EQUAL(1, result);
	TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[0].code);
}

void test_dictionaryAdd_given_ban_should_add_into_index_1_should_return_1(){
	Dictionary *dictionary = dictionaryNew(100);
  int result;
	
	result = dictionaryAdd(dictionary, "ban", 1);
	
	TEST_ASSERT_EQUAL(1, result);
	TEST_ASSERT_EQUAL_STRING("ban", dictionary->entries[1].code);
}

void test_dictionaryAdd_given_nab_and_index_101_should_return_0(){
	Dictionary *dictionary = dictionaryNew(100);
  int result;
	
	result = dictionaryAdd(dictionary, "nab", 101);
	
	TEST_ASSERT_EQUAL(0, result);
}

void test_dictionaryAdd_given_nab_and_index_neg_1_should_return_0(){
	Dictionary *dictionary = dictionaryNew(100);
  int result;
	
	result = dictionaryAdd(dictionary, "nab", -1);
	
	TEST_ASSERT_EQUAL(0, result);
}