#include "header.h"
/* Trova un gruppo di clienti incompatibili */
int *trovaGruppoIncompatibili(int num_clienti, int **matriceAdiacenza, int *size) {
    int i, j, maxIncompatibili;
    int clienteMaxIncompatibili;
    int incompatibiliGruppo;
    int *incompatibili = (int *)calloc(num_clienti, sizeof(int));
    int *gruppo = (int *)calloc(num_clienti, sizeof(int));
    int gruppoSize = 0;
    maxIncompatibili = 0;
    clienteMaxIncompatibili = 0;

    /*Calcola il numero di clienti incompatibili per ciascun cliente*/
    for (i = 0; i < num_clienti; i++) {
        for (j = 0; j < num_clienti; j++) {
            if (matriceAdiacenza[i][j] == 1) {
                incompatibili[i]++;
            }
        }
        /*Trova il cliente con il massimo numero di incompatibilità*/
        if (incompatibili[i] > maxIncompatibili) {
            maxIncompatibili = incompatibili[i];
            clienteMaxIncompatibili = i;
        }
    }

    /*Aggiunge il cliente principale al gruppo*/
    gruppo[gruppoSize++] = clienteMaxIncompatibili;
    incompatibili[clienteMaxIncompatibili] = -1;

    /*Aggiunge gli altri clienti incompatibili al gruppo*/
    while (1) {
        maxIncompatibili = -1;
        clienteMaxIncompatibili = -1;

        for (i = 0; i < num_clienti; i++) {
            if (incompatibili[i] == -1) continue;

            incompatibiliGruppo = 0;
            for (j = 0; j < gruppoSize; j++) {
                if (matriceAdiacenza[i][gruppo[j]] == 1) {
                    incompatibiliGruppo++;
                }
            }

            /*Verifica se il cliente è incompatibile con tutti i clienti nel gruppo*/
            if (incompatibiliGruppo == gruppoSize && incompatibili[i] > maxIncompatibili) {
                maxIncompatibili = incompatibili[i];
                clienteMaxIncompatibili = i;
            }
        }

        /*Se non ci sono più clienti incompatibili da aggiungere, esce dal ciclo*/
        if (clienteMaxIncompatibili == -1) {
            break;
        }

        /*Aggiunge il cliente al gruppo e lo contrassegna come già aggiunto*/
        gruppo[gruppoSize++] = clienteMaxIncompatibili;
        incompatibili[clienteMaxIncompatibili] = -1;
    }

    /*Imposta il valore di size al numero di clienti nel gruppo e restituisce l'array gruppo*/
    *size = gruppoSize;
    free(incompatibili);
    return gruppo;
}

/*  Stampa i nomi dei clienti incompatibili  */
void stampa_nomi_incompatibili(Cliente *cliente, int num_clienti, int **matrice_adiacenza) {
    int gruppoSize;
    int *gruppo = trovaGruppoIncompatibili(num_clienti, matrice_adiacenza, &gruppoSize);
    int i;
    char **nomi_incompatibili;
    printf("almeno %d pizze\n", gruppoSize);

    /*Crea un array di puntatori a stringhe e popola con i nomi dei clienti nel gruppo*/
    nomi_incompatibili = (char **)malloc(gruppoSize * sizeof(char *));
    for (i = 0; i < gruppoSize; i++) {
        nomi_incompatibili[i] = cliente[gruppo[i]].nome;
    }

    /*Ordina i nomi in ordine alfabetico*/
    mergesort(nomi_incompatibili, gruppoSize, sizeof(char *), compareNomiClienti);

    /*Stampa i nomi dei clienti incompatibili separati da uno spazio*/
    for (i = 0; i < gruppoSize; i++) {
        printf("%s", nomi_incompatibili[i]);
        if (i < gruppoSize ) {
            printf(" ");
        }
    }

    printf("\n");

    /*Libera la memoria allocata per l'array gruppo e nomi_incompatibili*/
    free(gruppo);
    free(nomi_incompatibili);
}
