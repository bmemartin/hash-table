#include "hash_table.h"

#include <cstdlib>

HashTable::HashTable()
{

}

HashTable::HashTable(const HashTable &other)
{

}

HashTable::~HashTable()
{

}

void HashTable::insert(string key, int val)
{

}

void HashTable::remove(string key)
{

}

int& HashTable::operator[](string key)
{

}

HashTable& HashTable::operator=(const HashTable &other)
{

}

inline void HashTable::clear()
{

}

int HashTable::getHashVal(const char *key)
{
  unsigned long hash = 5381;
  int c;
  while( (c = *(key++)) )
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  int hashVal = (int)(hash % TABLE_SIZE);
  return hashVal;
}
