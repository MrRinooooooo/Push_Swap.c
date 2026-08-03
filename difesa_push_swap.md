# push_swap — Guida completa alla difesa

Spiegazione di ogni funzione (mandatory + bonus), punti deboli noti, domande tipiche ed esercizi di live coding.

---

## Indice

1. Il progetto in breve: regole e obiettivo
2. Architettura generale e pipeline del `main`
3. Strutture dati: `t_list`, `t_vars`, `t_count`
4. Parsing e validazione dell'input
5. Operazioni sullo stack (sa/sb/ss/pa/pb/ra/rb/rr/rra/rrb/rrr)
6. Strategia Simple — O(n²)
7. Strategia Medium — O(n·√n)
8. Strategia Complex — O(n log n)
9. Strategia Adaptive e selezione automatica
10. Bench, printf_stderr e debugger
11. Bonus: il checker e get_next_line
12. Bug noti e punti deboli — da sistemare prima della difesa
13. Domande tipiche da correttore e risposte pronte
14. Esercizi di live coding (soluzioni in fondo, sezione separata)


---

## 1. Il progetto in breve

**push_swap** prende in input una lista di interi (unici, senza duplicati) come argomenti da riga di comando e deve stampare su stdout la sequenza minima (o comunque efficiente) di istruzioni che ordina la pila `stack_a` in ordine crescente, usando una seconda pila di appoggio `stack_b` inizialmente vuota.

Le uniche 11 operazioni permesse sono:

| Op | Effetto |
|----|---------|
| `sa` | swap dei primi 2 elementi di stack_a |
| `sb` | swap dei primi 2 elementi di stack_b |
| `ss` | sa + sb contemporaneamente |
| `pa` | push dalla cima di stack_b alla cima di stack_a |
| `pb` | push dalla cima di stack_a alla cima di stack_b |
| `ra` | rotate stack_a: il primo elemento diventa l'ultimo |
| `rb` | rotate stack_b |
| `rr` | ra + rb contemporaneamente |
| `rra` | reverse rotate stack_a: l'ultimo elemento diventa il primo |
| `rrb` | reverse rotate stack_b |
| `rrr` | rra + rrb contemporaneamente |

In questo progetto, oltre al comportamento standard 42, il programma supporta dei **flag** opzionali (`--bench`, `--simple`, `--medium`, `--complex`, `--adaptive`) che permettono di forzare una strategia di ordinamento specifica o di stampare statistiche. Senza nessun flag di strategia, il programma è in modalità **adaptive** di default (vedi `alg_selector` in `alg_adaptive.c`).

---

## 2. Architettura generale — pipeline del main

**`int main(int argc, char *argv[])` — main.c**

```c
flags_set_zero(flags);
flags_parser(flags, argc, argv);
int_arr = int_arr_parser(argc, argv, flags_num(flags));
size = argc - flags_num(flags) - 1;
stack_a = list_arg_parser(int_arr, size);
alg_selector(flags, int_arr, &stack_a, &stack_b, size);
```

Sei passi, in ordine:

1. **Azzeramento flag** — `flags_set_zero` mette a 0 l'array statico di 6 flag prima del parsing (evita valori indefiniti).
2. **Parsing dei flag** — `flags_parser` guarda solo `argv[1]` e `argv[2]` (i primi due argomenti) e attiva i flag corrispondenti a stringhe che iniziano con `--`.
3. **Conteggio flag** — `flags_num` somma i flag attivi; serve per sapere da quale indice di `argv` iniziano i numeri veri e propri.
4. **Parsing dei numeri** — `int_arr_parser` converte gli argomenti restanti in un array di `int` con `atoi_safe` (gestisce overflow ed errori di formato).
5. **Costruzione della pila** — `list_arg_parser` calcola il *rank* di ogni valore (posizione che avrebbe in ordine crescente) e costruisce `stack_a` come lista concatenata, in testa (quindi l'ultimo argomento letto finisce in cima alla pila — comportamento standard push_swap).
6. **Selezione strategia ed esecuzione** — `alg_selector` calcola il disordine dell'array, sceglie/applica una strategia (simple/medium/complex/adaptive), stampa il bench se richiesto.

> **Perché il rank e non il valore diretto?** I valori in input possono essere numeri qualsiasi (anche molto distanti tra loro, es. `-2000000000 5`). Gli algoritmi medium e complex ragionano per intervalli/pivot su indici *densi* 0..size-1: usare il rank invece del valore rende triviale calcolare pivot, chunk e range senza dover gestire buchi nei valori.

---

## 3. Strutture dati

**`t_list` — push_swap.h**

```c
typedef struct s_list
{
    int             value;   // il valore intero originale
    int             rank;    // posizione 0..size-1 nell'ordine crescente
    struct s_list   *next;
}                   t_list;
```

Lista concatenata singola. Sia `stack_a` che `stack_b` sono puntatori `t_list*`: la "cima" della pila è sempre la **testa** della lista.

**`t_vars` — push_swap.h (usata solo da alg_medium)**

```c
typedef struct s_alg_vars
{
    int chunk_size;     // ampiezza di ogni "fetta" di rank considerata
    int chunk_min;      // rank minimo della fetta corrente
    int chunk_max;      // rank massimo della fetta corrente
    int chunk_to_push;  // quanti elementi di questa fetta mancano da spostare in B
    int a_size;         // elementi rimasti in stack_a
    int b_size;         // elementi finora spostati in stack_b
}                   t_vars;
```

Tiene lo stato dell'algoritmo a "fette" (chunk): invece di cercare il minimo assoluto su tutta la pila A come fa il simple sort, cerca il minimo *dentro l'intervallo di rank corrente*, riducendo il numero di rotazioni necessarie.

**`t_count` — push_swap.h**

```c
typedef struct s_counters
{
    int sa, sb, ss, pa, pb;
    int ra, rb, rr, rra, rrb, rrr;
}                   t_count;
```

Un contatore per ciascuna delle 11 operazioni, incrementato dentro le funzioni operazione stesse. Usato esclusivamente per `--bench` (statistiche in stderr, vedi cap. 10). Non influenza la logica di ordinamento.

---

## 4. Parsing e validazione dell'input

### flags.c

**`void flags_set_zero(int flags[])`**
Azzera i 6 slot dell'array flag. Necessario perché l'array è dichiarato `static int flags[5]` in `main` — da notare: la dichiarazione usa dimensione 5 ma `flags_num` e `flags_set_zero` indicizzano fino a 5 incluso (6 elementi, indici 0..5): funziona solo perché le variabili `static` sono comunque azzerate a compile-time e l'array è di fatto sovradimensionato dal compilatore in questo caso solo per un elemento in meno di quanto viene effettivamente acceduto — **è un off-by-one latente** da conoscere se un correttore chiede "quanto è grande l'array flags?" (risposta onesta: dichiarato per 5, ma il codice lo tratta come se ne avesse 6; su questo compilatore/OS non causa crash osservabile, ma è undefined behaviour in senso stretto).

**`void set_flags(int flags[], int i)`**
Incrementa `flags[i]` di 1 (non lo mette a 1 direttamente): questo è voluto, perché permette a `flags_num` di rilevare un flag ripetuto due volte come errore (valore diventa 2, che non è né 0 né 1 → `print_error()`).

**`void flags_parser(int flags[], int argc, char *argv[])`**
Guarda solo `argv[0]`, `argv[1]`, `argv[2]` (condizione `i <= 2`): il programma accetta al massimo 2 flag contemporaneamente (es. `--bench --adaptive`), e devono stare nei primi due argomenti dopo il nome programma. Se una stringa inizia per `--` ma non combacia con nessun flag noto, chiama `print_error()`.

**`int flags_num(int flags[])`**
Scorre tutti e 6 gli slot, verifica che ognuno sia 0 o 1 (altrimenti errore — vedi `set_flags` sopra), e ritorna quanti sono stati attivati. Il valore di ritorno è usato per calcolare da quale indice di `argv` iniziano i numeri.

### strings_utils.c

**`int ps_strlen(char *s1)` / `int ps_strcmp(const char *s1, const char *s2)`**
Reimplementazioni minime di `strlen`/`strcmp` (la libc standard non è consentita al 42 fuori da libft). `ps_strcmp` ritorna la differenza tra i primi caratteri diversi, come lo strcmp standard.

**`int atoi_safe(const char *str)`**
Come `atoi` ma con due controlli aggiuntivi fondamentali:

- Se il primo carattere (dopo un eventuale `-`) non è una cifra → `print_error()` (rifiuta stringhe non numeriche tipo `"abc"`).
- Overflow-check *prima* di moltiplicare: confronta `result` con `(INT_MAX - digit) / 10` (caso positivo) o l'equivalente per `INT_MIN` usando aritmetica `unsigned int` (caso negativo, che ha un valore assoluto in più rispetto a INT_MAX). Questo evita l'undefined behaviour della classica implementazione ingenua che fa overflow su `int` con input come `99999999999`.
- Se dopo le cifre resta un carattere non nullo (es. `"42abc"`) → errore: l'intera stringa deve essere un numero valido, non solo il prefisso.

### parser.c

**`int *int_arr_parser(int argc, char *argv[], int flags_n)`**
Alloca un array di `argc - flags_n - 1` interi e lo riempie chiamando `atoi_safe` su ogni argomento a partire da `argv[flags_n + 1]` (salta il nome del programma e i flag).

**`void assign_rank(int *arr, int *rank_arr, int size)`**
Per ogni elemento `arr[i]`, conta quanti elementi dell'array sono più piccoli di lui: quel conteggio è il suo rank. Complessità O(n²), ma `size` in questo progetto è l'input dell'utente da riga di comando, quindi accettabile (non è la parte critica misurata per il numero di operazioni).

**`t_list *list_arg_parser(int arr[], int size)`**
Costruisce la lista partendo **dall'ultimo indice verso il primo** (`while (size--) ... ps_lstadd_front`): dato che ogni nodo è inserito in testa, il risultato finale ha `arr[0]` in cima alla pila — cioè il *primo* argomento passato da riga di comando è in cima a stack_a, come richiesto dalle specifiche 42.

**`void free_stack(t_list **stack)`**
Libera tutti i nodi della lista uno a uno salvando `next` prima di fare `free` del nodo corrente (pattern classico per evitare use-after-free).

### disorder.c

**`float compute_disorder(int array[], int arraylen)`**
Conta il numero di **coppie invertite** (inversioni: `i < j` ma `array[i] > array[j]`) su tutte le `n(n-1)/2` coppie possibili, e ritorna il rapporto `mistakes / total_pairs` come percentuale di disordine tra 0.0 (già ordinato) e 1.0 (ordinato al contrario). **Effetto collaterale importante**: se trova due valori uguali (`array[i] == array[j]`) chiama `print_error()` — questo è anche il punto in cui viene rispettata la regola "nessun duplicato" del progetto, quindi questa funzione viene sempre chiamata anche quando la strategia è forzata da flag, non solo in modalità adaptive.

---

## 5. Operazioni sullo stack

Tutte le operazioni condividono la stessa firma: prendono i puntatori alle pile coinvolte, un `t_count *count` da incrementare, e un flag `print` che decide se stampare (`write`) il nome dell'operazione su stdout. Il flag `print` viene messo a 0 quando l'operazione è chiamata come sotto-passo di un'operazione combinata (es. `sa` dentro `ss`), per evitare di stampare due volte.

### operations_push_swap.c

**`void sa(t_list **lst, t_count *count, int print)`**
Scambia i primi due nodi **senza spostare i dati**, ma ricollegando i puntatori `next`: prende il secondo nodo, lo mette in testa con `ps_lstadd_front`, e il vecchio primo nodo (`temp->next` già scollegato) resta come secondo. Non fa nulla se la pila ha 0 o 1 elementi (guard clause).

**`void sb(t_list **lst, t_count *count, int print)`**
Stessa logica di `sa` ma applicata a stack_b, scritta senza riutilizzare `ps_lstadd_front` (scambio manuale dei due puntatori).

**`void ss(t_list **a, t_list **b, t_count *count, int print)`**
Chiama `sa` e `sb` con `print=0`, poi decrementa manualmente i contatori `sa`/`sb` incrementati dalle due chiamate e incrementa `ss` — così il bench conta correttamente 1 operazione `ss` invece di 1 sa + 1 sb.

**`void pa(t_list **stack_a, t_list **stack_b, t_count *count, int print)` / `pb(...)`**
Staccano la testa della pila sorgente e la reinseriscono in testa alla pila destinazione con `ps_lstadd_front`. Non fanno nulla se la pila sorgente è vuota.

### operations_rotate.c

**`void ra(t_list **stack_a, t_count *count, int print)` / `rb(...)`**
Il primo elemento diventa l'ultimo: salva la testa, scorre fino all'ultimo nodo con un ciclo `while (node->next)`, ci attacca in coda il vecchio primo nodo (con `next = NULL`), e aggiorna la testa della pila al vecchio secondo elemento. Complessità O(n) per singola rotazione perché serve raggiungere la coda — punto spesso chiesto in difesa: **la lista è singolarmente concatenata, non c'è puntatore alla coda né lista doppia**, quindi ogni `ra`/`rra` è O(n).

**`void rr(t_list **stack_a, t_list **stack_b, t_count *count, int print)`**
Chiama `ra` e `rb` con `print=0` e corregge i contatori, stesso pattern di `ss`.

### operations_reverse_rotate.c

**`void rra(t_list **stack_a, t_count *count, int print)` / `rrb(...)`**
L'ultimo elemento diventa il primo: scorre la lista tenendo traccia sia dell'ultimo nodo (`last_a`) sia del penultimo (`com` — il nodo prima dell'ultimo), stacca l'ultimo nodo settando `com->next = NULL`, e lo reinserisce in testa.

> **Bug reale in operations_reverse_rotate.c, riga 39** (in `rrb`):
> ```c
> if (print == 1)count->rrb++;
>     write(1, "rrb\n", 4);
> ```
> Manca la graffa: così com'è, l'istruzione dopo l'`if` è solo `count->rrb++;` (eseguita solo se `print==1`, **oltre** all'incremento già fatto due righe sopra — quindi il conteggio di rrb raddoppia quando `print==1`), mentre la `write` è **fuori** dall'if e viene eseguita *sempre*, anche quando `print==0` (cioè quando `rrb` è chiamata da `rrr`, che si aspetta silenzio). Risultato pratico: ogni volta che `rrr` viene usata, stampa comunque `"rrb"` in più su stdout, corrompendo l'output del mandatory. **Da correggere prima della difesa** aggiungendo le graffe:
> ```c
> if (print == 1)
> {
>     count->rrb++;
>     write(1, "rrb\n", 4);
> }
> ```

**`void rrr(t_list **stack_a, t_list **stack_b, t_count *count, int print)`**
Chiama `rra` e `rrb` con `print=0`. Nota: a causa del bug sopra, anche passando `print=0` la `write` dentro `rrb` scatta comunque.

---

## 6. Strategia Simple — O(n²)

`alg_simple.c` — usata quando il disordine è basso (`< 0.2` in modalità adaptive) o forzata con `--simple`. Adatta a pile piccole/quasi ordinate.

**`void simple_sort(t_list **a, t_list **b, t_count *count)`**
Algoritmo di tipo "selection sort" tramite le due pile:

1. Finché stack_a non è vuota: trova il minimo, portalo in cima con il minor numero di rotazioni (`move_to_top`), spostalo in stack_b con `pb`. Alla fine di questo ciclo, stack_b contiene tutti gli elementi in ordine **crescente dalla cima verso il fondo** (il minimo assoluto è in cima).
2. Poi svuota stack_b in stack_a con `pa` ripetuto: siccome l'ultimo elemento pushato in B era il massimo (finiva in fondo a B), e pa preleva dalla cima di B, il risultato finale su A è ordinato crescente dalla cima.

**`void move_to_top(t_list **a, t_count *count)`**
Trova l'indice del minimo con `find_min_index`, poi decide la direzione di rotazione più economica confrontando la distanza in avanti (`ra` ripetuti `min_pos` volte) contro la distanza all'indietro (`rra` ripetuti `size - min_pos` volte), scegliendo sempre la metà più corta. Questo è il primo, più semplice esempio nel progetto di "rotazione ottimale" — utile da spiegare bene perché la stessa idea (min tra le due direzioni) ritorna identica in `move_to_top_chunk` e `move_to_top_b` nel medium sort.

**`int find_min_index(t_list *stack)` / `int stack_size(t_list *stack)`**
Scansioni lineari classiche su lista concatenata. `find_min_index` ritorna la posizione (non il valore) del minimo, partendo da 0 per la testa.

---

## 7. Strategia Medium — O(n·√n)

`alg_medium.c` + `alg_medium_utils.c` — usata per disordine intermedio (0.2 – 0.5) o con `--medium`. Idea centrale: dividere l'intervallo di rank `[0, size-1]` in "fette" (chunk) di ampiezza ≈ √size, e processare le fette una alla volta invece di cercare il minimo assoluto ogni volta (che sarebbe O(n²) come il simple sort).

**`int calculate_chunk(int size)` — alg_medium.c**
Cerca il più piccolo `i` tale che `i² > size`, poi ritorna `i - 1`: in pratica restituisce il quadrato perfetto più vicino a `√size` per arrotondamento verso il basso. Questo fissa l'ampiezza iniziale dei chunk, da cui deriva il fattore `√n` nella complessità O(n√n): n chunk-scan, ciascuno su una fetta di ampiezza √n.

**`void init_vars(t_vars *vars, int size)` — alg_medium.c**
Inizializza il primo chunk: `[0, chunk_size - 1]`, `chunk_to_push = chunk_size` (quanti elementi di questa fetta vanno ancora spostati), `a_size = size`, `b_size = 0`.

**`void medium_sort(t_list **stack_a, t_list **stack_b, int size, t_count *count)`**

```c
while (*stack_a != NULL)
{
    move_to_top_chunk(stack_a, &vars, count);
    pb(stack_b, stack_a, count, 1);
    update_vars(&vars, size);
}
while (vars.b_size > 0)
{
    move_to_top_b(stack_b, &vars, count);
    pa(stack_a, stack_b, count, 1);
    vars.a_size++;
    vars.b_size--;
}
```

**Fase 1 (svuota A in B):** ripetutamente trova, dentro il rank-range del chunk corrente, l'elemento più vicino alla cima di A (`move_to_top_chunk`), lo mette in cima con rotazioni minime, e lo spinge in B. `update_vars` fa avanzare la finestra `[chunk_min, chunk_max]` quando il chunk corrente è esaurito.

**Fase 2 (svuota B in A):** a questo punto stack_b contiene gli elementi processati chunk per chunk, quindi non è ordinato in modo semplice: bisogna ritrovare ogni volta il **massimo** corrente in B (`move_to_top_b`/`find_max_index`) e spingerlo in A, cosicché A si ricostruisca in ordine crescente man mano che si svuota B (il massimo va sempre in cima ad A, quindi finisce sotto ai valori più piccoli inseriti dopo).

**`int find_min_index_chunk(t_list *stack, t_vars *vars)` — alg_medium_utils.c**
Cerca, solo tra i nodi il cui `rank` cade dentro `[chunk_min, chunk_max]`, quello più vicino alla cima (distanza minima dalla testa). Nota: la variabile si chiama `min_pos` ma qui "min" significa "posizione minima dalla cima", non "valore minimo" — la selezione del valore giusto è già garantita dal filtro sul range di rank, non da un confronto di valore.

**`void move_to_top_chunk` / `move_to_top_b`**
Stessa logica di rotazione ottimale già vista in `move_to_top` (simple sort): sceglie `ra`/`rb` o `rra`/`rrb` in base a quale distanza è più corta.

**`void update_vars(t_vars *vars, int size)` — alg_medium_utils.c**
Decrementa `chunk_to_push` a ogni elemento spostato; quando arriva a 0 (fetta esaurita) e non si è ancora raggiunta la fine dell'intervallo (`chunk_max != size - 1`), fa avanzare la finestra: se il prossimo salto supererebbe `size - 1`, la fetta finale viene "allargata" fino alla fine (`chunk_max = size - 1`) per includere il resto senza lasciare elementi orfani; altrimenti trasla la finestra di `chunk_size`.

---

## 8. Strategia Complex — O(n log n)

`alg_complex.c` — usata per disordine alto (>= 0.5) o con `--complex`. È un **quicksort** adattato a due pile: invece di un array con partizione in-place, si partiziona spostando elementi tra stack_a e stack_b intorno a un pivot, ricorsivamente.

**`void complex_sort(t_list **a, t_list **b, int size, t_count *count)`**
Punto di ingresso: se `size <= 1` non fa nulla, altrimenti chiama `sort_a(a, b, size, 0, size - 1, count)` — l'intervallo di rank iniziale è tutto `[0, size-1]` perché il rank è denso.

**`void sort_a(t_list **a, t_list **b, int size, int min, int max, t_count *count)`**
Ordina (ricorsivamente) i primi `size` elementi di stack_a, sapendo che i loro rank sono compresi in `[min, max]`:

- Caso base: se il segmento è già ordinato rispetto al range (`is_range_sorted_a`) o `size < 1`, ritorna subito.
- Caso `size == 2`: un solo eventuale `sa` basta.
- Caso generale: pivot = punto medio di `[min, max]`. Chiama `partition_a` per separare gli elementi con rank < pivot (spinti in B) da quelli con rank >= pivot (che restano in A, ruotati fuori dai piedi). Poi ricorre su entrambe le metà: la parte rimasta in A (rank in `[pivot, max]`) via `sort_a`, la parte finita in B (rank in `[min, pivot-1]`) via `sort_b`.

**`int partition_a(t_list **a, t_list **b, int size, int pivot, t_count *count)`**
Scorre i primi `size` elementi di A una volta: se il rank in cima è `< pivot`, lo spinge in B (`pb`); altrimenti lo ruota in fondo alla porzione con `ra` (così resta "fuori dai piedi" senza mescolarsi con elementi già processati). Alla fine, se sono rimasti elementi oltre il segmento (`total_stack_a > size`), annulla le rotazioni fatte con altrettanti `rra`, per rimettere la porzione ruotata nella posizione relativa corretta rispetto al resto della pila. Ritorna quanti elementi sono stati spinti in B.

**`void sort_b` / `int partition_b` — logica speculare**
`sort_b` è l'analogo di `sort_a` ma per stack_b, con una differenza concettuale: essendo B una pila "di appoggio" temporanea, quando un segmento di B è già ordinato rispetto al proprio range (`is_range_sorted_b`), invece di ritornare e basta lo svuota subito in A con `pa` ripetuti — B deve sempre tendere a svuotarsi, non resta mai popolata a lungo. `partition_b` fa lo stesso lavoro di `partition_a` ma con la condizione invertita (rank > pivot va in A) e usa `rb`/`rrb` per accantonare/ripristinare.

**`int is_range_sorted_a` / `is_range_sorted_b`**
Controllano se i primi `size` nodi sono già in ordine (crescente per A, decrescente per B — perché B accumula elementi "al contrario" rispetto all'ordine finale desiderato, dato che l'ultimo push finisce in cima). Sono un'ottimizzazione per evitare partizioni/ricorsioni inutili quando un sotto-segmento risulta già ordinato durante il processo.

> **Debug `printf` non rimossi** in `sort_a`, `sort_b`, `partition_a`, `partition_b`, `complex_sort`: scrivono su **stdout** (non stderr), quindi con `--complex` attivo (o in adaptive con disordine alto) l'output del programma non è più solo la sequenza di operazioni valide — rompe qualunque verifica automatica/checker che legga stdout riga per riga. **Da rimuovere prima della consegna/difesa.** Comando rapido per trovarli tutti: `grep -n "printf(" alg_complex.c`

---

## 9. Strategia Adaptive e selezione

**`void alg_selector(int *flags, int *int_arr, t_list **stack_a, t_list **stack_b, int size)` — alg_adaptive.c**
Punto di dispatch centrale, chiamato una sola volta da `main`:

1. Calcola `disorder = compute_disorder(int_arr, size)` (questo, come già detto, è anche dove viene rilevato un eventuale duplicato).
2. Se nessuno dei flag `--simple/--medium/--complex` è attivo, forza `flags[4] = 1` (adaptive) — quindi **adaptive è il default assoluto**.
3. Se adaptive è attivo, chiama `adaptive_sort(disorder, flags)`, che in base alla soglia di disordine attiva a sua volta uno dei tre flag simple/medium/complex e ritorna una stringa descrittiva della complessità scelta.
4. Esegue poi la strategia risultante (i tre `if`/`else if` su `flags[1]/[2]/[3]` — nota: **non sono mutuamente esclusivi a priori** nel codice, ma lo sono in pratica perché solo uno dei tre viene mai messo a 1, sia dall'utente (al massimo 2 flag totali, difficile passarne 2 di strategia validi assieme) sia da `adaptive_sort`).
5. Se `--bench` è attivo, stampa le statistiche.

**`char *adaptive_sort(float disorder, int *flags)`**

```
disorder < 0.2        -> simple   (O(n^2))
0.2 <= disorder < 0.5  -> medium   (O(n sqrt n))
disorder >= 0.5        -> complex  (O(n log n))
```

Soglie scelte empiricamente: con poco disordine il numero assoluto di elementi "fuori posto" è basso, quindi anche un algoritmo quadratico compie poche operazioni reali; con disordine alto conviene l'algoritmo con la migliore complessità asintotica anche se ha più overhead per caso.

---

## 10. Bench, printf_stderr e debugger

### bench.c

**`void print_bench(t_count count, float disorder, int *flags, char *strategy)`**
Somma tutti i contatori in `total_ops` e stampa (su **stderr**, tramite `printf_stderr`, quindi senza sporcare l'output valutabile su stdout) percentuale di disordine, strategia scelta, totale operazioni e il dettaglio per ciascuna delle 11 operazioni.

**`void print_disorder(float disorder)`**
Converte il float in percentuale con 2 decimali **senza usare `%f`** (perché `printf_stderr` supporta solo `%c/%s/%d/%%`): moltiplica per 10000, separa parte intera e i due decimali con divisione/modulo interi, e gestisce a mano il padding con zero iniziale (`0.05%` invece di `0.5%`) e il caso limite 100.00%.

**`void print_strategy` / `void init_counts`**
`print_strategy` stampa "Adaptive / " o "Simple / " ecc. seguito dalla stringa di complessità ricevuta da `adaptive_sort` (o impostata a mano in `alg_selector` per i flag forzati). `init_counts` azzera tutti gli 11 contatori — va sempre chiamata prima di eseguire qualunque operazione, altrimenti i contatori partono da valori indefiniti nello stack.

### printf_stderr.c — mini printf fatto a mano

**`int printf_stderr(const char *s, ...)` e helper (`ft_handle_format`, `ft_putunbr`, `ft_putchar`, `ft_putstr`)**
Implementazione minimale di printf che scrive solo su **fd 2** (stderr) e supporta solo `%c`, `%s`, `%d`, `%%`. Punti da sapere spiegare a un correttore:

- `ft_putunbr` prende un `unsigned int` e stampa ricorsivamente cifra per cifra (divide per 10 finché >= 10, poi stampa il resto) — **non gestisce il segno**: se venisse usato per stampare un intero negativo con `%d`, il valore verrebbe convertito a unsigned e stamperebbe il numero sbagliato (senza `-`). Nel progetto va bene perché `%d` è usato solo per contatori/totali, sempre >= 0.
- `ft_handle_format` riceve `va_list args` **per valore** e ci chiama `va_arg` dentro: su Linux x86-64 funziona perché lì `va_list` è tipicamente un array (quindi il "passaggio per valore" in realtà passa un puntatore alla stessa struttura, e l'avanzamento è visibile al chiamante) — ma non è comportamento garantito dallo standard C su ogni piattaforma. Se un correttore lo chiede: "funziona qui perché l'ABI x86-64 System V tratta va_list come array-type, ma non è portabile".

### debugger.c

`print_stack`, `print_stack_rank`, `print_vars`, `print_flags`: semplici funzioni di stampa per debug manuale durante lo sviluppo (valore/rank per nodo, contenuto di `t_vars`, stato dei flag). Non fanno parte della logica di ordinamento; utili solo con gdb/printf debugging.

### errors_checker.c

**`void print_error()`**
Stampa `"Error\n"` su stderr ed esce con `exit(1)`. Chiamata da tutti i punti di validazione del progetto: flag sconosciuto, argomento non numerico, overflow, duplicato. È l'unico punto di uscita per errore in tutto il programma — comodo da citare come "gestione errori centralizzata".

---

## 11. Bonus — il checker

Il bonus è un secondo eseguibile (compilato a mano, non c'è target nel Makefile — vedi CLAUDE.md) che legge da stdin una sequenza di operazioni (una per riga, es. `sa`, `pb`, ...) generata da un altro push_swap o scritta a mano, la applica alle due pile costruite dagli stessi argomenti da riga di comando, e alla fine stampa `OK` se stack_a è ordinata e stack_b è vuota, altrimenti `KO`.

### main_bonus.c

**`int main(int argc, char *argv[])`**

```c
int_arr = int_arr_parser(argc, argv, 0);   // bonus non gestisce i flag --xxx
stack_a = list_arg_parser(int_arr, size);
while ((line = get_next_line(0)) != NULL)
{
    checker_ops(&stack_a, &stack_b, line);
    free(line);
}
checker(&stack_a, &stack_b);
```

Legge riga per riga finché `get_next_line` ritorna `NULL` (EOF), applica ogni riga come operazione, poi verifica lo stato finale. Nota: `int_arr_parser` qui è chiamato con `flags_n = 0` perché il checker non accetta i flag custom `--bench` ecc., solo la lista di numeri.

**`char *get_next_line(int fd)` — definita dentro main_bonus.c**
Implementazione classica della celebre **get_next_line** del curriculum 42: mantiene uno `static char *str` tra le chiamate (il "residuo" letto oltre l'ultimo `\n`), legge a blocchi di `BUFFER_SIZE` (12 byte, macro in push_swap.h) byte con `read` finché non trova un `\n` nel buffer accumulato o finché `read` ritorna 0/negativo (EOF/errore), poi separa la riga da restituire (`get_ret_line`) dal residuo da tenere per la prossima chiamata (`ft_split`, nome fuorviante: qui non fa uno split in stile array di stringhe, ma taglia via la parte già restituita dal buffer statico).

**`void checker_ops(t_list **a, t_list **b, char *ops)`**
Confronta la riga letta (che include ancora il carattere `'\n'` finale, es. `"sa\n"`) con ciascuno dei nomi di operazione validi tramite `ps_strcmp`, e chiama la funzione operazione corrispondente con `print=0` (il checker non deve ristampare le operazioni, solo applicarle silenziosamente) — eccetto `rra`, chiamata con `print=1`: probabilmente un refuso di sviluppo/debug rimasto nel codice, da controllare prima della difesa perché stamperebbe `"rra"` su stdout ogni volta che il checker riceve quell'operazione, cosa che uno script di valutazione automatico non si aspetta. Se la riga non combacia con nessuna operazione nota, chiama `print_error()`.

**`void checker(t_list **stack_a, t_list **stack_b)`**
`is_sorted(*stack_a) && !*stack_b`: la sequenza di operazioni è valida solo se, alla fine, A è ordinata E B è completamente vuota (nessun elemento dimenticato in B). Scrive `"OK\n"` o `"KO\n"` direttamente con `write` su fd 1.

### get_next_line_utils_bonus.c

**`int ft_strchr(const char *s, int c)`**
Versione booleana (ritorna 0/1, non un puntatore come la libc): usata solo per sapere *se* `str` contiene già un `\n`, non *dove*. Gestisce `s == NULL` ritornando 0 (utile alla prima chiamata di `get_next_line`, quando lo static `str` è ancora NULL).

**`char *ft_strdup` / `char *ft_strjoin`**
`ft_strjoin` concatena `s1` e `s2` in un buffer nuovo e **libera sempre `s1`** (anche sui percorsi di errore, con l'idioma `return (free(s1), NULL)`) — coerente con l'uso in `get_next_line`, dove `s1` è il vecchio buffer `str` che va sempre sostituito dal nuovo join, mai tenuto in vita due volte.

**`char *ft_split(char *str)`**
Nome eredità dal progetto *get_next_line* originale del curriculum 42 ma qui il comportamento è diverso da un vero "split": cerca il primo `\n` in `str`, copia tutto ciò che viene **dopo** in un nuovo buffer (il residuo da riusare alla prossima `get_next_line`), libera `str` e ritorna il residuo. Se non trova nessun `\n` (fine file raggiunta senza newline finale), il residuo è vuoto (`""`).

**`char *get_ret_line(char *str)`**
Estrae la porzione di `str` **fino al** primo `\n` incluso (la riga da restituire al chiamante). Se `str` non contiene `\n` (ultimo pezzo di file senza newline finale), ritorna semplicemente una copia (`ft_strdup`) di tutto `str`.

---

## 12. Bug noti e punti deboli — checklist pre-difesa

| # | Dove | Problema | Rischio in difesa |
|---|------|----------|--------------------|
| 1 | alg_complex.c (sort_a, sort_b, partition_a, partition_b, complex_sort) | printf di debug su stdout non rimossi | Rompe l'output valutabile ogni volta che si usa complex/adaptive con disordine alto — **massima priorità** |
| 2 | operations_reverse_rotate.c riga 39 | if senza graffe: `rrb` stampa sempre e conta doppio | Output sporco ogni volta che si chiama `rrr` |
| 3 | main.c | `int_arr` e le due pile non vengono mai liberate (free commentati) | Memory leak — un correttore con un check di leak (valgrind) lo nota subito |
| 4 | main_bonus.c, checker_ops | `rra` chiamata con `print=1` invece di 0 | Il checker stampa "rra" su stdout, comportamento anomalo rispetto alle altre operazioni |
| 5 | flags.c | `flags[5]` è indicizzato ma l'array in main è dichiarato `static int flags[5]` (taglia per indici 0..4) | Undefined behaviour tecnico, anche se non osservabile a runtime su questo target |
| 6 | tester.c/2/3/4 | Vecchi main di prova non compilati dal Makefile, con chiamate a firme di funzione ormai cambiate | Da poter spiegare se chiesto "cosa sono questi file?" — non sono usati, sono scratch di sviluppo |

Consiglio pratico: sistemare almeno i punti 1 e 2 **prima** della difesa, sono quelli che un correttore vede semplicemente eseguendo il programma normalmente.

---

## 13. Domande tipiche da correttore e risposte pronte

**D: Perché avete scelto 3 (+1 adattiva) strategie diverse invece di una sola?**
R: Perché la complessità ottimale dipende dal grado di disordine dell'input: con poco disordine il numero reale di scambi necessari è basso anche con un algoritmo O(n²), quindi non vale la pena pagare l'overhead costante più alto di un quicksort a due pile; con disordine alto invece l'O(n²) diventa concretamente più lento e conviene la strategia O(n log n). La modalità adaptive misura il disordine con `compute_disorder` e sceglie automaticamente in base a soglie (0.2 e 0.5).

**D: Come misurate il disordine?**
R: Contando le coppie invertite (inversioni) rispetto al totale delle coppie possibili: `mistakes / total_pairs`, in disorder.c. 0 significa già ordinato, 1 significa ordinato al contrario.

**D: Perché usate il rank invece del valore per confrontare/ordinare?**
R: I valori possono essere sparsi arbitrariamente (anche interi enormi o negativi); il rank li rimappa in `0..size-1`, un intervallo denso su cui pivot e chunk possono essere calcolati con semplice aritmetica di indici, senza dover gestire "buchi" nei valori.

**D: Perché ogni `ra`/`rra` è O(n) e non O(1)?**
R: Perché la lista è singolarmente concatenata (`t_list` ha solo `next`, non `prev`, e non c'è un puntatore separato alla coda): per fare `ra` serve comunque scorrere fino all'ultimo nodo per riattaccarci in coda il vecchio primo; stesso discorso per `rra`, che deve trovare l'ultimo e il penultimo nodo.

**D: Come decidete se ruotare in avanti (ra) o indietro (rra) per portare un elemento in cima?**
R: Si confronta la posizione dell'elemento target con `size / 2`: se è nella prima metà conviene ruotare in avanti (meno passi), altrimenti conviene ruotare all'indietro. La stessa idea è riusata identica in tre punti del codice: `move_to_top` (simple), `move_to_top_chunk` e `move_to_top_b` (medium).

**D: Nel medium sort, come scegliete l'ampiezza dei chunk?**
R: `calculate_chunk` trova il quadrato perfetto più vicino a `size` per approssimare `√size`: dividere l'intervallo di rank in circa √n fette da √n elementi ciascuna è ciò che dà il fattore O(n·√n) — n elementi processati, ciascuno con una ricerca dentro una fetta di ampiezza media √n.

**D: Come funziona la partizione nel complex sort (quicksort a due pile)?**
R: Si sceglie un pivot come punto medio del range di rank corrente. Si scorre la pila una volta: gli elementi con rank sotto il pivot vengono spinti sull'altra pila (`pb`/`pa`), quelli sopra vengono ruotati in fondo alla porzione corrente (`ra`/`rb`) per non essere ritoccati due volte nello stesso passaggio; a fine scansione le rotazioni vengono eventualmente annullate con altrettante rotazioni inverse per preservare l'ordine relativo col resto della pila. Poi si ricorre separatamente sulle due metà.

**D: Cosa succede se passo due volte lo stesso numero?**
R: `compute_disorder` confronta ogni coppia di valori e chiama `print_error()` (che stampa "Error" su stderr ed esce con status 1) appena trova due valori uguali — i duplicati non sono ammessi dalle specifiche del progetto.

**D: Cosa succede con un numero non valido, es. lettere o overflow di int?**
R: `atoi_safe` chiama `print_error()` se il primo carattere non è una cifra (dopo l'eventuale segno), se resta un carattere non numerico dopo le cifre, o se il valore accumulato supererebbe INT_MAX/INT_MIN — controllato *prima* di eseguire la moltiplicazione per evitare overflow undefined behaviour su `int`.

**D: Come funziona il vostro checker (bonus)?**
R: Ricostruisce le stesse due pile dagli argomenti da riga di comando, poi legge da stdin, riga per riga con una `get_next_line` scritta a mano, i nomi delle 11 operazioni valide e le applica silenziosamente (`print=0`) a stack_a/stack_b. Alla fine stampa OK solo se stack_a risulta ordinata E stack_b è completamente vuota; qualsiasi riga che non corrisponde a un'operazione valida causa `print_error()`.

**D: Perché avete scritto il vostro `printf_stderr` invece di usare quello della libc?**
R: Per il bench, che va solo su stderr e non deve interferire con l'output valutabile su stdout; inoltre al 42 l'uso della libc printf è tipicamente vietato fuori da libft/scopi diagnostici. La nostra versione supporta solo `%c/%s/%d/%%`, sufficiente per le statistiche del bench.

**D: Come gestite gli argomenti/flag opzionali come `--bench`?**
R: `flags_parser` guarda solo i primi due argomenti dopo il nome del programma, cercando stringhe che iniziano con `--` e combaciano con uno dei 5 flag noti; `flags_num` conta quanti sono stati attivati e serve a calcolare da quale indice di `argv` iniziano i numeri veri e propri.

---

## 14. Esercizi di live coding

Per ciascun esercizio: prova a scrivere la funzione da zero, con la firma data, **senza guardare il codice originale**. Le soluzioni (identiche al codice del progetto) sono tutte raggruppate nella sezione finale, dopo il divisorio — non guardarle finché non hai finito il tentativo.

**Esercizio 1 — is_sorted**
Scrivi `int is_sorted(t_list *stack)`: ritorna 1 se la pila è già ordinata in modo crescente (o ha 0/1 elementi), 0 altrimenti.

**Esercizio 2 — stack_size e find_min_index**
Scrivi `int stack_size(t_list *stack)` e `int find_min_index(t_list *stack)` (ritorna la posizione, non il valore, dell'elemento minimo, partendo da 0 per la testa).

**Esercizio 3 — sa**
Scrivi `void sa(t_list **lst)` (versione semplificata, senza count/print): scambia i primi due elementi della pila senza copiare i valori, solo ricollegando i puntatori.

**Esercizio 4 — ra e rra**
Scrivi `void ra(t_list **stack_a)` (il primo elemento diventa l'ultimo) e `void rra(t_list **stack_a)` (l'ultimo elemento diventa il primo), versioni semplificate senza count/print.

**Esercizio 5 — pa / pb**
Scrivi `void pa(t_list **stack_a, t_list **stack_b)`: sposta la cima di stack_b in cima a stack_a.

**Esercizio 6 — move_to_top (rotazione ottimale)**
Data una funzione `find_min_index` già scritta, implementa `void move_to_top(t_list **a)` che porta il minimo in cima usando il minor numero di rotazioni possibile (confrontando la distanza in avanti con quella all'indietro).

**Esercizio 7 — compute_disorder**
Scrivi `float compute_disorder(int array[], int arraylen)`: conta le coppie invertite su tutte le coppie possibili e ritorna il rapporto come float. Bonus: fai in modo che rilevi anche eventuali duplicati.

**Esercizio 8 — atoi_safe**
Scrivi `int atoi_safe(const char *str)`: come atoi, ma deve rifiutare (via `print_error()`, assumila già definita) stringhe non puramente numeriche e prevenire overflow/underflow su `int`.

**Esercizio 9 — calculate_chunk**
Scrivi `int calculate_chunk(int size)`: ritorna un'ampiezza di chunk vicina a `√size`, usando solo somme/moltiplicazioni intere (no `sqrt` di math.h).

**Esercizio 10 — spiegazione a voce (senza scrivere codice)**
Spiega a voce, disegnando su carta/lavagna se serve, come `partition_a` del complex sort decide se un elemento resta in A o va spinto in B, e perché alla fine di `partition_a` è necessario annullare le rotazioni fatte con altrettanti `rra`.

---
---

# SOLUZIONI — non leggere prima di aver provato da solo

---

### Soluzione 1 — is_sorted

```c
int is_sorted(t_list *stack)
{
    t_list *current;

    if (stack == NULL || stack->next == NULL)
        return (1);
    current = stack;
    while (current->next != NULL)
    {
        if (current->value > current->next->value)
            return (0);
        current = current->next;
    }
    return (1);
}
```

### Soluzione 2 — stack_size e find_min_index

```c
int stack_size(t_list *stack)
{
    int size;

    size = 0;
    while (stack != NULL)
    {
        size++;
        stack = stack->next;
    }
    return (size);
}

int find_min_index(t_list *stack)
{
    int min;
    int min_pos;
    int pos;
    t_list *current;

    min = stack->value;
    min_pos = 0;
    pos = 0;
    current = stack;
    while (current->next != NULL)
    {
        current = current->next;
        pos++;
        if (current->value < min)
        {
            min = current->value;
            min_pos = pos;
        }
    }
    return (min_pos);
}
```

### Soluzione 3 — sa

```c
void sa(t_list **lst)
{
    t_list *temp;

    if (!lst || !*lst || !(*lst)->next)
        return ;
    temp = (*lst)->next;
    (*lst)->next = temp->next;
    temp->next = *lst;
    *lst = temp;
}
```

### Soluzione 4 — ra e rra

```c
void ra(t_list **stack_a)
{
    t_list *first;
    t_list *node;

    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return ;
    first = *stack_a;
    *stack_a = first->next;
    node = *stack_a;
    while (node->next)
        node = node->next;
    node->next = first;
    first->next = NULL;
}

void rra(t_list **stack_a)
{
    t_list *last;
    t_list *before_last;

    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return ;
    last = *stack_a;
    before_last = NULL;
    while (last->next)
    {
        before_last = last;
        last = last->next;
    }
    before_last->next = NULL;
    last->next = *stack_a;
    *stack_a = last;
}
```

### Soluzione 5 — pa

```c
void pa(t_list **stack_a, t_list **stack_b)
{
    t_list *top_b;

    if (!stack_b || !*stack_b)
        return ;
    top_b = *stack_b;
    *stack_b = top_b->next;
    top_b->next = *stack_a;
    *stack_a = top_b;
}
```

### Soluzione 6 — move_to_top

```c
void move_to_top(t_list **a)
{
    int min_pos;
    int size;
    int moves;

    min_pos = find_min_index(*a);
    size = stack_size(*a);
    if (min_pos <= size / 2)
    {
        while (min_pos-- > 0)
            ra(a);
    }
    else
    {
        moves = size - min_pos;
        while (moves-- > 0)
            rra(a);
    }
}
```

### Soluzione 7 — compute_disorder

```c
float compute_disorder(int array[], int arraylen)
{
    int mistakes;
    int total_pairs;
    int i;
    int j;

    mistakes = 0;
    total_pairs = 0;
    i = 0;
    while (i < arraylen)
    {
        j = i + 1;
        while (j < arraylen)
        {
            if (array[i] == array[j])
                print_error();
            if (array[i] > array[j])
                mistakes++;
            total_pairs++;
            j++;
        }
        i++;
    }
    return ((float)mistakes / (float)total_pairs);
}
```

### Soluzione 8 — atoi_safe

```c
int atoi_safe(const char *str)
{
    int result;
    int sign;
    int digit;

    result = 0;
    sign = 1;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    if (*str < '0' || *str > '9')
        print_error();
    while (*str >= '0' && *str <= '9')
    {
        digit = *str - '0';
        if (sign == 1 && result > (INT_MAX - digit) / 10)
            print_error();
        if (sign == -1 && (unsigned int)result > ((unsigned int)INT_MAX + 1 - digit) / 10)
            print_error();
        result = result * 10 + digit;
        str++;
    }
    if (*str != '\0')
        print_error();
    return (result * sign);
}
```

### Soluzione 9 — calculate_chunk

```c
int calculate_chunk(int size)
{
    int chunk_size;
    int i;

    i = 1;
    chunk_size = 1;
    while (chunk_size <= size)
    {
        chunk_size = i * i;
        i++;
    }
    i -= 2;
    return (i);
}
```

### Soluzione 10 — spiegazione partition_a

Il pivot è il punto medio del range di rank corrente (es. range [0,9] -> pivot 4). Si scorre la pila per `size` elementi: se il rank della cima è `< pivot`, quell'elemento appartiene alla metà "bassa", quindi va spinto in B con `pb` (verrà poi ordinato da `sort_b` nel range `[min, pivot-1]`); se invece il rank è `>= pivot`, appartiene alla metà "alta" che deve restare in A, ma va tolto temporaneamente dalla cima per poter vedere gli elementi successivi: si usa `ra`, che lo sposta in fondo alla porzione.

Dopo aver scorso tutti i `size` elementi, la porzione "alta" rimasta in A è nell'ordine in cui è stata ruotata, non nell'ordine originale rispetto al resto della pila sotto di essa (se la pila ha altri elementi sotto, oltre alla porzione trattata). Per questo, se `total_stack_a > size` (cioè ci sono altri elementi sotto non ancora processati), si annullano esattamente le rotazioni fatte (`rotates` volte `rra`), riportando la porzione "alta" in cima nell'ordine relativo originale, pronta per la successiva chiamata ricorsiva di `sort_a`.
