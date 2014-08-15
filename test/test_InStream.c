#include "unity.h"
#include "CException.h"
#include "ErrorCode.h"
#include "InStream.h"

void setUp(){}

void tearDown(){}

void test_openInStream_given_nonexistant_file_should_throw_error(){
	CEXCEPTION_T e;
  InStream *in;

  Try{
    in = openInStream("NonExistant.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
  }
}

void test_openInStream_given_existant_file_should_read_a(){
	CEXCEPTION_T e;
  InStream *in;
  int result;

  Try{
    in = openInStream("InputTest.txt", "r");
    result = fgetc(in->file);
    closeInStream(in);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
  }

  TEST_ASSERT_EQUAL('a', result);
}

void test_openInStream_given_existant_file_should_read_6(){
	CEXCEPTION_T e;
  InStream *in;
  int result;

  Try{
    in = openInStream("InputTest_2.txt", "r");
    result = fgetc(in->file);
    closeInStream(in);
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
  }

  TEST_ASSERT_EQUAL('6', result);
}

void xtest_streamReadBits_given_a_0x61_should_return_a(){
	CEXCEPTION_T e;
  InStream *in;
  int result;

  Try{
    in = openInStream("InputTest_3.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
  }

  result = streamReadBits(in, 8);
  closeInStream(in);

  TEST_ASSERT_EQUAL('a', result);
}

void test_streamReadBits_given_a_0x100_should_return_256(){
	CEXCEPTION_T e;
  InStream *in;
  int result;

  Try{
    in = openInStream("InputTest_4.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
  }

  result = streamReadBits(in, 9);
  closeInStream(in);

  TEST_ASSERT_EQUAL(256, result);
}

void test_streamReadBit_given_0x97_should_return_1(){
	int result;

  result = streamReadBit(0x97);

  TEST_ASSERT_EQUAL(1, result);
}

void test_streamReadBit_given_0x37_should_return_0(){
	int result;

  result = streamReadBit(0x37);

  TEST_ASSERT_EQUAL(0, result);
}