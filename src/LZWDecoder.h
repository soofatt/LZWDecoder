#ifndef LZWDecoder_H
#define LZWDecoder_H

extern char *(*_getDictTranslation)(Dictionary *dict, int inputIndex);

void lzwDecode(InStream *in, Dictionary *dict, OutStream *out);
char getAsciiTranslation(int inputIndex);
char *getDictTranslation(Dictionary *dict, int inputIndex);
void emitCode(Dictionary *dict, int inputIndex, OutStream *out);
int getBitsToRead(Dictionary *dict);

#endif // LZWDecoder_H
