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

/**
 * The "main" function of the program calls test functions to test
 * the functionality of the HashTable class.
 *
 * It returns a whole number (int).
 * It takes no parameters.
 */
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

/**
 * readInCitiesTxt function reads in cities and their populations from a txt file and populates the
 * passed HashTable with the data read.
 *
 * It returns nothing.
 * It takes one parameter; a HashTable object
 */
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

/**
 * testConstructDestruct creates a HashTable object which is deleted on function end.
 *
 * The test passes if the object is created.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
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

/**
 * testInsert inserts three cities and their populations into a HashTable.
 *
 * The test passes if the cities populations are read back from the HashTable correctly.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
bool testInsert()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testInsert()" << endl;

    HashTable table;

    table.insert("Sydney", 4667283);
    table.insert("Melbourne", 4246345);
    table.insert("Devonport", 30330);

    cout << "Sydney should read 4667283 ---- " << table["Sydney"] << endl;
    cout << "Melbourne should read 4246345 ---- " << table["Melbourne"] << endl;
    cout << "Devonport should read 30330 ---- " << table["Devonport"] << endl;

    if(table["Sydney"] == 4667283 && table["Melbourne"] == 4246345 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

/**
 * testRemove inserts three cities and their populations into a HashTable and removes two of the inserted cities.
 *
 * The test passes if the cities are removed correctly.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
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

    cout << "Sydney should read -1 ---- " << table["Sydney"] << endl;
    cout << "Melbourne should read -1 ---- " << table["Melbourne"] << endl;
    cout << "Devonport should read 30330 ---- " << table["Devonport"] << endl;

    if(table["Sydney"] == -1 && table["Melbourne"] == -1 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

/**
 * testSubscript calls the readInCitiesTxt function which uses the subscript operator for setting items within
 * a HashTable.
 *
 * The test passes if the cities and populations were stored and accessed correctly.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
bool testSubscript()
{
    bool result = false;
    cout << "======================================================================" << endl;
    cout << "-->> Running: testSubscript()" << endl;

    HashTable table;

    readInCitiesTxt(table);

    cout << "Sydney should read 4667283 ---- " << table["Sydney"] << endl;
    cout << "Melbourne should read 4246345 ---- " << table["Melbourne"] << endl;
    cout << "Devonport should read 30330 ---- " << table["Devonport"] << endl;

    if(table["Sydney"] == 4667283 && table["Melbourne"] == 4246345 && table["Devonport"] == 30330)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}

/**
 * testCopyConstructor calls the readInCitiesTxt function to enter data into the HashTable and calls
 * the copy constructor to copy "table" contents into "table2".
 *
 * The test always passes. It is up to testers discretion to view outputs for correct functionality.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
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

/**
 * testAssignment calls the readInCitiesTxt function to enter data into the HashTable and uses the assignment
 * operator to copy "table" contents into "table2".
 *
 * The test always passes. It is up to testers discretion to view outputs for correct functionality.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
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

/**
 * testComboFunct tests all the functions of the HashTable class within one test. Different HashTable functions
 * are called and combined into a more real world scenario.
 *
 * The test passes if the cities and populations were stored, accessed, removed, and copied correctly.
 * Test checks are performed at different times throughout the function.
 *
 * It returns a boolean value (true/false).
 * It takes no parameters.
 */
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

    cout << "New York City should read 8245123 ---- " << table["New York City"] << endl;
    cout << "New York City (table2) should read 8245123 ---- " << table2["New York City"] << endl;
    cout << "Sydney should read 4667283 ---- " << table["Sydney"] << endl;

    bool part1 = (table["New York City"] == 8245123 && table["New York City"] == table2["New York City"] && table["Sydney"] == 4667283) ? true : false;

    table.remove("New York City");
    table.remove("Sydney");

    table2 = table;

    cout << "New York City should read -1 ---- " << table["New York City"] << endl;
    cout << "New York City (table2) should read -1 ---- " << table2["New York City"] << endl;
    cout << "Sydney should read -1 ---- " << table["Sydney"] << endl;
    cout << "Los Angeles (table2) should read 3820345 ---- " << table2["Los Angeles"] << endl;

    bool part2 = (table["New York City"] == -1 && table["New York City"] == table2["New York City"]) ? true : false;
    bool part3 = (table["Sydney"] == -1 && table2["Los Angeles"] == 3820345) ? true : false;

    if(part1 && part2 && part3)
        result = true;

    cout << "-->> Result: " << ((result) ? "Passed" : "Failed" )<< endl;
    cout << "======================================================================" << endl << endl << endl;
    return result;
}
