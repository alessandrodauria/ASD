#ifndef HASHRBTREE_H
#define HASHRBTREE_H

#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include "Node.h"

using namespace std;

class HashRBTree
{
private:
    int size;
    Node *root;

    void leftRotate(Node *node);
    void rightRotate(Node *node);
    void removeNode(Node *node);
    void display(Node *nodo);

public:
    HashRBTree() : root(nullptr), size(0){};
    // Hash function per calcolare l'Id
    int hashingFunction(int key);
    // Function che si occupa dell'inserimento di un nodo
    void insert(int &id, int &key, string &val);
    int cmp(int a, int b);
    // Function di ricerca
    Node *TreeSearch(Node *nodo);
    Node *TreeSearchKey(Node *nodo);
    bool remove(Node *nodo);

    // Stampa la struttura sullo schermo
    // con le liste dei rispettivi nodi
    void disp();
};

// Per il calcolo dell'ID utilizzo la hash function e in particolare
// Il metodo della moltiplicazione che opera in due passi:
// - si moltiplica la chiave per una costante A, tale che 0 < A < 1
// e si estrae la parte frazionaria del risultato
// - si moltiplica questo valore per m e si prende la parte intera inferiore
int HashRBTree::hashingFunction(int key)
{
    float A = 0.6180339887;
    int p = 14, w = 32, s, x, m;
    m = pow(2, p);

    s = floor(A * m);
    x = key * s;

    return x >> (w - p);
};

// L’inserimento di un nodo si divide in due fasi:
// 1. Prima viene inserito il
// nodo nell’albero come in un normale
// ABR con l’unica differenza che il nodo appena
// inserito viene colorato di rosso
//
// 2. Poi vengono ripristinate le proprietà dell'albero Rosso-Nero;
// ciò avviene nel while

void HashRBTree::insert(int &id, int &key, string &value) // O(logn N)
{
    Node *node = new Node;
    Node *parent = new Node;
    Node *z = new Node;

    parent = NULL;
    node = root;

    // Cerca la posizione dovve inserire
    while (node)
    {
        parent = node;
        if (id < node->getId())
        {
            node = node->getLeft();
        }
        else
        {
            node = node->getRight();
        }
    }

    // Se parent è nullo inserisco nella radice
    if (!parent)
    {
        z = root = new Node;
        z->setId(id);
        z->setKey(key);
        z->setVal(value);
        z->setColor(BLACK);
        z->setParent(NULL);
        z->setLeft(NULL);
        z->setRight(NULL);
    }
    else
    {
        z = new Node;
        z->setId(id);
        z->setKey(key);
        z->setVal(value);
        z->setColor(RED);
        z->setParent(parent);
        z->setLeft(NULL);
        z->setRight(NULL);

        // Verifico se l'ID è minore dell'Id presente nell'albero
        if (z->getId() < parent->getId())
        {
            // se è minore inserisco a sinistra.
            parent->setLeft(z);
        }
        else
        {
            // se è maggiore inserisco a destra.
            parent->setRight(z);
        }
    }

    Node *uncle;
    bool side;

    // FIX-UP | Complessità O(log N)
    // Fase in cui vengono ripristinate le proprietà degli alberi Rosso-Neri
    while (z->getParent() && z->getParent()->getColor() == RED)
    {
        if ((side = (z->getParent() == z->getParent()->getParent()->getLeft())))
        {

            uncle = z->getParent()->getParent()->getRight();
        }
        else
        {
            uncle = z->getParent()->getParent()->getLeft();
        }
        // Caso 1 " Zio di Z è [ROSSO] "
        // - Coloro di nero il padre di Z
        // - Coloro di nero lo zio
        // - Coloro di rosso il nonno di Z
        // - sposto il puntatore, facendo del nonno di Z il nuovo Z
        if (uncle && uncle->getColor() == RED)
        {
            z->getParent()->setColor(BLACK);
            uncle->setColor(BLACK);
            z->getParent()->getParent()->setColor(RED);
            z = z->getParent()->getParent();
        }
        else
        {
            // Caso 2 " Zio di Z è NERO e Z è figlio destro"
            // Qui trasformo il caso 2 in caso 3 richiamando la funzione
            // leftRotate() del nodo Z, facendolo diventare figlio sinistro.
            // La variabile " side " mi dice se è figlio sinistro o destro e in
            // base a quello applico la rotazione giusta.
            // Infatti se mi trovo nel Caso 3 " Zio di Z è NERO e Z è figlio sinistro "
            // Effettuo una rotazione a destra richimando rightRotate()
            if (z == (side ? z->getParent()->getRight() : z->getParent()->getLeft()))
            {
                z = z->getParent();
                side ? leftRotate(z) : rightRotate(z);
            }
            // Caso 3 "Zio di Z è NERO e Z è figlio sinistro "
            // - Colorare di nero il padre di Z
            // - Coloro di rosso il nonno di Z
            // - effettuare una rotazione a destro del nonno di Z
            z->getParent()->setColor(BLACK);
            z->getParent()->getParent()->setColor(RED);
            side ? rightRotate(z->getParent()->getParent()) : leftRotate(z->getParent()->getParent());
        }
    }

    root->setColor(BLACK);
}

// rotazione a sinistra
void HashRBTree::leftRotate(Node *node)
{
    assert(node->getRight() != nullptr);
    Node *temp = node->getRight();
    // aggiorna i due nodi
    node->setRight(temp->getLeft());
    if (temp->getLeft() != nullptr)
        temp->getLeft()->setParent(node);
    temp->setLeft(node);
    temp->setParent(node->getParent());
    node->setParent(temp);

    // aggiorna 'parent'
    if (root == node)
    {
        root = temp;
        return;
    }
    if (temp->getParent()->getLeft() == node)
        temp->getParent()->setLeft(temp);
    else
        temp->getParent()->setRight(temp);
}

//  rotazione a destra

void HashRBTree::rightRotate(Node *node)
{
    assert(node->getLeft() != nullptr);
    Node *temp = node->getLeft();

    // aggiorna i due nodi
    node->setLeft(temp->getRight());
    if (temp->getRight() != nullptr)
        temp->getRight()->setParent(node);
    temp->setRight(node);
    temp->setParent(node->getParent());
    node->setParent(temp);

    // aggiorna 'parent'
    if (root == node)
    {
        root = temp;
        return;
    }
    if (temp->getParent()->getLeft() == node)
        temp->getParent()->setLeft(temp);
    else
        temp->getParent()->setRight(temp);
}

void HashRBTree::disp()
{
    display(root);
}
void HashRBTree::display(Node *p)
{
    if (root == NULL)
    {
        cout << "\nEmpty Tree.";
        return;
    }
    if (p != NULL)
    {
        cout << "\n--------------------- ";
        cout << "\n\t NODE: ";
        cout << "\n ID: " << p->getId();
        cout << "\n Key: " << p->getKey();
        cout << "\n Val: " << p->getVal();
        cout << "\n Colour: ";

        if (p->getColor() == BLACK)
            cout << "Black";
        else
            cout << "Red";

        cout << "\n\n List of node: " << endl;
        p->printList();
        cout << endl;
        /* if (p->getParent() != NULL)
            cout << "\n Parent: " << p->getParent()->getKey();
        else
            cout << "\n There is no parent of the node.  ";
        if (p->getRight() != NULL)
            cout << "\n Right Child: " << p->getRight()->getKey();
        else
            cout << "\n There is no right child of the node.  ";
        if (p->getLeft() != NULL)
            cout << "\n Left Child: " << p->getLeft()->getKey();
        else
            cout << "\n There is no left child of the node.  ";
        cout << endl; */
        if (p->getLeft())
        {
            cout << "\n\nLeft:\n";
            display(p->getLeft());
        }
        if (p->getRight())
        {
            cout << "\n\nRight:\n";
            display(p->getRight());
        }
    }
}

// compara 'a' e 'b'
// return -1 se a < b
// return 0 se a = b
// return 1 se a > b

int HashRBTree::cmp(int a, int b)
{
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    if (a > b)
        return 1;

    return 0;
}

// restituisce 1 se ok
// restituire 0 se non ha trovato
// rimuove il nodo <jey, val> dall'albero, poi
// aggiorna l'albero per mantenere le sue proprietà, se necessario.
// this->size diminuirà di 1
bool HashRBTree::remove(Node *nodo) // O(log N)
{
    // trova il nodo da cancellare

    Node *curr = root;

    while (curr->getLeft() != NULL | curr->getRight() != NULL)
    {
        // Se trovo nella il valore cercato procedo con
        // la verifica fuori dal while!
        if (nodo->getId() == curr->getId() && nodo->getKey() == curr->getKey() && nodo->getVal() == curr->getVal())
        {
            break;
        }
        // Verifo se l'id è presente nella struttura
        // confronto anche <key, val> in modo da prendere
        // lo specifico caso in cui è presente solo l'id
        // ma non la <key, val>. Così da andare a cercare
        //  e eliminare nella lista quel determinato valore.
        if (nodo->getId() == curr->getId() && nodo->getKey() != curr->getKey() && nodo->getVal() != curr->getVal())
        {
            curr->deleteNode(nodo);
        }

        if (cmp(nodo->getId(), curr->getId()) >= 0)
            curr = curr->getRight();
        else
            curr = curr->getLeft();
    }
    if (curr->getId() != nodo->getId())
    {
        return 0;
    }

    // Verifico che un determinato nodo ha una lista,
    // se il nodo ha la lista, alloco un nodo temporaneo
    // tmp e procedo a settare il nodo con i valori del nodo
    // che si trova in testa alla lista.
    // Poi dealloco la memoria del nodo e faccio puntare
    // la testa della lista al prossimo elemento della lista
    if (curr->getHead() != nullptr)
    {
        cout << "Selected node has a list! " << endl;

        Node *tmp = curr->getHead();

        curr->setKey(tmp->getKey());
        curr->setVal(tmp->getVal());
        curr->setId(nodo->getId());
        // dealloco il nodo temporaneo
        delete tmp;
        // punto al prossimo alemento della lista
        curr->setHead(curr->getNext());
    }
    else
    {
        // se il nodo non ha una lista procedo a richiamare la
        // FIX-UP
        this->removeNode(curr);
        (this->size)--;
    }

    return 1;
}

// FASE 2
// RemoveNode stabilisce se devono essere ripristinate le proprietà degli alberi Rosso-Neri ed
// eventualmente viene richiamata una funzione DELETE-FIXUP che ha proprio tale scop

void HashRBTree::removeNode(Node *node) // O(log N)
{

    if (node->getColor() == RED)
    {
        if (node->getLeft() != nullptr && node->getRight() != nullptr)
        {
            // figlio x 2
            // trova il successore, poi riempie 'node' con il successore
            Node *successor = node->getRight();
            while (successor->getLeft() != nullptr)
                successor = successor->getLeft();
            node->setId(successor->getId());
            node->setKey(successor->getKey());
            node->setVal(successor->getVal());

            this->removeNode(successor);
        }
        else if (node->getLeft() != nullptr)
        {
            // figlio sinistro
            // riempire il 'nodo' con il figlio sinistro
            node->setId(node->getLeft()->getId());
            node->setKey(node->getLeft()->getKey());
            node->setVal(node->getLeft()->getVal());
            node->setColor(node->getLeft()->getColor());
            this->removeNode(node->getLeft());
        }
        else if (node->getRight() != nullptr)
        {
            // figlio destro
            // riempire il 'nodo' con il figlio destro
            node->setId(node->getRight()->getId());
            node->setKey(node->getRight()->getKey());
            node->setVal(node->getRight()->getVal());
            node->setColor(node->getRight()->getColor());
            this->removeNode(node->getRight());
        }
        else
        {
            // se non ha figli
            if (node->getParent() == nullptr)
            {
                delete node;
                root = nullptr;
                return;
            }

            if (node->getParent()->getLeft() == node)
                node->getParent()->setLeft(nullptr);
            else
                node->getParent()->setRight(nullptr);

            delete node;
        }
    }
    else
    {
        // Viene richiamata quando il nodo da cancellare è NERO
        // questo perché se il nodo da eliminare fosse rosso non cambierebbero
        // le altezze nere (proprietà 5), non si creerebbero nodi rossi
        // consecutivi (proprietà 4) e la radice resterebbe nera (proprietà 2).
        if (node->getLeft() != nullptr && node->getRight() != nullptr)
        {
            // figlio x 2
            // trova il successore, poi riempie 'node' con il successore
            Node *successor = node->getRight();
            while (successor->getLeft() != nullptr)
                successor = successor->getLeft();
            node->setId(successor->getId());
            node->setKey(successor->getKey());
            node->setVal(successor->getVal());
            this->removeNode(successor);
        }
        else if (node->getLeft() != nullptr)
        {
            // figlio sinistro
            // riempie il 'nodo' con il figlio sinistro
            node->setId(node->getLeft()->getId());
            node->setKey(node->getLeft()->getKey());
            node->setVal(node->getLeft()->getVal());
            this->removeNode(node->getLeft());
        }
        else if (node->getRight() != nullptr)
        {
            // figlio destro
            // riempie il 'nodo' con il figlio destro
            node->setId(node->getRight()->getId());
            node->setKey(node->getRight()->getKey());
            node->setVal(node->getRight()->getVal());
            this->removeNode(node->getRight());
        }
        else
        {
            // nessun figlio.
            // Dato che il nodo NERO cancellato è una foglia,
            // bisogna fare la FIX-UP dopo la cancellazione.
            if (node->getParent() == nullptr)
            {
                // Il 'nodo' è la radice
                delete node;
                root = nullptr;
                return;
            }

            if (node->getParent()->getLeft() == node)
            {
                node->getParent()->setLeft(nullptr);
                if (node->getParent()->getRight() != nullptr && node->getParent()->getRight()->getColor() == RED)
                {
                    node->getParent()->getRight()->setColor(BLACK);
                    leftRotate(node->getParent());
                }
            }
            else
            {
                node->getParent()->setRight(nullptr);
                if (node->getParent()->getLeft() != nullptr && node->getParent()->getLeft()->getColor() == RED)
                {
                    node->getParent()->getLeft()->setColor(BLACK);
                    rightRotate(node->getParent());
                }
            }

            if (node->getParent()->getLeft() == nullptr && node->getParent()->getRight() == nullptr && node->getParent()->getParent() != nullptr)
            {
                // 'node->parent->parent' deve essere ROSSO
                rightRotate(node->getParent()->getParent());
            }

            delete node;
        }
    }
}

// return 0 se non trova
// trova il nodo con 'id' in questo albero
Node *HashRBTree::TreeSearch(Node *nodo) // O(log N)
{
    Node *temp = root;
    if (temp == nullptr)
    {
        return nullptr;
    }

    while (temp)
    {
        if (nodo->getId() == temp->getId())
        {
            return temp;
        }
        else if (nodo->getId() < temp->getId())
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }
    return nullptr;
}

// return 0 se non trova
// trova il nodo con <id, key, val> in questo albero
Node *HashRBTree::TreeSearchKey(Node *nodo)
{
    Node *temp = root;

    if (temp == nullptr)
    {
        return nullptr;
    }

    while (temp)
    {
        if (temp->getId() == nodo->getId() && temp->getKey() == nodo->getKey() && temp->getVal() == nodo->getVal())
        {

            return temp;
        }
        else if (nodo->getId() < temp->getId())
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }

    return nullptr;
}

#endif // HASHRBTREE_H