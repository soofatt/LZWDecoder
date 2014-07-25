#ifndef LZWDecoder_H
#define LZWDecoder_H

typedef struct {
	char *code;
	int length;
}DictionaryEntry;

typedef struct {
	DictionaryEntry *entries;
	int length;
}Dictionary;

Dictionary *dictionaryNew(int length);
void dictionaryDel(Dictionary *dict);
void dictionaryAdd(Dictionary *dict, char *code, int index);
char getAsciiTranslation(int input);
char *codeNewAndAppend(char *oldCode, char codeToAppend);

#endif // LZWDecoder_H
