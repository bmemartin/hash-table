/**
* Program Aim: To test the functionality of the HashTable class (hash_table.h & hash_table.cpp)
*
* Author: Benjamin Martin
* Email Address: benjamin.martin2@griffithuni.edu.au
* Student ID: s2846492
*
* Note: Some test results also rely on testers discretion to view
*       outputs for correct functionality.
*/

#include "hash_table.h"

#include <string>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

void readInCitiesTxt(HashTable &table);

bool testConstructDestruct();

bool testInsert();
bool testRemove();

bool testSubscript();

bool testCopyConstructor();
bool testAssignment();

bool testComboFunct();

int main()
{
    int numTests = 0, numPassed = 0;

    numTests++;
    if(testConstructDestruct())
        numPassed++;
    numTests++;
    if(testInsert())
        numPassed++;
    numTests++;
    if(testRemove())
        numPassed++;
    numTests++;
    if(testSubscript())
        numPassed++;
    numTests++;
    if(testCopyConstructor())
        numPassed++;
    numTests++;
    if(testAssignment())
        numPassed++;
    numTests++;
    if(testComboFunct())
        numPassed++;

    cout << "======================================================================" << endl;
    cout << "-->>  Successful Tests: " << numPassed << "/" << numTests << endl;
    cout << "======================================================================" << endl << endl;
}

void readInCitiesTxt(HashTable &table)
{
    ifstream inFile("cities.txt");
    string city;
    int population;
    inFile >> city;
    inFile >> population;
    while(inFile.good()) {
        table[city] = population;
        inFile >> city;
        inFile >> population;
    }
    inFile.close();
}

bool testConstructDestruct()
{
    bool result = true;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testConstructDestruct()" << endl;

    HashTable table;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testInsert()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testInsert()" << endl;

    HashTable table;

    table.insert("Sydney", 4667283);
    table.insert("Melbourne", 4246345);
    table.insert("Devonport", 30330);

    if(table["Sydney"] == 4667283 && table["Melbourne"] == 4246345 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testRemove()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testRemove()" << endl;

    HashTable table;

    table.insert("Sydney", 4667283);
    table.insert("Melbourne", 4246345);
    table.insert("Devonport", 30330);

    table.remove("Melbourne");
    table.remove("Sydney");

    if(table["Sydney"] == -1 && table["Melbourne"] == -1 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testSubscript()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testSubscript()" << endl;

    HashTable table;

    readInCitiesTxt(table);

    if(table["Sydney"] == 4667283 && table["Melbourne"] == 4246345 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testCopyConstructor()
{
    bool result = true;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testCopyConstructor()" << endl;

    HashTable table;

    readInCitiesTxt(table);

    HashTable table2 = table;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testAssignment()
{
    bool result = true;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testAssignment()" << endl;

    HashTable table;

    readInCitiesTxt(table);

    HashTable table2;
    table2 = table;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

bool testComboFunct()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testComboFunct()" << endl;

    HashTable table;

    table.insert("Los Angeles", 3820345);
    table.insert("New York City", 8245123);

    readInCitiesTxt(table);

    HashTable table2 = table;

    bool part1 = (table["New York City"] == 8245123 && table["New York City"] == table2["New York City"] && table["Sydney"] == 4667283) ? true : false;

    table.remove("New York City");
    table.remove("Sydney");

    table2 = table;

    bool part2 = (table["New York City"] == -1 && table["New York City"] == table2["New York City"]) ? true : false;
    bool part3 = (table["Sydney"] == -1 && table2["Los Angeles"] == 3820345) ? true : false;

    if(part1 && part2 && part3)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}
