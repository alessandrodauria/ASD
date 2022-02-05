# ASD
## Progetto di algoritmi e strutture dati
> Traccia 1

Seguendo i principi di progettazione object oriented, progettare ed implementare in C++, in maniera ORIGINALE, tutti gli algoritmi e le strutture dati necessari per risolvere i seguenti punti:

# HashRBTree

Si vuole realizzare la struttura dati **HashRBTree** che consenta di memorizzare coppie **<key,value>** all’interno di un albero Red Black.
1. A partire dalla chiave **key**, utilizzando una funzione di hash, si ricava un **id** che verrà utilizzato per indentificare un nodo dell’albero al cui interno viene memorizzato il dato value.
2. 2.Per inserire un nuovo valore nel **HashRBTree**, si applica la **funzione di hash** alla key e si inserisce un nuovo nodo utilizzando l’id restituito.
3. Nel caso di **collisione**, ovvero nel caso in cui all’interno dell’albero esista già un nodo con lo stesso id, il nuovo nodo viene **inserito in una lista associata** al nodo che ha generato la collisione.

Progettare ed implementare una struttura dati che, **dato un file di coppie chiave valore separate da virgola**, costruisca HashRBTree corrispondente e consenta di effettuare le seguenti operazioni:

```
1. **SEARCH**(< key,value >),
2. **INSERT**(< key,value >), 
3. **DELETE**(< key,value >).
```

Dotare il programma di un menu da cui sia possibile richiamare le suddette operazioni.


```cpp
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
```
