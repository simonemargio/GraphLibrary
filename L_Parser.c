#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L_Utility.h"
#define DIM 50 // Dim array contenente i caratteri letti da file

/* Salvataggio su file delle info del grafo */
void F_salva_info(FILE *fd,Grafo G,int listmatr)
{
    fprintf(fd,"%d-",G->nsize);     // Num elementi
    fprintf(fd,"%d-",G->infpeso);   // 1=Grafo non pesato - 2=Grafo pesato
    fprintf(fd,"%d-",listmatr);     // 1=Lista Adj - 2=Matrice Adj
    fprintf(fd,"%d\n",G->tipodato); // 1=Int - 2=Float - 3=Char - 4=String
}

/* Salvataggio su file di tutti i nodi */
void F_salva_elem_nodi(FILE *fd,Grafo G)
{
    L li=G->struttura;
    fprintf(fd,"{");
    while (li!=NULL)
    {
        G->salvaelemgrafo(fd,li->nodo); // Richiama: F_salva_elem_int/float/char/string
        li=li->ptrNext;
    }
    fprintf(fd,"}\n");
}

/* Salvataggio su file del nodo di tipo specifico */
void F_salva_elem_int(FILE *fd,void *el)
{
    fprintf(fd,"(%d)",*((int *)el));
}

void F_salva_elem_float(FILE *fd,void *el)
{
    fprintf(fd,"(%f)",*((float *)el));
}

void F_salva_elem_char(FILE *fd,void *el)
{
    fprintf(fd,"(%c)",*((char *)el));
}

void F_salva_elem_string(FILE *fd,void *el)
{
    fprintf(fd,"(%s)",((char *)el));
}

/* Salvataggio dell'informazione relativa ai nodi con i relativi archi e pesi */
void F_salva_archi(FILE *fd,Grafo G)
{
    L li=G->struttura,ar=NULL; int cont=0;

    while (li!=NULL)
    {
        cont=0;
        ar=li->ptrArco; // Preleva l'arco se presente
        G->salvaelemgrafo(fd,li->nodo); // Richiama: F_salva_elem_int/float/char/string

        while (ar!=NULL)
        {
            if(cont>0) G->salvaelemgrafo(fd,li->nodo);
            /* Info su cont:
             * Nel caso in cui siano presenti piu' di un arco uscente dal nodo corrente
             * viene riscritto di nuovo il nodo di partenza.
             * ES:
             * Lista: 12->33->44
             * File: (12)(peso)(33)(12)(peso)(44)
             * */
            if(G->infpeso!=1) fprintf(fd,"(%f)",ar->ptrPeso->peso); // Inserimento del peso
            else fprintf(fd,"(-)");  // Non pesato
            G->salvaelemgrafo(fd,ar->nodo);
            ar=ar->ptrArco;
            cont++;
        }
        fprintf(fd,"\n");
        li=li->ptrNext;
    }
}

/* Funzione per salvare le informazioni di un grafo su file */
void F_salva_grafo(Grafo G)
{
    /* Il salvataggio di un grafo viene effettuato
     * sempre rappresentandoil grafo in termini di lista
     * di Adj. Nel caso in cui il grafo corrente e' nella sua
     * rappresentazione a matrice, esso verra' prima trasformato
     * in una lista e poi salvato nel file.
     * Ovviamente viene mantenuta l'informazione della sua rappresentazione
     * reale. Quando viene letto da file, anche se espresso come una lista, viene
     * trasformato in matrice.
     * */
    FILE *fd=fopen("grafo.txt","w");
    if(fd)
    {
        int c=0;
        /* Caso in cui il grafo e' rappresentato in matrice */
        if(G->listmatr!=1) {F_matrice_a_lista(G); F_salva_info(fd,G,2); c=1; }
        else F_salva_info(fd,G,1); // Scrive su file le info del grafo: n°nodi, tipo dato ecc...
        F_salva_elem_nodi(fd,G);   // Scrive su file tutti i nodi presenti
        F_salva_archi(fd,G);       // Scrive su file i nodi con i relativi archi se presenti
        fprintf(fd,".");           // Terminazione file
        fclose(fd);
        if(c!=0) F_lista_a_matrice(G); // Ripririno della rappresentazione iniziale
    } else puts("\nErrore apertura file, ritorno al menu'!");
}

/* Array usato per contenere i caratteri letti */
char *F_alloca_vett_lettura()
{
    char *arr=malloc(DIM* sizeof(char));
    return arr;
}

/* Inizializzazione dell'array di lettura caratteri */
void F_inizializza_array(char *arr)
{
    int i=0;
    for(i=0;i<DIM;i++)
        arr[i]='x';
}

/* Esegue la lettura di un elemento della prima riga da file */
int F_leggi_prima_riga(FILE *fd,char *arr)
{
    /*Info sulla funzione:
     * La prima riga nel file contiene le seguenti
     * informazioni nel seguente ordine:
     * -Numero di nodi presenti
     * -Pesato o non (1 pes, 2 no)
     * -Lista o matrice (1 list, 2 matr)
     * -Tipo dato (1 int, 2 float, 3 char, 4 stringa)
     * */
    char c,*ptr; int i=0;

    /* Esegue la lettura di ogni valore numerico fino al carattere - */
    do
    {
        c= (char) fgetc(fd);
        if(c!='-'){ arr[i]=c; i++;}

    }while(c!='-' && c!='\n');
    /* Converte il valore letto in un intero */
    int val=strtol(arr,&ptr,10);
    F_inizializza_array(arr);
    return val;
}

/* Funzione principale per la lettura della prima riga da file */
void F_inserisci_info_grafo(Grafo G,FILE *fd,char *arr)
{
    int num_elem=F_leggi_prima_riga(fd,arr);     // Lettura: numero nodi
    int peso=F_leggi_prima_riga(fd,arr);         // Lettura: peso
    int list_matr=F_leggi_prima_riga(fd,arr);    // Lettura: rappresentazione
    int tipo_dato=F_leggi_prima_riga(fd,arr);    // Lettura: tipo di dato
    // Ulteriori info sul valore corretto in: F_leggi_prima_riga
    /* Inserisce tutte le informazioni prese da file e gestisce le giuste callback */
    F_aggiungi_info(G,list_matr,tipo_dato,num_elem,peso);
}

/* Converte il dato letto da file per gestirlo nell'inserimento nel grafo */
void *F_analizza_dato_letto(int tipodato,char *arr,void *elem,int i,FILE *fd)
{
    char *ptr,c, *vett=NULL;

    switch (tipodato)
    {
        case 1: // Intero
            elem=malloc(sizeof(int));
            int e=strtol(arr,&ptr,10);
            memcpy(elem,&e,sizeof(int));
            break;
        case 2: // Float
            printf("");
            elem=malloc(sizeof(float));
            float b= (float) atof(arr);
            if(b<0) {puts("\nValore di un nodo negativo, file non corretto! Si ritorna al menu'."); fclose(fd); F_menu_principale();}
            memcpy(elem,&b,sizeof(float));
            break;
        case 3: // Char
            elem=malloc(sizeof(char));
            c=arr[0];
            memcpy(elem,&c,sizeof(char));
            break;
        case 4: // Stringa
            vett=malloc(sizeof(char)*(i+1));
            int j=0;

            for(j=0;j<i;j++)
                vett[j]=arr[j];
            vett[j]='\0';
            elem=vett;
            break;
        default:
            puts("\nErrore lettura tipo dato nel file del grafo. Ritorno al menu'!");
            fclose(fd);
            F_menu_principale();
            break;
    }

    return elem;
}

/* Legge da file un vertice */
void F_esegui_lettura_vertice(Grafo G, FILE *fd,char *arr,L lis)
{
    char c; int i=0; void *elem=NULL;
    F_inizializza_array(arr);

    /* Legge il nodo da file finche' non termina col carattere ')' */
    do
    {
        c= (char) fgetc(fd);
        if(c!=')'){ arr[i]=c; i++;}

    }while(c!=')' && c!='\n');

    /* Ritorna un puntatore di tipo void "contenente" il vertice letto */
    elem=F_analizza_dato_letto(G->tipodato,arr,elem,i,fd);

    /* E' gia' presente almeno un nodo */
    if(G->struttura!=NULL) lis=G->struttura;
    /* Alloca un nuovo elemento nella rappresentazione a lista di Adj */
    lis=F_alloca_elemento_lista(lis,elem);
    /* Collega la lista alla struttura princiale */
    G->struttura=lis;
}

/* Esegue la lettura di tutti i vertici nella seconda riga */
void F_lettura_vertice(Grafo G, FILE *fd,char *arr,L lis)
{
    /* Fino alla terminazione della seconda riga mediante
     * il carattere '}' si procede a leggere ogni singolo
     * nodo presente
     */
    char c;
    c= (char) fgetc(fd);
    if(c=='}') return;
    else
    {
        F_esegui_lettura_vertice(G,fd,arr,lis); // Legge un singolo vertice
        F_lettura_vertice(G,fd,arr,lis);
    }
}

/* Funzione principale per la lettura della seconda riga da file */
void F_alloca_lista(Grafo G, FILE *fd,char *arr, L lis)
{
    char c;
    c= (char) fgetc(fd);
    if(c=='{')  F_lettura_vertice(G,fd,arr,lis); // Lettura di tutti i vertici della riga
    else { puts("\nErrore nella sintassi del file. Ritorno al menu'!\n"); fclose(fd); F_menu_principale();}

}

/* Ricerca un determinato nodo presente nel grafo (usato per gestire gli archi) */
void *F_cerca_elem_grafo(Grafo G,void *elem,FILE *fd)
{
    L lis=G->struttura; int confronto=-1;

    while(lis!=NULL)
    {
        confronto=G->confronto_elementi(lis->nodo,elem); // Richiama: F_confronto_interi/float/carattere/stringa
        if(confronto==0) {elem=lis; break;}
        lis=lis->ptrNext;
    }
    if(confronto!=0) {puts("\nErrore nella sintassi del file. Elemento non trovato! Ritorno al menu'."); fclose(fd); F_menu_principale();}

    return elem;
}

/* Legge da file il peso dell'arco */
float F_leggi_peso(int infopeso,FILE *fd,char *arr)
{
    char c; int i=0,j=0; void *elem=NULL; float peso=0;

    F_inizializza_array(arr);

    /* Leggia sia un eventuale peso in float che
     * il carattere '-' nel caso in cui il grafo e'
     * non pesato
     */
    do
    {
        c= (char) fgetc(fd);
        if(c=='-') j=1;
        if(c!=')' && c!='-'){ arr[i]=c; i++;}

    }while(c!=')');

    if(infopeso!=1) // Grafo pesato
    {
        elem = F_analizza_dato_letto(2, arr, elem, i,fd);
        peso=*(float *)elem;
    }

    /* Nella prima cella dall'array di lettura da file e' presente '-' */
    if(j!=0) peso=F_ritorna_negativo(peso);

    return peso;
}

/* Costruisce gli archi del grafo */
void F_leggi_nodo_arco(Grafo G, FILE *fd,char *arr)
{
    char c; int i=0; void *elem=NULL; float peso=0;
    F_inizializza_array(arr);

    /* Legge da file finche':
     * Si arriva alla fine di una parentesi
     * Si arriva alla fine della riga '\n'
     * Il file e' terminato
     */
    do
    {
        c= (char) fgetc(fd);
        if((c!='(') && (c!=')')){ arr[i]=c; i++;}
        if(c=='.') return;

    }while(c!=')' && c!='\n');

    /* Lettura di un nodo */
    elem=F_analizza_dato_letto(G->tipodato,arr,elem,i,fd);
    /* Ricerca del nodo all'interno del grafo */
    void *nodo_s=F_cerca_elem_grafo(G,elem,fd);

    /* O si legge la fine della riga
     * oppure una parentesi aperta '('.
     * In questo caso necessariamente sara'
     * presente il peso o il carattere '-'
     */
    c= (char) fgetc(fd);
    if(c=='\n') return;
    peso=F_leggi_peso(G->infpeso,fd,arr);
    F_inizializza_array(arr); i=0;

    /* Lettura del secondo nodo */
    do
    {
        c= (char) fgetc(fd);
        if(c!='(' && c!=')'){ arr[i]=c; i++;}

    }while(c!=')' && c!='\n');

    elem=F_analizza_dato_letto(G->tipodato,arr,elem,i,fd);
    void *nodo_a=F_cerca_elem_grafo(G,elem,fd);

    L s=nodo_s, a=nodo_a, new_elem_a=NULL;

    /* Si provvede ad allocare le relative strutture e ha inserire l'arco */
    new_elem_a=F_alloca_elemento_lista(new_elem_a,a->nodo);

    if(s->ptrArco!=NULL) {
        new_elem_a->ptrArco=s->ptrArco;
        s->ptrArco=new_elem_a;

    } else
        s->ptrArco=new_elem_a;

    if(G->infpeso!=1) // Inserimento del peso
    {
        P PesoNew=F_alloca_struttura_peso(peso);
        new_elem_a->ptrPeso=PesoNew;
    }
}

/* Provvede alla lettura di tutte le righe presenti nel file dalla 2° riga in poi */
void F_lettura_vertice_arco(Grafo G,FILE *fd,char *arr)
{
    char c;
    while (!feof(fd))
    {
        c= (char) fgetc(fd);
        if(c==-1 || c=='.'){puts("\nfine file\n"); return;}; // -1: EOF
        if(c!='(' && c!='\n') {puts("\nErrore nella sintassi del file. Ritorno al menu'."); fclose(fd); F_menu_principale();}
        else F_leggi_nodo_arco(G,fd,arr); // Provvedo alla lettura dei nodi con eventuali archi
    }
}

/* Inizia la lettura della terza riga del file contenente info su nodi e archi */
void F_alloca_nodo(Grafo G,FILE *fd,char *arr)
{
    char c;
    c= (char) fgetc(fd);
    if(c=='\n') F_lettura_vertice_arco(G,fd,arr); // Terminato la seconda riga, passo alla terza
    else { puts("\nErrore nella sintassi del file. Ritorno al menu'!\n"); fclose(fd); F_menu_principale();}
}

/* Funzione principale di lettura del grafo da file */
Grafo F_leggi_grafo(Grafo Old)
{
    Grafo G=NULL; L lis=NULL;
    FILE *fd=fopen("grafo.txt","r");
    if(fd)
    {
        rewind(fd); // Non necessario ma riporta il puntatore a inizio file
        char *arr=F_alloca_vett_lettura(); // Alloca il vettore contenente i caratteri da leggere
        G=F_alloca_grafo(G); // Alloca la struttura principale di gestione del grafo
        F_inserisci_info_grafo(G,fd,arr); // Legge la prima riga (info nella funzione stessa)
        F_alloca_lista(G,fd,arr,lis);     // Legge la seconda riga e alloca i nodi del grafo
        F_alloca_nodo(G,fd,arr);          // Legge tutte le restanti righe per eventuali archi e pesi
        if(G->listmatr!=1) F_lista_a_matrice(G); // Ripristina il grafo nel caso in cui era rappresentato mediate matrice
        fclose(fd);
    } else puts("\nErrore apertura file,"
                "verificare che sia presente il file grafo.txt,"
                " ritorno al menu'!");

    if(G==NULL) G=Old; // In caso di errore apertura file
    else Old->dealloca_grafo(Old->struttura,Old); // Si dealloca il grafo precedente
    return G;
}


