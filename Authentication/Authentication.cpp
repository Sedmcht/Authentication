
#include <iostream>
#include <string>
#include "hash_table.h"

int main()
{
    
    HashTable MyHT;

    
    
    for (int i = 0; i < 50; i++)
    MyHT.add(to_string(i), to_string(i));

    
    for (int i = 0; i < 50; i++)
       cout << MyHT.find(to_string(i)) << endl;
}

