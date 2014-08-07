#ifndef LZWDecoder_H
#define LZWDecoder_H

typedef enum{
  ERR_NO_ERROR,
  END_OF_STREAM
} ErrorCode;

void lzwDecode(InStream *in, Dictionary *dict, OutStream *out);
char getAsciiTranslation(int inputIndex);
char *getDictTranslation(Dictionary *dict, int inputIndex);
void emitCode(Dictionary *dict, int index, OutStream *out);

#endif // LZWDecoder_H
