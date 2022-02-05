#include <iostream>
#include "HashRBTree.h"
#include "function.h"

using namespace std;

int main(int argc, char const *argv[])
{
    HashRBTree obj;
    // Funzione che si occupa della lettura da file
    obj = readFromFile();
    // Menu
    menu();
    return 0;
}