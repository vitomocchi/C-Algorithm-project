#include "header.h"
/* Crea una nuova istanza di Pizza vuota*/
Pizza creaPizzaVuota()
{
    Pizza pizza;
    /*Inizializza gli attributi della pizza a valori nulli o 0*/
    pizza.ingredienti = NULL;
    pizza.nIngredienti = 0;
    pizza.clienti_soddisfatti = NULL;
    pizza.nClientiSoddisfatti = 0;
    return pizza;
}

/* Aggiunge un ingrediente alla Pizza*/
void aggiungiIngredienteAPizza(Pizza *pizza, opinioniSuIngrediente *ingrediente)
{
    if (pizza->ingredienti == NULL)
    {
        /* Se la pizza non ha ancora ingredienti, alloca memoria per il primo ingrediente*/
        pizza->ingredienti = (char **)malloc(sizeof(char *));
        pizza->ingredienti[0] = (char *)malloc(sizeof(char) * N);
        strcpy(pizza->ingredienti[0], ingrediente->ingrediente);
        pizza->nIngredienti = 1;
    }
    else
    {
        /*Se la pizza ha già ingredienti, rialloca memoria per aggiungere un nuovo ingrediente*/
        pizza->ingredienti = (char **)realloc(pizza->ingredienti, sizeof(char *) * (pizza->nIngredienti + 1));
        pizza->ingredienti[pizza->nIngredienti] = (char *)malloc(sizeof(char) * N);
        strcpy(pizza->ingredienti[pizza->nIngredienti], ingrediente->ingrediente);
        pizza->nIngredienti++;
    }
}

/*Conta quante volte un ingrediente è escluso dai clienti nella lista_clienti*/
int contaEsclusioni(Cliente *lista_clienti, const char *ingrediente)
{
    int esclusioni = 0;
    Cliente *cliente;
    int i;
    /*Scorri la lista dei clienti*/
    for (cliente = lista_clienti; cliente != NULL; cliente = cliente->next)
    {
        /*Scorri le esclusioni di ogni cliente*/
        for (i = 0; i < cliente->nEsclusioni; i++)
        {
            /*Se l'ingrediente corrisponde a una delle esclusioni, incrementa il contatore*/
            if (strcmp(cliente->esclusi[i], ingrediente) == 0)
            {
                esclusioni++;
                break;
            }
        }
    }
    return esclusioni;
}

/*Copia un array di stringhe*/
char **copiaArrayStringhe(char **array, int n)
{
    int i;
    char **copia;
    /*Alloca memoria per l'array di copia*/
    copia = (char **)malloc(n * sizeof(char *));
    for (i = 0; i < n; i++)
    {
        /*Alloca memoria per ogni stringa nell'array di copia e copia il contenuto*/
        size_t len = strlen(array[i]);
        copia[i] = (char *)malloc((len + 1) * sizeof(char));
        strcpy(copia[i], array[i]);
    }
    return copia;
}

/*Copia una struttura Cliente*/
Cliente *copiaCliente(Cliente *cliente)
{
    Cliente *copia;
    copia = (Cliente *)malloc(sizeof(Cliente));
    /*Copia i valori degli attributi dalla struttura originale alla copia*/
    copia->id = cliente->id;
    strncpy(copia->nome, cliente->nome, N);
    copia->nRichieste = cliente->nRichieste;
    copia->richiesti = copiaArrayStringhe(cliente->richiesti, cliente->nRichieste);
    copia->nEsclusioni = cliente->nEsclusioni;
    copia->esclusi = copiaArrayStringhe(cliente->esclusi, cliente->nEsclusioni);
    copia->nGradimenti = cliente->nGradimenti;
    copia->graditi = copiaArrayStringhe(cliente->graditi, cliente->nGradimenti);
    copia->next = NULL;
    return copia;
}

/*Copia una lista di clienti*/
Cliente *copiaListaClienti(Cliente *lista_clienti)
{
    Cliente *copia_lista;
    Cliente *cursore_copia;
    Cliente *cursore_originale;
    if (lista_clienti == NULL)
    {
        return NULL;
    }

    /*Copia il primo cliente nella lista originale*/
    copia_lista = copiaCliente(lista_clienti);

        cursore_copia = copia_lista;
    cursore_originale = lista_clienti->next;

    while (cursore_originale != NULL)
    {
        /*Copia il cliente successivo nella lista originale*/
        cursore_copia->next = copiaCliente(cursore_originale);
        cursore_copia = cursore_copia->next;
        cursore_originale = cursore_originale->next;
    }
    return copia_lista;
}

/* Trova l'ingrediente con il minor numero di esclusioni tra i clienti*/
opinioniSuIngrediente *trovaIngredienteMenoEsclusioni(Cliente *lista_clienti, opinioniSuIngrediente *lista_ingredienti)
{
    opinioniSuIngrediente *ingrediente_min_esclusioni = NULL;
    int min_esclusioni = INT_MAX;
    opinioniSuIngrediente *ingrediente;
    int esclusioni;
    /* Scorri la lista degli ingredienti*/
    for (ingrediente = lista_ingredienti; ingrediente != NULL; ingrediente = ingrediente->next)
    {
        /* Conta il numero di esclusioni per l'ingrediente corrente*/
        esclusioni = contaEsclusioni(lista_clienti, ingrediente->ingrediente);
        /* Se il numero di esclusioni è inferiore al minimo attuale, aggiorna l'ingrediente minimo*/
        if (esclusioni < min_esclusioni)
        {
            ingrediente_min_esclusioni = ingrediente;
            min_esclusioni = esclusioni;
        }
    }
    return ingrediente_min_esclusioni;
}

/* Rimuove i clienti che escludono l'ingrediente specificato*/
void rimuoviClientiCheEscludonoIngrediente(Cliente **lista_clienti, opinioniSuIngrediente *ingrediente, int *num_clienti_insoddisfatti)
{
    Cliente *prev = NULL;
    Cliente *cliente = *lista_clienti;
    int i;
    Cliente *tmp;
    while (cliente != NULL)
    {
        bool esclude_ingrediente = false;

        for (i = 0; i < cliente->nEsclusioni; i++)
        {
            if (strcmp(cliente->esclusi[i], ingrediente->ingrediente) == 0)
            {
                esclude_ingrediente = true;
                break;
            }
        }

        if (esclude_ingrediente)
        {
            if (prev != NULL)
            {
                prev->next = cliente->next;
            }
            else
            {
                *lista_clienti = cliente->next;
            }

            (*num_clienti_insoddisfatti) -= 1;
            tmp = cliente;
            cliente = cliente->next;

            /* Deallocate memory for richiesti, esclusi, and graditi*/
            for (i = 0; i < tmp->nRichieste; i++)
            {
                free(tmp->richiesti[i]);
            }
            free(tmp->richiesti);

            for (i = 0; i < tmp->nEsclusioni; i++)
            {
                free(tmp->esclusi[i]);
            }
            free(tmp->esclusi);

            for (i = 0; i < tmp->nGradimenti; i++)
            {
                free(tmp->graditi[i]);
            }
            free(tmp->graditi);

            /* Free the memory for the Cliente struct*/
            free(tmp);
        }
        else
        {
            prev = cliente;
            cliente = cliente->next;
        }
    }
}

/*Valuta se un ingrediente è escluso da tutti o meno*/
bool ingredienteEsclusoDaTutti(opinioniSuIngrediente *ingrediente, Cliente *lista_clienti)
{
    bool escluso_da_tutti;
    bool escluso;
    int i;
    Cliente *cliente;
    escluso_da_tutti = true;
    for (cliente = lista_clienti; cliente != NULL; cliente = cliente->next)
    {
        escluso = false;

        for (i = 0; i < cliente->nEsclusioni; i++)
        {
            if (strcmp(cliente->esclusi[i], ingrediente->ingrediente) == 0)
            {
                escluso = true;
                break;
            }
        }

        if (!escluso)
        {
            escluso_da_tutti = false;
            break;
        }
    }

    return escluso_da_tutti;
}

/*Rimuove clienti soddisfatti da lista clienti e li aggiunge alla lista dei soddisfatti della pizza*/
void rimuoviClientiSoddisfatti(Cliente **head, Pizza *pizza, int *num_clienti)
{
    Cliente *prev = NULL;
    Cliente *current = *head;
    int j,k;
    bool presente;
    bool richiesti_presenti;
    bool esclusi_assenti;
    bool trovato;
    Cliente *temp;
    while (current != NULL)
    {
        richiesti_presenti = true;
        esclusi_assenti = true;

        for (j = 0; j < current->nRichieste; j++)
        {
            trovato = false;
            for (k = 0; k < pizza->nIngredienti; k++)
            {
                if (strcmp(current->richiesti[j], pizza->ingredienti[k]) == 0)
                {
                    trovato = true;
                    break;
                }
            }
            if (!trovato)
            {
                richiesti_presenti = false;
                break;
            }
        }

        if (richiesti_presenti)
        {
            for (j = 0; j < current->nEsclusioni; j++)
            {
                presente = false;
                for (k = 0; k < pizza->nIngredienti; k++)
                {
                    if (strcmp(current->esclusi[j], pizza->ingredienti[k]) == 0)
                    {
                        presente = true;
                        break;
                    }
                }
                if (presente)
                {
                    esclusi_assenti = false;
                    break;
                }
            }
        }

        if (richiesti_presenti && esclusi_assenti)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                (*num_clienti)--;
                prev->next = current->next;
            }
            temp = current;
            current = current->next;
            if (pizza->clienti_soddisfatti == NULL)
            {
                pizza->clienti_soddisfatti = malloc(100 * sizeof(char *));
            }
            pizza->clienti_soddisfatti[pizza->nClientiSoddisfatti] = malloc(100 * sizeof(char));
            strcpy(pizza->clienti_soddisfatti[pizza->nClientiSoddisfatti], temp->nome);
            pizza->nClientiSoddisfatti++;
            free(temp);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

/*Rimuove un ingrediente dalla lista degli ingredienti*/
void rimuoviIngredienteDaListaIngredienti(opinioniSuIngrediente **lista_ingredienti, opinioniSuIngrediente *ingrediente_da_rimuovere, int *num_ingredienti)
{
    opinioniSuIngrediente *prev;
    opinioniSuIngrediente *current;
    if (lista_ingredienti == NULL || *lista_ingredienti == NULL || ingrediente_da_rimuovere == NULL)
    {
        printf("ERROR");
        return;
    }

    prev = NULL;
    current = *lista_ingredienti;

    while (current != NULL)
    {
        if (strcmp((*current).ingrediente, (*ingrediente_da_rimuovere).ingrediente) == 0)
        {
            
            if (prev == NULL)
            {
                *lista_ingredienti = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            *num_ingredienti = *num_ingredienti - 1;
            break;
        }
        prev = current;
        current = current->next;
    }
}

/*Rimuove un ingrediente dalla lista degli ingredienti*/
opinioniSuIngrediente *creaListaIngredientiDaArray(opinioniSuIngrediente *array_ingredienti, int num_ingredienti)
{
    opinioniSuIngrediente *head;
    opinioniSuIngrediente *tail;
    int i;
    opinioniSuIngrediente *new_node;
    if (array_ingredienti == NULL || num_ingredienti <= 0)
    {
        return NULL;
    }

    head = NULL;
    tail = NULL;

    for (i = 0; i < num_ingredienti; i++)
    {
        new_node = malloc(sizeof(opinioniSuIngrediente));
        if (new_node == NULL)
        {
            return NULL;
        }

        *new_node = array_ingredienti[i];
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

/*Rimuove un ingrediente dalla lista degli ingredienti*/
Cliente *creaListaClientiDaArray(Cliente *array_clienti, int num_clienti)
{
    Cliente *head;
    Cliente *tail;
    Cliente *new_node;
    int i;
    if (array_clienti == NULL || num_clienti <= 0)
    {
        return NULL;
    }

    head = NULL;
    tail = NULL;

    for (i = 0; i < num_clienti; i++)
    {
        new_node = malloc(sizeof(Cliente));
        if (new_node == NULL)
        {
            return NULL;
        }

        *new_node = array_clienti[i];
        new_node->next = NULL;

        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return head;
}

/*Stampa gli ingredienti della pizza ordinati*/
void stampaPizza(Pizza *pizza)
{
    char **ingredienti_copia;
    int i;
    ingredienti_copia = copiaArrayStringhe(pizza->ingredienti, pizza->nIngredienti);

    mergesort(ingredienti_copia, pizza->nIngredienti, sizeof(char *), compare_strings);

    for (i = 0; i < pizza->nIngredienti; i++)
    {
        printf("%s ", ingredienti_copia[i]);
    }
    printf("\n");
    mergesort(pizza->clienti_soddisfatti, pizza->nClientiSoddisfatti, sizeof(char *), compare_strings);
    for (i = 0; i < pizza->nClientiSoddisfatti; i++)
    {
        printf("%s ", pizza->clienti_soddisfatti[i]);
    }
    printf("\n");
    for (i = 0; i < pizza->nIngredienti; i++)
    {
        free(ingredienti_copia[i]);
    }
    free(ingredienti_copia);
}

/*Costruisce e stampa il menu che soddisfa tutti i clienti*/
void buildMenu(Cliente *cliente, int num_clienti, int num_ingredienti, opinioniSuIngrediente opinioni_array[]) 
{
    Cliente *lista_clienti_insoddisfatti;
    opinioniSuIngrediente *lista_ingredienti;
    opinioniSuIngrediente *temp;
    int contatore_clienti_insoddisfatti;
    int contatore_pizze_menu;
    Cliente *lista_clienti_temporanea;
    int contatore_clienti_temporanea;
    Pizza *menu;
    bool pizza_finita;
    int num_ingredienti_temp;
    int num;
    int i;
    Pizza pizza;
    opinioniSuIngrediente ingrediente_meno_esclusioni;
    Cliente *cursore;
    lista_clienti_insoddisfatti = NULL;
    lista_ingredienti = NULL;
    mergesort(opinioni_array, num_ingredienti, sizeof(opinioniSuIngrediente), compareIngredientiAlf);

    lista_clienti_insoddisfatti = creaListaClientiDaArray(cliente, num_clienti);
    contatore_clienti_insoddisfatti = num_clienti;
    menu = (Pizza *)malloc(num_clienti * sizeof(Pizza));
    contatore_pizze_menu = 0;
    while (lista_clienti_insoddisfatti != NULL) {
        
        lista_clienti_temporanea = copiaListaClienti(lista_clienti_insoddisfatti);
        
        contatore_clienti_temporanea = contatore_clienti_insoddisfatti;
        pizza_finita = false;
        lista_ingredienti = creaListaIngredientiDaArray(opinioni_array, num_ingredienti);
        pizza = creaPizzaVuota();
        num_ingredienti_temp = num_ingredienti;
        while (!pizza_finita ) {
            
            
            ingrediente_meno_esclusioni = *trovaIngredienteMenoEsclusioni(lista_clienti_temporanea, lista_ingredienti);
            if (ingredienteEsclusoDaTutti(&ingrediente_meno_esclusioni, lista_clienti_temporanea)) {
                pizza_finita = true;
            } else {
                rimuoviClientiCheEscludonoIngrediente(&lista_clienti_temporanea, &ingrediente_meno_esclusioni, &contatore_clienti_temporanea);
                aggiungiIngredienteAPizza(&pizza, &ingrediente_meno_esclusioni);
                rimuoviIngredienteDaListaIngredienti(&lista_ingredienti, &ingrediente_meno_esclusioni, &num_ingredienti_temp);
            }
            if (lista_ingredienti == NULL) {
                pizza_finita = true;
            }
        }
        rimuoviClientiSoddisfatti(&lista_clienti_insoddisfatti, &pizza, &contatore_clienti_insoddisfatti);
        menu[contatore_pizze_menu] = pizza;
        fflush(stdout);
        contatore_pizze_menu++;
        cursore = lista_clienti_temporanea;
        num = 0;
        while (cursore != NULL) {
            num++;
            cursore = cursore->next;
        }
        while (lista_ingredienti != NULL) {
            temp = lista_ingredienti;
            lista_ingredienti = lista_ingredienti->next;
            free(temp);
        }
        distruggiListaClienti(lista_clienti_temporanea);
    }
    
    fflush(stdout);
    printf("%d pizze\n", contatore_pizze_menu);
    for (i = 0; i < contatore_pizze_menu; i++) {
        stampaPizza(&menu[i]);
    } 
    fflush(stdout);
    distruggiMenu(menu, contatore_pizze_menu);
    distruggiListaClienti(lista_clienti_insoddisfatti);

}
