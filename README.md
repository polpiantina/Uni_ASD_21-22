## Esercizio 1

### Linguaggio richiesto: C

### Testo

Implementare una libreria che offre due algortmi di ordinamento, Quick Sort e Binary Insertion Sort. Scrivere una relazione che tratta la scelta del pivot per l'algoritmo Quick Sort ed i tempi di risposta. Il codice deve essere generico. Gli algoritmi devono ordinare le tuple prese per intero, non soltanto i singoli campi.

Il file `records.csv` utilizzato contiene 20 milioni di righe da ordinare.
Ogni riga contiene:

- id: (tipo intero) identificatore della tupla;
- field1: (tipo stringa) contiene parole senza spazi e caratteri speciali;
- field2: (tipo intero);
- field3: (tipo floating point);

Il formato è un CSV standard: i campi sono separati da virgole; i record sono separati da `\n`.

## Esercizio 2 - Skip List

### Linguaggio richiesto: C

### Testo

Realizzare una libreria che fornisce una SkipList, usando lo pseudocodice fornito. 

Vengono inoltre forniti due file: un dizionario, contenente un elenco di parole, ed un testo da correggere, contenente un testo. Il main deve stampare a schermo la lista di parole del testo che non sono presenti nel dizionario. Scrivere una relazione che studi i tempi di risposta della SkipList variando il valore di ``MAX_HEIGHT``. Le parole che dovrebbero comparire come output sono:

```
cinqve
perpeteva
squola
domandrono
vuolessi
corpito
wita
```

## Esercizio 3

### Linguaggio richiesto: Java

### Testo

Implementare una libreria che realizza una Priority Queue, strutturata come uno Heap Minimo. L'implementazione deve essere generica per quanto riguarda il tipo dei dati contenuti all'interno della Priority Queue. Sono specificate delle limitazioni sulla complessità temporale di ogni metodo.

## Esercizio 4

### Linguaggio richiesto: Java

### Testo

Implementare una libreria che realizza la struttura dati Grafo ottimale per dati sparsi. L'implementazione deve essere generica per quanto riguarda il tipo dei nodi ed il tipo delle etichette degli archi e deve consentire di gestire grafi diretti e non diretti. Sono specificate delle limitazioni sulla complessità temporale di ogni metodo.

In seguito, implementare una libreria che realizza l'algoritmo di Dijkstra per determinare i cammini minimi da sorgente unica in un grafo orientato pesato, con pesi tutti non negativi. L'algoritmo dovrà usare le classi grafo e priority queue implementate precedentemente. Viene fornito un file contenente tutte le informazioni necessarie, formattato come segue:

- località 1: (tipo stringa) nome della località "sorgente". La stringa può contenere spazi, non può contenere virgole;
- località 2: (tipo stringa) nome della località "destinazione". La stringa  può contenere spazi, non può contenere virgole;
- distanza: (tipo float) distanza in metri tra le due località.

