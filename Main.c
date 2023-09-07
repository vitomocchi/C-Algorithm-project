#include "header.h"
#define struct Cliente Cliente

int main(int argc, char *argv[]) {
    /*Dichiarazione di variabili char*/
    char ingredienti_file[256],clienti_file[256];
    /*Dichiarazione di variabili int*/
    int num_ingredienti, num_clienti, *gruppo, gruppoSize,**matrice_adiacenza, *frequenze_esclusioni;
   /*Dichiarazione di file*/
    FILE *fp1, *fp2;
    /*Dichiarazione di Struct*/
    Cliente *cliente;
   
    opinioniSuIngrediente *opinioni_array;
    
    InterpretaLineaComando(argc, argv, ingredienti_file, clienti_file);
    fp1 = fopen(ingredienti_file, "r");
    if (fp1 == NULL) {
        perror("Errore nell'apertura dei file dell'ingredienti");
        return 1;
    }
    fscanf(fp1, "%d", &num_ingredienti);
    /*Allocazione di memoria*/
    opinioni_array = (opinioniSuIngrediente *)malloc(num_ingredienti * sizeof(opinioniSuIngrediente));
    
    inizializza_opinioni(opinioni_array, num_ingredienti, fp1);
    fclose(fp1);
    fp2 = fopen(clienti_file, "r");
    if (fp2 == NULL) {
        perror("Errore nell'apertura dei file dei clienti");
        return 1;
    }
    fscanf(fp2, "%d", &num_clienti);
    
    frequenze_esclusioni = (int *)malloc((num_clienti + 1) * sizeof(int));
    /*Allocazione di memoria*/
    cliente = (Cliente *)calloc(num_clienti, sizeof(Cliente));
    
    inizializza_clienti(cliente, num_clienti, num_ingredienti, fp2, opinioni_array);
    /*Chiusura del secondo file*/
    fclose(fp2);
    
    stampa_opinioni(opinioni_array, num_ingredienti);
    
    stampa_clienti(cliente, num_clienti);
    
    frequenza_esclusioni(opinioni_array, num_ingredienti, frequenze_esclusioni, num_clienti);
    
    stampa_frequenze_esclusioni(frequenze_esclusioni, num_clienti);

    matrice_adiacenza = calcolaMatriceAdiacenza(cliente, num_clienti);
    
    stampaMatriceAdiacenza(matrice_adiacenza, num_clienti, cliente);
    
    gruppo = trovaGruppoIncompatibili(num_clienti, matrice_adiacenza, &gruppoSize);
    
    stampa_nomi_incompatibili(cliente, num_clienti, matrice_adiacenza);
    
    buildMenu(cliente, num_clienti, num_ingredienti, opinioni_array);
    /*Libera memoria*/
    free_memory(cliente, num_clienti, num_ingredienti, matrice_adiacenza, gruppo, frequenze_esclusioni, opinioni_array);
    
    return 0;
}


