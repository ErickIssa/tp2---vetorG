#include <stdio.h>
#include <stdlib.h>
#include "ListaSondas.h"
#include <time.h>

int minhaVariavelGlobal = 1;

int main(){

    clock_t inicio = clock();
    SondaMarte sonda1;
    listaSonda sondasL;
    ListaRochas compartimentoL;
    
    inicializarListaComp(&compartimentoL);
    iniciaListaSonda(&sondasL);

    for(int i = 0;i < 3;i++){
        insereSonda(&sondasL, inicializaSonda(&sonda1));
    }

    ImprimeListaSondas(&sondasL);
    FILE *arq = NULL;
    arq = fopen("testerocha.txt", "r");
    if(arq == NULL){
        printf("falha leitura");
        exit(0);
    }
    int nRochas; 
    float peso, valor;
    fscanf(arq, "%d", &nRochas);

    for(int i = 0; i<nRochas;i++){
        fscanf(arq,"%f %f", &peso, &valor);
        insere_Rocha(&compartimentoL, valor, peso, 0);
    }
    ImprimeCompartimento(&compartimentoL);

    int indicesSelecionados[MAX];
    int numSelecionados = 0;

    selecionarRochas(&compartimentoL, 10000, indicesSelecionados, &numSelecionados);
    for (int i = 0; i < numSelecionados; i++) {
        int idx = indicesSelecionados[i];
        printf("Índice: %d, Valor: %.2f, Peso: %.2f\n", idx, compartimentoL.vetor[idx].valorRocha, compartimentoL.vetor[idx].pesoRocha);
    }
    int pesoDivisor = 40;
    int contpeso = 0;
    
    for(int p = 0;p < 3;p++){
        for (int i = 0; i < numSelecionados; i++) {
            int idx = indicesSelecionados[i];
            if(contpeso + compartimentoL.vetor[idx].pesoRocha <= pesoDivisor && compartimentoL.vetor[idx].usada == 0){
                printf("Rocha separada: %d, Valor: %.2f, Peso: %.2f\n", idx, compartimentoL.vetor[idx].valorRocha, compartimentoL.vetor[idx].pesoRocha);
                contpeso = contpeso + compartimentoL.vetor[idx].pesoRocha;
                compartimentoL.vetor[idx].usada = 1;
            }
        }
    contpeso = 0;
    printf("\n");
    }

    

    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio);
    printf("Tempo gasto: %f segundos\n", tempo_decorrido);
    printf("\n"); 


    return 0;
}