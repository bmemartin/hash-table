#include "hash_table.h"

#include <cstdlib>

HashTable::HashTable()
{
    table = new Item*[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

HashTable::HashTable(const HashTable &other)
{

}

HashTable::~HashTable()
{
    clear();
}

void HashTable::insert(string key, int val)
{

}

void HashTable::remove(string key)
{

}
int temp = 0; //Delete after implementation of operator[]
int& HashTable::operator[](string key)
{
    
    return temp;
}

HashTable& HashTable::operator=(const HashTable &other)
{

}

inline void HashTable::clear()
{
    for(int i = 0; i < TABLE_SIZE; i++) {
        while(table[i]) {
            Item *temp = table[i];
            table[i] = temp->next;
            delete temp;
        }
    }
    delete[] table;
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
