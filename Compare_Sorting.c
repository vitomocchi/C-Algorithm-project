#include "header.h"
/*Confronta le opinioni su ingrediente per popolarità*/
int compare_opinioni(const opinioniSuIngrediente *a, const opinioniSuIngrediente *b)
{
    if (a->nEsclusioni != b->nEsclusioni)
        return a->nEsclusioni - b->nEsclusioni;
    if (a->nRichieste != b->nRichieste)
        return b->nRichieste - a->nRichieste;
    if (a->nGradimenti != b->nGradimenti)
        return b->nGradimenti - a->nGradimenti;
    return strcmp(a->ingrediente, b->ingrediente);
}

/*Esegue merge su due sotto-array ordinati di un array di tipo opinioniSuIngrediente*/
void merge_opinioni(opinioniSuIngrediente *arr, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    opinioniSuIngrediente *L = (opinioniSuIngrediente *)malloc(n1 * sizeof(opinioniSuIngrediente));
    opinioniSuIngrediente *R = (opinioniSuIngrediente *)malloc(n2 * sizeof(opinioniSuIngrediente));

    memcpy(L, &arr[left], n1 * sizeof(opinioniSuIngrediente));
    memcpy(R, &arr[mid + 1], n2 * sizeof(opinioniSuIngrediente));

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (compare_opinioni(&L[i], &R[j]) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/*Implementa mergesort per un array di opinioniSuIngrediente*/
void mergesort_opinioni(opinioniSuIngrediente *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergesort_opinioni(arr, left, mid);
        mergesort_opinioni(arr, mid + 1, right);

        merge_opinioni(arr, left, mid, right);
    }
}

/*Confronta i clienti per numero di vincoli forti*/
int cmp_clienti(const void *a, const void *b)
{
    int vincoli_forti_a;
    int vincoli_forti_b;
    Cliente *cliente_a;
    Cliente *cliente_b;
    cliente_a = (Cliente *)a;
    cliente_b = (Cliente *)b;
    vincoli_forti_a = cliente_a->nRichieste + cliente_a->nEsclusioni;
    vincoli_forti_b = cliente_b->nRichieste + cliente_b->nEsclusioni;
    if (vincoli_forti_a != vincoli_forti_b)
    {
        return vincoli_forti_a - vincoli_forti_b;
    }

    if (cliente_a->nGradimenti != cliente_b->nGradimenti)
    {
        return cliente_a->nGradimenti - cliente_b->nGradimenti;
    }

    return strcmp(cliente_a->nome, cliente_b->nome);
}

/*Esegue merge su due sotto-array ordinati di un array di tipo Cliente*/
void merge_clienti(Cliente *clienti, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    Cliente *L = (Cliente *) malloc(n1 * sizeof(Cliente));
    Cliente *R = (Cliente *) malloc(n2 * sizeof(Cliente));



    for (i = 0; i < n1; i++)
        L[i] = clienti[low + i];
    for (j = 0; j < n2; j++)
        R[j] = clienti[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;
    while (i < n1 && j < n2) {
        if (cmp_clienti(&L[i], &R[j]) <= 0) {
            clienti[k] = L[i];
            i++;
        } else {
            clienti[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        clienti[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        clienti[k] = R[j];
        j++;
        k++;
    }
    free(L);
free(R);
}

/*Implementa mergesort per un array di Cliente*/
void mergesort_clienti(Cliente *clienti, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergesort_clienti(clienti, low, mid);
        mergesort_clienti(clienti, mid + 1, high);

        merge_clienti(clienti, low, mid, high);
    }
}

/*Esegue l'operazione di merge su due sotto-array ordinati di un array generico*/
void merge(void *dest, void *src1, int num1, void *src2, int num2, size_t size, int (*cmpfun)(const void *, const void *))
{
    int i = 0, j = 0, k = 0;
    char *cdest = (char *)dest;
    char *csrc1 = (char *)src1;
    char *csrc2 = (char *)src2;

    while (i < num1 && j < num2)
    {
        if (cmpfun(csrc1 + i * size, csrc2 + j * size) <= 0)
        {
            memcpy(cdest + k * size, csrc1 + i * size, size);
            i++;
        }
        else
        {
            memcpy(cdest + k * size, csrc2 + j * size, size);
            j++;
        }
        k++;
    }
    while (i < num1)
    {
        memcpy(cdest + k * size, csrc1 + i * size, size);
        i++;
        k++;
    }
    while (j < num2)
    {
        memcpy(cdest + k * size, csrc2 + j * size, size);
        j++;
        k++;
    }
}

/*Esegue il merge sort ricorsivamente su un array generico. */
void sort_helper(void *dst, void *src, int num, size_t size, int (*cmpfun)(const void *, const void *))
{
    if (num > 1)
    {
        int half = num / 2;
        char *csrc = (char *)src;
        char *cdst = (char *)dst;

        sort_helper(csrc, cdst, half, size, cmpfun);
        sort_helper(csrc + half * size, cdst + half * size, num - half, size, cmpfun);
        merge(cdst, csrc, half, csrc + half * size, num - half, size, cmpfun);
    }
}

/*Confronta i clienti per nome*/
int compareClienti(const void *a, const void *b)
{
    Cliente *clienteA;
    Cliente *clienteB;
    clienteA = (Cliente *)a;
    clienteB = (Cliente *)b;
    return strcmp(clienteA->nome, clienteB->nome);
}

/*mplementa l'algoritmo di ordinamento merge sort per un array generico*/
void mergesort(void *arr, int num, size_t size, int (*cmpfun)(const void *, const void *))
{
    if (num > 1)
    {
        void *tmp = malloc(num * size);
        if (tmp != NULL)
        {
            memcpy(tmp, arr, num * size);
            sort_helper(arr, tmp, num, size, cmpfun);
            free(tmp);
        }
        else
        {
            fprintf(stderr, "Error: Memory allocation failed in mergesort.\n");
            return;
        }
    }
}

/*Confronta nomi*/
int compareNomiClienti(const void *a, const void *b)
{
    
    char *nomeA;
    char *nomeB;
    nomeA = *(char **)a;
    nomeB = *(char **)b;
    return strcmp(nomeA, nomeB);
}

/*Confronta opinioniSuIngrediente in base al loro ingrediente*/
int compareIngredientiAlf(const void *a, const void *b)
{
    opinioniSuIngrediente *ingrediente_a;
    opinioniSuIngrediente *ingrediente_b;
    ingrediente_a = (opinioniSuIngrediente *)a;
    ingrediente_b = (opinioniSuIngrediente *)b;
    return strcmp(ingrediente_a->ingrediente, ingrediente_b->ingrediente);
}

/*Confronta stringhe*/
int compare_strings(const void *a, const void *b)
{
    const char **aa;
    const char **bb;
    aa = (const char **)a;
    bb = (const char **)b;
    return strcmp(*aa, *bb);
}
