#include <iostream>
#include <string>
#include "Lab_2_cpp.h"
using namespace hash;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    HashTable<int> hashTable;

    hashTable.insert(1, 100);
    hashTable.insert(2, 200);
    hashTable.insert(3, 300);
    hashTable.insert(41, 1300);
    hashTable.insert(52, 343);
    hashTable.insert(150, 3403);
    hashTable.insert(65, 3404);
    hashTable.insert(73, 3555);
  /*  hashTable.insert(65, 3405);
    hashTable.insert(65, 2);
    hashTable.insert(52, 0);*/
    hashTable.print();

    cout << endl;

    string roman1 = "CMX";
    string roman2 = "XVIII";
    string roman3 = "XLII";

    int hashResult1 = hashTable.hash_to_roman(roman1);
    int hashResult2 = hashTable.hash_to_roman(roman2);
    int hashResult3 = hashTable.hash_to_roman(roman3);

    cout << "Римское число " << roman1 << ": " << hashResult1 << endl;
    cout << "Римское число " << roman2 << ": " << hashResult2 << endl;
    cout << "Римское число " << roman3 << ": " << hashResult3 << endl;

    cout << endl;
    cout << endl;


    auto counter_collisions = hashTable.count(52);
    cout << counter_collisions;

    return 0;
}
