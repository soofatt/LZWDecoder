#ifndef Dictionary_H
#define Dictionary_H

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
int dictionaryAdd(Dictionary *dict, char *code, int index);
char *codeNewAndAppend(char *oldCode, char codeToAppend);

#endif // Dictionary_H
