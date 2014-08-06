#ifndef LZWDecoder_H
#define LZWDecoder_H

void LZWDecode(InStream *in, Dictionary *dict, OutStream *out);
char getAsciiTranslation(int inputIndex);
char *getDictTranslation(Dictionary *dict, int inputIndex);
void emitCode(Dictionary *dict, int index, OutStream *out);

#endif // LZWDecoder_H
