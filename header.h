#ifndef HEADER_H
#define HEADER_H

/* Standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/*Constants*/
#define N 51

/*Structures*/
typedef struct Cliente Cliente;
struct Cliente
{
    int id;
    char nome[N];
    int nRichieste;
    char **richiesti;
    int nEsclusioni;
    char **esclusi;
    int nGradimenti;
    char **graditi;
    struct Cliente *next;
};

typedef struct opinioniSuIngrediente opinioniSuIngrediente;
struct opinioniSuIngrediente
{
    char ingrediente[N];
    int nRichieste;
    int nEsclusioni;
    int nGradimenti;
    struct opinioniSuIngrediente *next;
};

typedef struct Pizza Pizza;
struct Pizza
{
    char **ingredienti;
    int nIngredienti;
    int nClientiSoddisfatti;
    char **clienti_soddisfatti;
} ;

/*Functions*/
void InterpretaLineaComando(int argc, char *argv[], char *ingredienti_file, char *clienti_file);
void inizializza_opinioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti, FILE *fp1);
void inizializza_clienti(Cliente *cliente, int num_clienti, int num_ingredienti, FILE *fp2, opinioniSuIngrediente *opinioni_array);
int compare_opinioni(const opinioniSuIngrediente *a, const opinioniSuIngrediente *b);
void merge_opinioni(opinioniSuIngrediente *arr, int left, int mid, int right);
void mergesort_opinioni(opinioniSuIngrediente *arr, int left, int right);
void stampa_opinioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti);
int cmp_clienti(const void *a, const void *b);
void merge_clienti(Cliente *clienti, int low, int mid, int high);
void mergesort_clienti(Cliente *clienti, int low, int high);
void stampa_clienti(Cliente *cliente, int num_clienti);
void frequenza_esclusioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti, int *frequenze, int num_clienti);
void stampa_frequenze_esclusioni(int *frequenze_esclusioni, int num_clienti);
void merge(void *dest, void *src1, int num1, void *src2, int num2, size_t size, int (*cmpfun)(const void *, const void *));
void sort_helper(void *dst, void *src, int num, size_t size, int (*cmpfun)(const void *, const void *));
int compareClienti(const void *a, const void *b);
void mergesort(void *arr, int num, size_t size, int (*cmpfun)(const void *, const void *));
int **calcolaMatriceAdiacenza(Cliente *clienti, int num_clienti);
void stampaMatriceAdiacenza(int **matrice, int num_clienti, Cliente *cliente);
int *trovaGruppoIncompatibili(int num_clienti, int **matriceAdiacenza, int *size);
int compareNomiClienti(const void *a, const void *b);
void stampa_nomi_incompatibili(Cliente *cliente, int num_clienti, int **matrice_adiacenza);
Pizza creaPizzaVuota();
void aggiungiIngredienteAPizza(Pizza *pizza, opinioniSuIngrediente *ingrediente);
int contaEsclusioni(Cliente *lista_clienti, const char *ingrediente);
opinioniSuIngrediente *trovaIngredienteMenoEsclusioni(Cliente *lista_clienti, opinioniSuIngrediente *lista_ingredienti);
int compareIngredientiAlf(const void *a, const void *b);
void rimuoviClientiCheEscludonoIngrediente(Cliente **lista_clienti, opinioniSuIngrediente *ingrediente, int *num_clienti_insoddisfatti);
bool ingredienteEsclusoDaTutti(opinioniSuIngrediente *ingrediente, Cliente *lista_clienti);
void rimuoviClientiSoddisfatti(Cliente **head, Pizza *pizza, int *num_clienti);
void rimuoviIngredienteDaListaIngredienti(opinioniSuIngrediente **lista_ingredienti, opinioniSuIngrediente *ingrediente_da_rimuovere, int *num_ingredienti);
opinioniSuIngrediente *creaListaIngredientiDaArray(opinioniSuIngrediente *array_ingredienti, int num_ingredienti);
Cliente *creaListaClientiDaArray(Cliente *array_clienti, int num_clienti);
char **copiaArrayStringhe(char **array, int n);
Cliente *copiaCliente(Cliente *cliente);
Cliente *copiaListaClienti(Cliente *lista_clienti);
int compare_strings(const void *a, const void *b);
void stampaPizza(Pizza *pizza);
void distruggiPizza(Pizza *pizza);
void distruggiMenu(Pizza *menu, int n);
void distruggiListaClienti(Cliente *lista_clienti);
void buildMenu(Cliente *cliente, int num_clienti, int num_ingredienti, opinioniSuIngrediente opinioni_array[]);
void free_memory(Cliente *cliente, int num_clienti, int num_ingredienti, int **matrice_adiacenza, void *gruppo, void *frequenze_esclusioni, void *opinioni_array);
#endif