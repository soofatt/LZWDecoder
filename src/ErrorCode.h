#ifndef ErrorCode_H
#define ErrorCode_H

typedef enum{
  ERR_NO_ERROR,
  ERR_INVALID_INDEX,
  ERR_EXCEEDING_DICTIONARY_SIZE,
  END_OF_STREAM,
  ERR_CANNOT_OPEN_FILE
} ErrorCode;

#endif // ErrorCode_H
