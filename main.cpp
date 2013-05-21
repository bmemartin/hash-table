#include "hash_table.h"

#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int main()
{
  HashTable table;

  ifstream inFile("cities.txt");
  string city;
  int population;
  inFile >> city;
  inFile >> population;
  while(inFile.good())
  {
    table[city] = population;

    inFile >> city;
    inFile >> population;
  }
  inFile.close();

  cout << "Sydney should read 4667283 ---- " << table["Sydney"] << endl;
  cout << "Melbourne should read 4246345 ---- " << table["Melbourne"] << endl;
  cout << "Devonport should read 30330 ---- " << table["Devonport"] << endl;

}
