/**
 * Function implementations for hash_table.h
 *
 * Author: Benjamin Martin
 * Email Address: benjamin.martin2@griffithuni.edu.au
 * Student ID: s2846492
 */

#include "hash_table.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

#define DEBUG // Comment out to disable debug mode

/**
 * The constructor initialises the data member "table", our hash table.
 * Table is an array that can hold memory addresses, pointers, to Items.
 *
 * It returns nothing.
 * It takes no parameters.
 */
HashTable::HashTable()
{
    table = new Item*[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

/**
 * The copy constructor performs a deep copy of data from one hash table to this one.
 * Since the hash table contains pointers a deep copy ensures that the data is copied and
 * not just the memory addresses.
 *
 * It returns nothing.
 * It takes one parameter; a reference to another hash table which can only be read from.
 */
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

/**
 * The destructor calls the clear function
 *
 * It returns nothing.
 * It takes no parameters.
 */
HashTable::~HashTable()
{
    clear();
}

/**
 * The insert function creates an Item object at a hashed index, calculated through getHashVal function,
 * of the hash table. Each Item contains it's key, value and a memery address to the next Item object.
 *
 * It returns nothing.
 * It takes two parameters; a string containing a key and an int containing the value related to the key.
 */
void HashTable::insert(string key, int val)
{
    int index = getHashVal(key.c_str());
    bool useExisting = (table[index] && table[index]->val < 0) ? true : false;
    Item *newItem = (useExisting) ? table[index] : new Item();
    newItem->key = key;
    newItem->val = val;
    if(!useExisting)
        newItem->next = (table[index]) ? table[index] : NULL;
    table[index] = newItem;
}

/**
 * The remove function looks for a specific Item and if found deletes it from the hash table.
 *
 * It returns nothing.
 * It takes one parameter; a string containing a key.
 */
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

/**
 * Overloading the subscript operator allows Items to be retrieved or inserted with ease.
 * The hash table is searched for the supplied key, if it is not found then an item with that key is created.
 * The found Item or created Item's value is passed back via reference.
 *
 * It returns a reference to an int (memory address).
 * It takes one parameter; a string containing a key.
 */
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

/**
 * The overloaded assignment operator now performs a deep copy of data from one hash table to this one.
 * Since the hash table contains pointers a deep copy ensures that the data is copied and
 * not just the memory addresses.
 *
 * It returns nothing.
 * It takes one parameter; a reference to another hash table which can only be read from.
 */
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

/**
 * The clear function cycles through the hash table and any Item lists freeing each item
 * and then the table from the heap.
 *
 * It returns nothing.
 * It takes no parameters.
 */
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

/**
 * The getHashVal function calculates a hashed value (int) from a provided key.
 *
 * It returns an int.
 * It takes one parameters; char pointer (memory address).
 */
int HashTable::getHashVal(const char *key)
{
    unsigned long hash = 5381;
    int c;
    while( (c = *(key++)) )
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    int hashVal = (int)(hash % TABLE_SIZE);
    return hashVal;
}
