#ifndef UNIONFIND_H
#define UNIONFIND_H

typedef struct {
    int *parent;
    int *size;
    int count;
} UnionFind;

int findroot(UnionFind *uf, int city);

void unionCities(UnionFind *uf, int city1, int city2);

#endif