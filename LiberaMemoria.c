#include "header.h"
/*Distruggi pizza*/
void distruggiPizza(Pizza *pizza) {
    int i;
    /*libera pizza->ingredienti*/
    for(i=0; i<pizza->nIngredienti; i++)
    {
        free(pizza->ingredienti[i]);
    }
    free(pizza->ingredienti);
    /*libera pizza->clienti soddisfatti*/
    for(i=0; i<pizza->nClientiSoddisfatti; i++)
    {
        free(pizza->clienti_soddisfatti[i]);
    }
    free(pizza->clienti_soddisfatti);
}
/*Distruggi menu*/
void distruggiMenu(Pizza *menu, int n) {
    int i;
    for(i=0; i<n; i++)
    {
        distruggiPizza(&menu[i]);
    }
    free(menu);
}
/*Distruggi ListaClienti*/
void distruggiListaClienti(Cliente *lista_clienti) {
    Cliente *temp;
    int i;

    while (lista_clienti != NULL) {
        temp = lista_clienti;
        lista_clienti = lista_clienti->next;
        /* Free the memory allocated for the richiesti, esclusi, and graditi arrays*/
        for (i = 0; i < temp->nRichieste; i++) {
            free(temp->richiesti[i]);
        }
        free(temp->richiesti);

        for (i = 0; i < temp->nEsclusioni; i++) {
            free(temp->esclusi[i]);
        }
        free(temp->esclusi);

        for (i = 0; i < temp->nGradimenti; i++) {
            free(temp->graditi[i]);
        }
        free(temp->graditi);

        /*Free the memory allocated for the Cliente structure*/
        free(temp);
    }
    free(lista_clienti);
}
/*Libera tutto ciò che non è stato liberato*/
void free_memory(Cliente *cliente, int num_clienti, int num_ingredienti, int **matrice_adiacenza, void *gruppo, void *frequenze_esclusioni, void *opinioni_array) {
    int i, j;

    for (i = 0; i < num_clienti; i++) {
        for (j = 0; j < num_ingredienti; j++) {
            free(cliente[i].richiesti[j]);
            free(cliente[i].graditi[j]);
            free(cliente[i].esclusi[j]);
        }
        free(cliente[i].richiesti);
        free(cliente[i].graditi);
        free(cliente[i].esclusi);
    }
    free(cliente);

    for (i = 0; i < num_clienti; i++) {
        free(matrice_adiacenza[i]);
    }
    free(matrice_adiacenza);

    free(gruppo);
    free(frequenze_esclusioni);
    free(opinioni_array);
}
