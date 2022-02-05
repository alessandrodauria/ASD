#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

enum Color
{
    BLACK,
    RED
};

class Node
{
private:
    int key;
    int id;
    string val;
    Node *parent, *left, *right;
    Color color;
    Node *next;
    Node *head;

public:
    Node() : parent(nullptr), left(nullptr), right(nullptr), head(NULL), color(RED){};
    ~Node()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

    int getKey() { return key; }
    void setKey(int keyy) { key = keyy; }
    int getId() { return id; }
    void setId(int ident) { id = ident; }
    void setVal(string v) { val = v; }
    string getVal() { return val; }
    void setParent(Node *p) { parent = p; }
    Node *getParent() { return parent; }
    void setLeft(Node *l) { left = l; }
    Node *getLeft() { return left; }
    void setRight(Node *r) { right = r; }
    Node *getRight() { return right; }
    void setColor(Color c) { color = c; }
    Color getColor() { return color; }
    void setNext(Node *n) { next = n; }
    Node *getNext() { return next; }
    Node *getHead() { return head; }
    void setHead(Node *n) { head = n; }
    bool search(Node *nodo); // O(n)
    // Function che inserisce
    // il nodo alla fine della
    // linked list.
    void insertNode(int, string); // O(1)

    // Function che stampa la
    // linked list.
    void printList(); // O(n)

    // Function che elimina il
    // nodo in una det. posizione.
    void deleteNode(Node *nodo); // O(n)
};

// Function che cerca <Key, Value> nella lista
// ritorna true se trova la corrispondenza e
// false se non la trova.
bool Node::search(Node *nodo) // O(N)
{
    Node *current = head;
    while (current != NULL)
    {
        // Verifica se è presente <Key, Value>
        if (current->getKey() == nodo->getKey() && current->getVal() == nodo->getVal())
        {
            cout << "\n\tCOLLISION DETECTED!" << endl;
            cout << endl
                 << "\tFOUND in list with ID: " << nodo->getId() << endl;
            return true;
        }

        // aggiorna il puntatore al successivo.
        current = current->getNext();
    }
    cout << "\n\tNOT FOUND!" << endl;
    return false;
}

void Node::deleteNode(Node *nodo) // O(N)
{
    Node *temp = head;
    Node *prev;

    // Verifico se mi trovo nel caso base e <Key, Value>
    // si trovano in testa alla lista e elimino, aggiornando
    // il puntatore al successivo.
    if (head->getKey() == nodo->getKey() && head->getVal() == nodo->getVal())
    {
        delete head;
        head = head->getNext();
        return;
    }

    // Verifico
    if (head->getNext() == NULL)
    {
        if (head->getKey() == nodo->getKey() && head->getVal() == nodo->getVal())
        {
            delete head;
            head = NULL;
            return;
        }
        cout << "... VALUE NOT FOUND ...";
        return;
    }

    // Scorro tutta la lista finche non trovo il <Key,Value>
    // corrispondente alla coppia cercata, se lo trovo elimino
    // e aggiorno il puntatore al successivo.
    while (temp->next != NULL)
    {
        if (temp->getNext()->getKey() == nodo->getKey() && temp->getNext()->getVal() == nodo->getVal())
        {
            Node *temp_ptr = temp->getNext()->getNext();
            delete temp->getNext();
            temp->setNext(temp_ptr);
            return;
        }
        temp = temp->getNext();
    }

    cout << "... VALUE NOT EXIST ... !!" << endl
         << endl;
}

// Function che inserisce un nuovo nodo nella lista
void Node::insertNode(int key, string val) // O(1)
{
    // Creo un nuovo nodo
    Node *newNode = new Node;
    newNode->key = key;
    newNode->val = val;
    // Lo assegno alla testa
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    // Attraversa fino alla fine della lista
    Node *temp = head;
    while (temp->next != NULL)
    {
        // Aggiorno temp
        temp = temp->next;
    }

    // Inserisco alla fine.
    temp->next = newNode;
}

// Function che stampa la
// linked list.
void Node::printList()
{
    Node *temp = head;
    int posizion = 0;

    // Verifico se la lista è vuota
    if (head == NULL)
    {
        cout << "List empty" << endl;
        return;
    }

    // Attraverso la lista
    while (temp != NULL)
    {
        posizion++;
        cout << "in position ";
        cout << posizion << endl;
        cout << temp->key << " ";
        cout << temp->val << " " << endl;
        temp = temp->next;
    }
}

#endif // NODE_H