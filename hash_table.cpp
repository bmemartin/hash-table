#include "hash_table.h"

#include <cstdlib>



int HashTable::getHashVal(const char *key)
{
  unsigned long hash = 5381;
  int c;
  while( (c = *(key++)) )
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  int hashVal = (int)(hash % TABLE_SIZE);
  return hashVal;
}
