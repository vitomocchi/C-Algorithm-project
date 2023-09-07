#include "header.h"

/* Interpreta la linea di comando */
void InterpretaLineaComando(int argc, char *argv[], char *ingredienti_file, char *clienti_file)
{
    /* Verifica il numero corretto di argomenti nella linea di comando */
    if (argc != 3)
    {
        fprintf(stderr, "Errore nella linea di comando!\n");
        exit(EXIT_FAILURE);
    }
    
    /* Copia i nomi dei file dagli argomenti nella variabili corrispondenti */
    strcpy(ingredienti_file, argv[1]);
    strcpy(clienti_file, argv[2]);
}

/* Inizializza le opinioni sugli ingredienti */
void inizializza_opinioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti, FILE *fp1)
{
    int i;

    /* Inizializza le opinioni per ogni ingrediente */
    for (i = 0; i < num_ingredienti; i++)
    {
        /* Legge il nome dell'ingrediente dal file */
        fscanf(fp1, "%s", opinioni_array[i].ingrediente);

        /* Inizializza i conteggi delle richieste, esclusioni e gradimenti a zero */
        opinioni_array[i].nRichieste = 0;
        opinioni_array[i].nEsclusioni = 0;
        opinioni_array[i].nGradimenti = 0;
    }
}

/* Inizializza i clienti */
void inizializza_clienti(Cliente *cliente, int num_clienti, int num_ingredienti, FILE *fp2, opinioniSuIngrediente *opinioni_array)
{
    int i, j, k;

    /* Inizializza ogni cliente */
    for (i = 0; i < num_clienti; i++)
    {
        /* Legge il nome del cliente dal file */
        fscanf(fp2, "%s", cliente[i].nome);

        /* Alloca dinamicamente memoria per i vettori di ingredienti richiesti, graditi ed esclusi */
        cliente[i].richiesti = (char **)calloc(num_ingredienti, sizeof(char *));
        cliente[i].graditi = (char **)calloc(num_ingredienti, sizeof(char *));
        cliente[i].esclusi = (char **)calloc(num_ingredienti, sizeof(char *));

        /* Verifica se l'allocazione di memoria ha avuto successo */
        if (cliente[i].richiesti == NULL || cliente[i].graditi == NULL || cliente[i].esclusi == NULL)
        {
            printf("Errore nell'allocazione della memoria ");
            /* Gestire l'errore qui (ad esempio con una exit o una return) */
        }

        /* Alloca dinamicamente memoria per i vettori di ingredienti richiesti per il cliente corrente */
        for (j = 0; j < num_ingredienti; j++)
        {
            cliente[i].richiesti[j] = (char *)calloc(N, sizeof(char));
        }

        /* Legge il numero di ingredienti richiesti dal file per il cliente corrente */
        fscanf(fp2, "%d", &cliente[i].nRichieste);

        /* Legge gli ingredienti richiesti dal file per il cliente corrente */
        for (k = 0; k < cliente[i].nRichieste; k++)
        {
            fscanf(fp2, "%s", cliente[i].richiesti[k]);
        }

        /* Alloca dinamicamente memoria per i vettori di ingredienti graditi per il cliente corrente */
        for (j = 0; j < num_ingredienti; j++)
        {
            cliente[i].graditi[j] = (char *)calloc(N, sizeof(char));
        }

        /* Legge il numero di ingredienti graditi dal file per il cliente corrente */
        fscanf(fp2, "%d", &cliente[i].nGradimenti);

        /* Legge gli ingredienti graditi dal file per il cliente corrente */
        for (k = 0; k < cliente[i].nGradimenti; k++)
        {
            fscanf(fp2, "%s", cliente[i].graditi[k]);
        }

        /* Alloca dinamicamente memoria per i vettori di ingredienti esclusi per il cliente corrente */
        for (j = 0; j < num_ingredienti; j++)
        {
            cliente[i].esclusi[j] = (char *)calloc(N, sizeof(char));
        }

        /* Legge il numero di ingredienti esclusi dal file per il cliente corrente */
        fscanf(fp2, "%d", &cliente[i].nEsclusioni);

        /*Legge gli ingredienti esclusi dal file per il cliente corrente*/
        for (k = 0; k < cliente[i].nEsclusioni; k++)
        {
            fscanf(fp2, "%s", cliente[i].esclusi[k]);
        }

        /*Aggiorna le opinioni degli ingredienti in base ai dati del cliente*/
        for (j = 0; j < num_ingredienti; j++)
        {
            for (k = 0; k < cliente[i].nRichieste; k++)
            {
                if (strcmp(opinioni_array[j].ingrediente, cliente[i].richiesti[k]) == 0)
                {
                    opinioni_array[j].nRichieste++;
                }
            }
            for (k = 0; k < cliente[i].nGradimenti; k++)
            {
                if (strcmp(opinioni_array[j].ingrediente, cliente[i].graditi[k]) == 0)
                {
                    opinioni_array[j].nGradimenti++;
                }
            }
            for (k = 0; k < cliente[i].nEsclusioni; k++)
            {
                if (strcmp(opinioni_array[j].ingrediente, cliente[i].esclusi[k]) == 0)
                {
                    opinioni_array[j].nEsclusioni++;
                }
            }
        }
    }
}

/* Stampa le opinioni degli ingredienti */
void stampa_opinioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti)
{
    int i;

    /*Ordina l'array di opinioni*/
    mergesort_opinioni(opinioni_array, 0, num_ingredienti - 1);

    /*Stampa il numero di ingredienti*/
    printf("%d ingredienti\n", num_ingredienti);

    /*Stampa le opinioni di ogni ingrediente*/
    for (i = 0; i < num_ingredienti; i++)
    {
        printf("%s %d %d %d\n", opinioni_array[i].ingrediente, opinioni_array[i].nEsclusioni, opinioni_array[i].nRichieste, opinioni_array[i].nGradimenti);
    }
}

/* Stampa i dettagli dei clienti */
void stampa_clienti(Cliente *cliente, int num_clienti)
{
    int i;

    /*Ordina l'array di clienti*/
    mergesort_clienti(cliente, 0, num_clienti - 1);

    /*Stampa il numero di clienti*/
    printf("%d clienti\n", num_clienti);

    /*Stampa i dettagli di ogni cliente*/
    for (i = 0; i < num_clienti; i++)
    {
        /*Calcola il numero di vincoli forti per il cliente corrente*/
        int vincoli_forti = cliente[i].nRichieste + cliente[i].nEsclusioni;

        printf("%s %d %d\n", cliente[i].nome, vincoli_forti, cliente[i].nGradimenti);
    }
}

/* Calcola le frequenze delle esclusioni */
void frequenza_esclusioni(opinioniSuIngrediente *opinioni_array, int num_ingredienti, int *frequenze, int num_clienti)
{
    int i;

    /*Inizializza l'array delle frequenze a zero*/
    for (i = 0; i <= num_clienti; i++)
    {
        frequenze[i] = 0;
    }

    /*Calcola le frequenze delle esclusioni*/
    for (i = 0; i < num_ingredienti; i++)
    {
        int esclusioni = opinioni_array[i].nEsclusioni;
        if (esclusioni >= 0)
        {
            frequenze[esclusioni]++;
        }
    }
}

/* Stampa le frequenze delle esclusioni */
void stampa_frequenze_esclusioni(int *frequenze_esclusioni, int num_clienti)
{
    int i;

    /* Stampa le frequenze delle esclusioni*/
    printf("esclusioni\n");
    for (i = 0; i <= num_clienti; i++)
    {
        if (frequenze_esclusioni[i] > 0)
        {
            printf("%d per %d clienti\n", frequenze_esclusioni[i], i);
        }
    }
}
