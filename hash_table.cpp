#include "hash_table.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

#define DEBUG // Comment out to disable debug mode

HashTable::HashTable()
{
    table = new Item*[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

HashTable::HashTable(const HashTable &other)
{
    table = new Item*[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++) {
        Item *original = other.table[i];

        if(original) { // Create a copy of the first item if one exists
            Item *copy = new Item();
            table[i] = copy; // Set first item to table index
            copy->key = original->key;
            copy->val = original->val;

            while(original->next) { // Create copies of any additional items found
                original = original->next;
                Item *nextItem = new Item();
                copy->next = nextItem; // Set the previous item's link to this new item
                copy = copy->next;
                copy->key = original->key;
                copy->val = original->val;
            }
            copy->next = NULL; // Set last item's link in chain to NULL
        }
        else {
            table[i] = NULL;
        }
    }

    #ifdef DEBUG
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "--------------------  Copy Constructor  --------------------" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << std::setw(6) << std::left << "I";
        std::cout << std::setw(30) << std::left << "Original";
        std::cout << std::setw(30) << std::left << "Copy" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        for(int i = 0; i < TABLE_SIZE; i++) {
            Item *originalTable = other.table[i];
            Item *copyTable = table[i];
            while(originalTable) {
                std::cout << std::setw(6) << std::left << i;
                std::cout << std::setw(30) << std::left << originalTable->key;
                std::cout << std::setw(30) << std::left << copyTable->key << std::endl;
                originalTable = originalTable->next;
                copyTable = copyTable->next;
            }
        }
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif /* DEBUG */
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
    if(this != &other) {
        clear();

        table = new Item*[TABLE_SIZE];
        for(int i = 0; i < TABLE_SIZE; i++) {
            Item *original = other.table[i];

            if(original) { // Create a copy of the first item if one exists
                Item *copy = new Item();
                table[i] = copy; // Set first item to table index
                copy->key = original->key;
                copy->val = original->val;

                while(original->next) { // Create copies of any additional items found
                    original = original->next;
                    Item *nextItem = new Item();
                    copy->next = nextItem; // Set the previous item's link to this new item
                    copy = copy->next;
                    copy->key = original->key;
                    copy->val = original->val;
                }
                copy->next = NULL; // Set last item's link in chain to NULL
            }
            else {
                table[i] = NULL;
            }
        }
    }

    #ifdef DEBUG
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "------------------- Assignment Operator --------------------" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << std::setw(6) << std::left << "I";
        std::cout << std::setw(30) << std::left << "Original";
        std::cout << std::setw(30) << std::left << "Copy" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        for(int i = 0; i < TABLE_SIZE; i++) {
            Item *originalTable = other.table[i];
            Item *copyTable = table[i];
            while(originalTable) {
                std::cout << std::setw(6) << std::left << i;
                std::cout << std::setw(30) << std::left << originalTable->key;
                std::cout << std::setw(30) << std::left << copyTable->key << std::endl;
                originalTable = originalTable->next;
                copyTable = copyTable->next;
            }
        }
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif /* DEBUG */

    return *this;
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
