#include <stdio.h>
#include <stdlib.h>
#include "ListaSondas.h"
#include <time.h>

int minhaVariavelGlobal = 1;

float calcularValorAgregado(RochaIndv r) {
    return r.valorRocha / r.pesoRocha;
}

// Função para ordenar os índices por valor agregado (ordem decrescente)
void ordenarIndicesPorValorAgregado(ListaRochas *lista, int indices[]) {
    // Inicializa os índices com suas posições originais
    for (int i = 0; i < lista->tamanho; i++) {
        indices[i] = i;
    }

    // Ordena os índices com base no valor agregado correspondente
    for (int i = 0; i < lista->tamanho - 1; i++) {
        for (int j = 0; j < lista->tamanho - i - 1; j++) {
            if (calcularValorAgregado(lista->vetor[indices[j]]) < calcularValorAgregado(lista->vetor[indices[j + 1]])) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}

// Função para selecionar as melhores rochas dado um limite de peso
float selecionarRochas(ListaRochas *lista, float limitePeso, int indicesSelecionados[], int *numSelecionados) {
    int indices[MAX];
    float pesoTotal = 0.0;
    float valorTotal = 0.0;

    // Inicializa o contador de selecionados
    *numSelecionados = 0;

    // Ordena os índices com base no valor agregado
    ordenarIndicesPorValorAgregado(lista, indices);

    // Seleciona as rochas com base na ordenação dos índices
    for (int i = 0; i < lista->tamanho; i++) {
        int idx = indices[i];
        if (pesoTotal + lista->vetor[idx].pesoRocha <= limitePeso) {
            pesoTotal += lista->vetor[idx].pesoRocha;
            valorTotal += lista->vetor[idx].valorRocha;
            lista->vetor[idx].usada = 1; // Marca a rocha como usada
            indicesSelecionados[*numSelecionados] = idx; // Armazena o índice da rocha selecionada
            (*numSelecionados)++;
        }
    }

    return valorTotal;
}

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

     float limitePeso = 40.0;
    int indicesSelecionados[MAX];
    int numSelecionados = 0;

    selecionarRochas(&compartimentoL, limitePeso, indicesSelecionados, &numSelecionados);
    for (int i = 0; i < numSelecionados; i++) {
        int idx = indicesSelecionados[i];
        printf("Índice: %d, Valor: %.2f, Peso: %.2f\n", idx, compartimentoL.vetor[idx].valorRocha, compartimentoL.vetor[idx].pesoRocha);
    }

    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio);
    printf("Tempo gasto: %f segundos\n", tempo_decorrido);
    printf("\n"); 


    return 0;
}