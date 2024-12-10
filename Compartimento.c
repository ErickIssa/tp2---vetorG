#include "Compartimento.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarListaComp(ListaRochas* lista) {
    lista->tamanho = 0;
}


void insere_Rocha(ListaRochas* lista, float valor, float peso, int usada) {
    if (lista->tamanho >= MAX) {
        printf("Tamanho Max da lista\n");
        return;
    }
    RochaIndv novaRocha = {valor, peso, usada};
    lista->vetor[lista->tamanho] = novaRocha;
    lista->tamanho++;
    return;
}


void remove_Rocha(ListaRochas* lista, int indice) {
    if (indice < 0 || indice >= lista->tamanho) {
        printf("Sem rocha\n");
        return;
    }
    for (int i = indice; i < lista->tamanho - 1; i++) {
        lista->vetor[i] = lista->vetor[i + 1];
    }
    lista->tamanho--;
    return;
}

void ImprimeCompartimento(ListaRochas* lista) {
    if (lista->tamanho == 0) {
        printf("Vazia\n");
        return;
    }
    printf("Lista de Rochas:\n");
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Rocha Indice:%d  Valor: %.2f  Peso: %.2f\n", i, lista->vetor[i].valorRocha, lista->vetor[i].pesoRocha);
    }
}

float calcularValorAgregado(RochaIndv r) {
    return r.valorRocha / r.pesoRocha;
}

void ordenarIndicesPorValorAgregado(ListaRochas *lista, int indices[]) {
    for (int i = 0; i < lista->tamanho; i++) {
        indices[i] = i;
    }

    // ordena pela razao
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


float selecionarRochas(ListaRochas *lista, float limitePeso, int indicesSelecionados[], int *numSelecionados) {
    int indices[MAX];
    float pesoTotal = 0.0;
    float valorTotal = 0.0;

    *numSelecionados = 0;

    //ordenador de indice
    ordenarIndicesPorValorAgregado(lista, indices);

    // seleciona rochas por indice
    for (int i = 0; i < lista->tamanho; i++) {
        int idx = indices[i];
        if (pesoTotal + lista->vetor[idx].pesoRocha <= limitePeso) {
            pesoTotal += lista->vetor[idx].pesoRocha;
            valorTotal += lista->vetor[idx].valorRocha;
            lista->vetor[idx].usada = 0;
            indicesSelecionados[*numSelecionados] = idx; //poe no ponteiro pq eu n posso atribuir vetor as rochas selecionadas
            (*numSelecionados)++;
        }
    }

    return valorTotal;
}
