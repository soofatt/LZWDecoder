#include "unity.h"
#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "ErrorCode.h"
#include "LZWDecoder.h"

void setUp(void){}
void tearDown(void){}

void test_lzwDecode_given_code_97_should_decode_into_a(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("LZWDecodeOutput_1.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_1.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
  }
  
  closeInStream(in);
  closeOutStream(out);
  
}

void test_lzwDecode_given_code_98_97_should_decode_into_ba(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("LZWDecodeOutput_2.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_2.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
  }
}

void test_lzwDecode_given_code_98_97_110_should_decode_into_ban(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("LZWDecodeOutput_3.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_3.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
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
  OutStream *out = openOutStream("LZWDecodeOutput_4.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_4.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ab", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("bc", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("cd", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("da", dictionary->entries[3].code);
    TEST_ASSERT_EQUAL_STRING("abc", dictionary->entries[4].code);
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
  OutStream *out = openOutStream("LZWDecodeOutput_5.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_5.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("aa", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("aaa", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("aaaa", dictionary->entries[2].code);
  }
}

/*
 * Input : 98, 97, 110, 257, 259
 *
 * Output : bananana
 *
 */
void test_lzwDecode_case_3_should_decode_into_bananana(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("LZWDecodeOutput_6.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_6.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[3].code);
  }
}

/*
 * Input : 98, 97, 110, 257, 97, 95, 258, 258, 256
 *
 * Output : banana_nanaba
 *
 */
void test_lzwDecode_case_4_should_decode_into_banana_nanaba(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("LZWDecodeOutput_7.txt", "w");
  InStream *in = openInStream("LZWDecodeInput_7.txt", "r");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[3].code);
    TEST_ASSERT_EQUAL_STRING("a_", dictionary->entries[4].code);
    TEST_ASSERT_EQUAL_STRING("_n", dictionary->entries[5].code);
    TEST_ASSERT_EQUAL_STRING("nan", dictionary->entries[6].code);
    TEST_ASSERT_EQUAL_STRING("nab", dictionary->entries[7].code);
  }
}