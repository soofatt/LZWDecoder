#include "unity.h"
#include "CException.h"
#include "Dictionary.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"
#include "LZWDecoder.h"

void setUp(void){}
void tearDown(void){}

void test_emitCode_given_index_97_should_translate_to_a_and_output_a(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream out;
  int index = 97;
  
  streamWriteBits_Expect(&out, 97, 8);
  
  Try{
    emitCode(dictionary, index, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_EXCEEDING_DICTIONARY_SIZE, e);
  }
}

void test_emitCode_given_index_neg_1_should_throw_error(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream out;
  int index = -1;
  
  Try{
    emitCode(dictionary, index, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_INVALID_INDEX, e);
  }
}

void test_emitCode_given_index_256_should_translate_to_ab_and_output_a_b(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[0].code = "ab";
  OutStream out;
  int index = 256;
  
   streamWriteBits_Expect(&out, 97, 8);
   streamWriteBits_Expect(&out, 98, 8);
  
  Try{
    emitCode(dictionary, index, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_EXCEEDING_DICTIONARY_SIZE, e);
  }
}

void test_emitCode_given_index_257_should_translate_to_nan_and_output_nan(){
  Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[1].code = "nan";
  OutStream out;
  int index = 257;
  
  streamWriteBits_Expect(&out, 110, 8);
  streamWriteBits_Expect(&out, 97, 8);
  streamWriteBits_Expect(&out, 110, 8);
  
  emitCode(dictionary, index, &out);
}

void test_lzwDecode_given_code_97_should_decode_into_a(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream out;
  InStream in;
   
  streamReadBits_ExpectAndReturn(&in, 8, 97);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndThrow(&in, 9, END_OF_STREAM);
  
  Try{
    lzwDecode(&in, dictionary, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
    printf("End of stream");
  }
}

void test_lzwDecode_given_code_98_97_110_should_decode_into_ban(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream out;
  InStream in;
   
  streamReadBits_ExpectAndReturn(&in, 8, 98);
  streamWriteBits_Expect(&out, 98, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 97);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 110);
  streamWriteBits_Expect(&out, 110, 8);
  streamReadBits_ExpectAndThrow(&in, 9, END_OF_STREAM);
  
  Try{
    lzwDecode(&in, dictionary, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
    printf("End of stream");
  }
}

/*
 * Input : 97, 98, 99, 100, 256, 99
 *
 * Output : abcdabc
 *
 */
void test_lzwDecode_case_1_should_decode_into_abcdabc(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream out;
  InStream in;
   
  streamReadBits_ExpectAndReturn(&in, 8, 97);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 98);
  streamWriteBits_Expect(&out, 98, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 99);
  streamWriteBits_Expect(&out, 99, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 100);
  streamWriteBits_Expect(&out, 100, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 256);
  streamWriteBits_Expect(&out, 97, 8);
  streamWriteBits_Expect(&out, 98, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 99);
  streamWriteBits_Expect(&out, 99, 8);
  streamReadBits_ExpectAndThrow(&in, 9, END_OF_STREAM);
  
  Try{
    lzwDecode(&in, dictionary, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
    TEST_ASSERT_EQUAL_STRING("ab", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("bc", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("cd", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("da", dictionary->entries[3].code);
    TEST_ASSERT_EQUAL_STRING("abc", dictionary->entries[4].code);
    printf("End of stream");
  }
}

/*
 * Input : 97, 256, 257, 97
 *
 * Output : aaaaaaa
 *
 */
void test_lzwDecode_case_2_should_decode_into_aaaaaaa(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream out;
  InStream in;
   
  streamReadBits_ExpectAndReturn(&in, 8, 97);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 256);
  streamWriteBits_Expect(&out, 97, 8);
  streamWriteBits_Expect(&out, 97, 8);
   streamReadBits_ExpectAndReturn(&in, 9, 257);
  streamWriteBits_Expect(&out, 97, 8);
  streamWriteBits_Expect(&out, 97, 8);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndReturn(&in, 9, 97);
  streamWriteBits_Expect(&out, 97, 8);
  streamReadBits_ExpectAndThrow(&in, 9, END_OF_STREAM);
  
  Try{
    lzwDecode(&in, dictionary, &out);
  }Catch(e){
    TEST_ASSERT_EQUAL(END_OF_STREAM, e);
    TEST_ASSERT_EQUAL_STRING("aa", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("aaa", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("aaaa", dictionary->entries[2].code);
    printf("End of stream");
  }
}

void test_getAsciiTranslation_given_ASCII_a_should_return_char_a(){
	char result;
	
	result = getAsciiTranslation(97);
	
	TEST_ASSERT_EQUAL('a', result);
}

void test_getDictTranslation_given_256_index_0_should_return_ba(){
	Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[0].code = "ba";
  char *result;
	
	result = getDictTranslation(dictionary, 256);
	
	TEST_ASSERT_EQUAL_STRING("ba", result);
}

void test_getDictTranslation_given_257_index_1_should_return_na(){
	Dictionary *dictionary = dictionaryNew(100);
  dictionary->entries[1].code = "na";
  char *result;
	
	result = getDictTranslation(dictionary, 257);
	
	TEST_ASSERT_EQUAL_STRING("na", result);
}

void test_getDictTranslation_given_258_index_2_should_return_NULL(){
	Dictionary *dictionary = dictionaryNew(100);
  char *result;
	
	result = getDictTranslation(dictionary, 258);
	
	TEST_ASSERT_EQUAL_STRING(NULL, result);
}

void test_getDictTranslation_given_258_index_2_smaller_than_dict_length_should_throw_error(){
	CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(1);
  char *result;
	
  Try{
    result = getDictTranslation(dictionary, 258);
	}Catch(e){
    TEST_ASSERT_EQUAL(ERR_EXCEEDING_DICTIONARY_SIZE, e);
  }
}