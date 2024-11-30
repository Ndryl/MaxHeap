#ifndef METODOS_H
#define METODOS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Aviao{
    char identificador[100];
    double Combustivel;
    int tipo;
    int emergencia;
    double prioridade;
    int previsao;

};
typedef struct Aviao Aviao;
typedef struct{
    Aviao* data;
    int capacity;
    int size;

}heap;

Aviao contructorAeronave(char identificador[100], double Combustivel, int tipo, int emergencia, int previsao);
void informacaoAeronave(Aviao aeronave);
Aviao getAviao(Aviao* aeronaves, int indice);
heap* criaHeap(int capacity, Aviao* aeronaves);
void insertHelper(heap* h, int index);
void insert(heap* h, Aviao data);
void deleteNode(heap* h);
void atualizaPrioridade(heap*h, char identificador[100]);
void maxHeapify(heap* h, int index);
void carregar_voos(heap* h, char nome_arquivo[500]);
void remover_quebra_linha(char* str);
void removeAeronave(heap* h, char identificador[100]);
void findAeronave(heap* h, char identificador[100]);


#endif