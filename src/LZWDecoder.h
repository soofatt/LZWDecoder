#ifndef LZWDecoder_H
#define LZWDecoder_H

typedef enum{
  ERR_NO_ERROR,
  ERR_INVALID_INDEX,
  ERR_EXCEEDING_DICTIONARY_SIZE,
  END_OF_STREAM
} ErrorCode;

extern char *(*_getDictTranslation)(Dictionary *dict, int inputIndex);

void lzwDecode(InStream *in, Dictionary *dict, OutStream *out);
char getAsciiTranslation(int inputIndex);
char *getDictTranslation(Dictionary *dict, int inputIndex);
void emitCode(Dictionary *dict, int index, OutStream *out);
int getUpperLimit(Dictionary *dict);

#endif // LZWDecoder_H
