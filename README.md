# ASD
##Progetto di algoritmi e strutture dati

Seguendo i principi di progettazione object oriented, progettare ed implementare in C++, in maniera ORIGINALE, tutti gli algoritmi e le strutture dati necessari per risolvere i seguenti punti:

#HashRBTree
Si vuole realizzare la struttura dati HashRBTree che consenta di memorizzare coppie <key,value> all’interno di un albero Red Black.
1. A partire dalla chiave key, utilizzando una funzione di hash, si ricava un id che verrà utilizzato per indentificare un nodo dell’albero al cui interno viene memorizzato il dato value.
2. 2.Per inserire un nuovo valore nel HashRBTree, si applica la funzione di hash alla key e si inserisce un nuovo nodo utilizzando l’id restituito.
3. Nel caso di collisione, ovvero nel caso in cui all’interno dell’albero esista già un nodo con lo stesso id, il nuovo nodo viene inserito in una lista associata al nodo che ha generato la collisione.

Progettare ed implementare una struttura dati che, dato un file di coppie chiave valore separate da virgola, costruisca HashRBTree corrispondente e consenta di effettuare le seguenti operazioni:
1. SEARCH(<key,value>),
2. INSERT(<key,value>), 
3. DELETE(<key,value>).

Dotare il programma di un menu da cui sia possibile richiamare le suddette operazioni.
