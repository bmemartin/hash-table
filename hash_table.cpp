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
    int index = getHashVal(key.c_str());
    Item *newItem = new Item();
    newItem->key = key;
    newItem->val = val;
    newItem->next = (table[index]) ? table[index] : NULL;
    table[index] = newItem;
}

void HashTable::remove(string key)
{
    int index = getHashVal(key.c_str());
    Item *item = table[index];
    if(item && item->key == key) {
        table[index] = item->next;
        delete item;
    }
    else {
        bool removed = false;
        while(item && item->next && !removed) {
            if(item->next->key == key) {
                Item *temp = item->next;
                item->next = temp->next;
                delete temp;
                removed = true;
            }
            item = item->next;
        }
    }
}

int& HashTable::operator[](string key)
{
    int index = getHashVal(key.c_str());
    Item *item = table[index];
    while(item && item->key != key)
        item = item->next;
    if(!item) {
        insert(key, -1);
        item = table[index];
    }
    return item->val;
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
