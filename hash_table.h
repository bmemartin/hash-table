#include <string>

using std::string;

#define TABLE_SIZE 30

class HashTable
{
  struct Item {
    string key;
    int val;
    Item* next;
  };

  Item **table;

public:

  HashTable();
  HashTable(const HashTable &other);
  ~HashTable();

  void insert(string key, int val);
  void remove(string key);

  int& operator[](string key);

  HashTable& operator=(const HashTable &other);

private:
  inline void clear();
  int getHashVal(const char *key);

};
