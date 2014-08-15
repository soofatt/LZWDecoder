#include "unity.h"
#include "CException.h"
#include "ErrorCode.h"
#include "OutStream.h"

void setUp(){}

void tearDown(){}
//TEST ASSERT MORE THING IN INSTREAM TEST, OUTSTREAM TEST IF BITINDEX MOVE N IF BITINDEX ROLLOVER FOR NEW BYTE
void test_openOutStream_given_output_test_file_should_write_d_to_file(){
	CEXCEPTION_T e;
  OutStream *out;

  out = openOutStream("OutputTest.txt", "w");
  fputc('d', out->file);
  closeOutStream(out);
}