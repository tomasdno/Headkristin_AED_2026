#ifndef HEALKRISTIN_H
#define HEALKRISTIN_H

#include <stdio.h>
#include "Unionfind.h"

typedef struct No {
    int city;
    struct No *next;
} No;

// Aresta candidata/escolhida: a < b, d2 = distancia euclidiana ao quadrado
typedef struct {
    int a;
    int b;
    long long d2;
} Edge;

int extensaoexists(char *filename, char *extensao);

void freeGrafo(No **grafo, int C);

void uffrees(UnionFind uf);

void fcloses(FILE *questsFILE, FILE *positionFILE, FILE *mapFILE);

void doTask1(UnionFind *uf,
             FILE *resultsFILE,
             int *firstOutput);

void doTask2(UnionFind *uf,
             int C,
             FILE *resultsFILE,
             int *firstOutput);
void doTask3(UnionFind *uf,
             int *X,
             int *Y,
             int C,
             int city,
             FILE *resultsFILE,
             int *firstOutput);
void doTask4(UnionFind *uf,
             int *X,
             int *Y,
             int C,
             int city,
             FILE *resultsFILE,
             int *firstOutput);

Edge *calcularMST(UnionFind *uf, int *X, int *Y, int C, int *nEdges);

void doTask5(UnionFind *uf,
             int *X,
             int *Y,
             int C,
             FILE *resultsFILE,
             int *firstOutput);

#endif