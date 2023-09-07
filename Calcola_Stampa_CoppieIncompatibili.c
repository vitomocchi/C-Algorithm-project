#include "header.h"
/*Confronta i clienti per numero di richieste, esclusioni e nome*/
int **calcolaMatriceAdiacenza(Cliente *clienti, int num_clienti)
{
    int i, j, k, l;
    int incompatibile; 
    /* Dichiaro e alloco matrice dinamica con valori iniziali tutti nulli */
    int **adj;
    mergesort(clienti, num_clienti, sizeof(Cliente), compareClienti);

    adj = (int **)calloc(num_clienti, sizeof(int *));
    for (i = 0; i < num_clienti; i++)
    {
        adj[i] = (int *)calloc(num_clienti, sizeof(int));
    }
    /*trova le coppie di clienti incompatibili*/
    for (i = 0; i < num_clienti; i++)
    {
        for (j = i + 1; j < num_clienti; j++)
        {
            incompatibile = 0;
            for (k = 0; k < clienti[i].nRichieste && !incompatibile; k++)
            {
                for (l = 0; l < clienti[j].nEsclusioni && !incompatibile; l++)
                {
                    if (strcmp(clienti[i].richiesti[k], clienti[j].esclusi[l]) == 0)
                    {
                        incompatibile = 1;
                    }
                }
            }
            for (k = 0; k < clienti[j].nRichieste && !incompatibile; k++)
            {
                for (l = 0; l < clienti[i].nEsclusioni && !incompatibile; l++)
                {
                    if (strcmp(clienti[j].richiesti[k], clienti[i].esclusi[l]) == 0)
                    {
                        incompatibile = 1;
                    }
                }
            }
            adj[i][j] = incompatibile;
            adj[j][i] = incompatibile;
        }
    }

    return adj;
}

/* Stampa la matrice di adiacenza */
void stampaMatriceAdiacenza(int **matrice, int num_clienti, Cliente *cliente)
{
    char *ausiliaria;
    int num_coppie_incompatibili;
    int i, j; 
    num_coppie_incompatibili = 0;
    ausiliaria = (char *)calloc(N * N * num_clienti * num_clienti, sizeof(char));
    
    for (i = 0; i < num_clienti; i++)
    {
        for (j = i + 1; j < num_clienti; j++)
        {
            if (matrice[i][j] == 1)
            {
                num_coppie_incompatibili++;
                strcat(ausiliaria, cliente[i].nome);
                strcat(ausiliaria, " ");
                strcat(ausiliaria, cliente[j].nome);
                strcat(ausiliaria, "\n");
            }
        }
    }
    printf("%d coppie incompatibili\n%s", num_coppie_incompatibili, ausiliaria);
    free(ausiliaria);
}
