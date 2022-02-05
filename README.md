# ASD
## Progetto di algoritmi e strutture dati
> Traccia 1

Seguendo i principi di progettazione object oriented, progettare ed implementare in C++, in maniera ORIGINALE, tutti gli algoritmi e le strutture dati necessari per risolvere i seguenti punti:

# HashRBTree :deciduous_tree:

Si vuole realizzare la struttura dati **HashRBTree** che consenta di memorizzare coppie **<key,value>** all’interno di un albero Red Black.
1. A partire dalla chiave **key**, utilizzando una funzione di hash, si ricava un **id** che verrà utilizzato per indentificare un nodo dell’albero al cui interno viene memorizzato il dato value.
2. Per inserire un nuovo valore nel **HashRBTree**, si applica la **funzione di hash** alla key e si inserisce un nuovo nodo utilizzando l’id restituito.
3. Nel caso di **collisione**, ovvero nel caso in cui all’interno dell’albero esista già un nodo con lo stesso id, il nuovo nodo viene **inserito in una lista associata** al nodo che ha generato la collisione.

Progettare ed implementare una struttura dati che, **dato un file di coppie chiave valore separate da virgola**, costruisca HashRBTree corrispondente e consenta di effettuare le seguenti operazioni:

```
1. SEARCH (< key,value >),
2. INSERT (< key,value >), 
3. DELETE (< key,value >).
```

Dotare il programma di un menu da cui sia possibile richiamare le suddette operazioni.











> Traccia 2

# Servizio Mobilità :running_man:

Il primo ministro dello stato di Grapha-Nui vuole incentivare l’utilizzo del servizio pubblico di mobilità. A tal fine promuove un **abbonamento mensile** da usare su un** unico percorso** dalla città capitale fino ad una qualunque città dello stato, con la possibilità di ottenere uno sconto pari al costo della tratta più onerosa del percorso scelto. Si vuole progettare un algoritmo che, data una città dello stato ed una piantina con tutte le tratte ed i relativi costi, aiuti i cittadini a scegliere il percorso più economico considerando lo sconto pari alla tratta più costosa.

## Dati di input:

```
È assegnato un file di testo contenente nel primo rigo due interi separati da uno spazio: 
il numero N delle città (numerate da 1 ad N, 0 rappresenta la capitale), il numero P delle tratte.
I successivi P righi contengono ciascuno tre numeri S, E, C, per indicare la città di partenza,
quella di arrivo e il costo.
```

## Dati di output:

```
Determinare il percorso più economico dalla città 0 alla città N, indicando quali attraversare 
e quale è il costo finale (dopo aver detratto lo sconto).
```
## Assunzioni:


```
• 2≤N≤1000
• 1≤P≤10000
• 0≤ Si ≤ N         Per ogni i=1...P
• 0≤ Ei ≤ N         Per ogni i=1...P
• 1 ≤ Ci ≤ 10000    Per ogni i=1...P
```

## Esempio:


