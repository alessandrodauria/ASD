#ifndef FUNCTION_H
#define FUNCTION_H
#include <fstream>
#include "Node.h"
#include "HashRBTree.h"

using namespace std;

// Function che legge riga per riga dal file e riempie
// la mia struttura dati verificando se ci sono
// le collisioni.

HashRBTree readFromFile()
{
    HashRBTree obj;
    int ch, key, keyId;
    int y = 0;
    Node *nodo = new Node;
    ifstream fileName("input0_1_1.txt");
    string val, line;

    if (fileName.is_open())
    {
        // Faccio la lettura del file
        while (getline(fileName, line, ','))
        {
            // Prendo la chiave
            key = atoi(line.c_str() + 1);
            getline(fileName, line);
            // Prendo il valore
            val = line.substr();
            // TODO: ROMOzione ultio carattere
            val.erase(9, 10);
            //  rimuovo l'ultimo carattere dopo la stringa

            // val.erase(remove(val.begin(), val.end(), '>'));

            //  Calcolo l'id del nodo con la HashFunction
            keyId = obj.hashingFunction(key);

            nodo->setId(keyId);
            nodo->setKey(key);
            nodo->setVal(val);

            cout << "KEY: " << key << "    Val: " << val << endl
                 << endl;

            // Verifico se ci sono le collisioni
            // se è presente concateno nella lista <key, val>,
            // altrimenti faccio l'inserimento nel'albero RB
            if (obj.TreeSearch(nodo)) // O(log N)
            {
                cout << "->     Collisione id: " << keyId << endl
                     << endl;
                cout << "--------------" << endl;
                // Inserisco in lista
                obj.TreeSearch(nodo)->insertNode(key, val); // O(log N) + O(1)
                obj.TreeSearch(nodo)->printList();
                cout << endl;
            }
            else
            {
                // Altrimenti inserisco nell'albero
                // confrontando i KeyId
                obj.insert(keyId, key, val); // O(log N)
            }
        }
        fileName.close();
    }
    else
    {
        cout << "Error";
    }
    return obj;
}

void menu()
{
    int ch, key, keyId;
    int y = 0;
    Node *nodo = new Node;
    HashRBTree obj;

    string val, line;
    do
    {
        cout << "\n\t HASHRB TREE\n ";
        cout << "\n 1. Insert";
        cout << "\n 2. Search";
        cout << "\n 3. Delete";
        cout << "\n 4. Display the tree ";
        cout << "\n 5. Display List ";
        cout << "\n 6. Exit ";
        cout << "\nEnter Your Choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            // insert
            cout << "\n\n-------------------";
            cout << endl
                 << "INSERT NODE: " << endl;
            cout << "-------------------\n\n"
                 << endl;
            cout << "Insert KEY: ";
            cin >> key;

            cout << "insert VALUE: ";
            cin >> val;
            // Calcolo L'ID della key
            keyId = obj.hashingFunction(key);

            nodo->setId(obj.hashingFunction(key));
            nodo->setKey(key);
            nodo->setVal(val);

            // Verifico se ci sono le collisioni
            // se è presente concateno nella lista <key, val>,
            // altrimenti faccio l'inserimento nel'albero RB
            if (obj.TreeSearch(nodo)) // O(log N)
            {

                cout << "\n\tCOLLISION DETECTED ! " << endl;
                // Inserisco in lista
                obj.TreeSearch(nodo)->insertNode(key, val);
                // O(log N) + O(1)
                cout << "\n\tVALUE INSERED WITH ID: " << nodo->getId() << " ! " << endl;
            }
            else
            {
                // inserisco nell'albero
                obj.insert(keyId, key, val); // O(log N)

                cout << "\n\tVALUE INSERED WITH ID: " << nodo->getId() << " ! " << endl;
            }

            break;
        case 2:
            cout << "\n\n-------------------";
            cout << endl
                 << "SEARCH NODE: " << endl;
            cout << "-------------------\n\n"
                 << endl;

            cout << "Insert KEY: ";
            cin >> key;

            cout << "Insert VALUE: ";
            cin >> val;

            keyId = obj.hashingFunction(key);
            nodo->setId(keyId);
            nodo->setKey(key);
            nodo->setVal(val);

            //  verifico se è presente < Key, Val >

            if (obj.TreeSearchKey(nodo)) // O(log N)
            {
                cout << "\n\tFOUND WITH ID: " << nodo->getId() << " ! " << endl;
            }
            else if (obj.TreeSearch(nodo)) // O(log N)
            {

                obj.TreeSearch(nodo)->search(nodo); // O(log N) + O(N) = O(log N + N )
            }
            else
            {
                cout << "\n\tNOT FOUND!" << endl;
            }
            break;
        case 3:
            cout << "\n\n-------------------";
            cout << endl
                 << "DELETE NODE: " << endl;
            cout << "-------------------\n\n"
                 << endl;

            cout << "Insert KEY: ";
            cin >> key;

            cout << "Insert VALUE: ";
            cin >> val;

            keyId = obj.hashingFunction(key);

            nodo->setId(keyId);
            nodo->setKey(key);
            nodo->setVal(val);

            obj.remove(nodo); // O(log N)

            break;
        case 4:

            obj.disp();

            break;
        case 5:
            cout << "\n\n-------------------";
            cout << endl
                 << "PRINT LIST OF NODE: " << endl;
            cout << "-------------------\n\n"
                 << endl;
            cout << "Insert KEY: ";
            cin >> key;

            keyId = obj.hashingFunction(key);

            if (obj.TreeSearch(nodo))
            {
                obj.TreeSearch(nodo)->printList();
            }
            else
            {
                cout << "Node not found";
                break;
            }

            break;
        case 6:

            y = 1;
            break;
        default:
            cout << "\nEnter a Valid Choice.";
        }
        cout << endl;

    } while (y != 1);
}
// Menu

#endif