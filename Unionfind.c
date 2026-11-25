 luis
#include <stdlib.h>
#include "Unionfind.h"

int findroot(UnionFind *uf, int city) {
    int root = city;

    while (root != uf->parent[root]) {
        root = uf->parent[root];
    }

    while (city != uf ->parent[city]) {
        int next = uf->parent[city];
        uf->parent[city] = root;
        city = next;
    }
    return root;
}

void unionCities(UnionFind *uf, int city1, int city2) {
    int raiz1 = findroot(uf, city1);
    int raiz2 = findroot(uf, city2);

    if (raiz1 == raiz2) {
        return;
    }

    if (uf->size[raiz1] < uf->size[raiz2]) {

        uf->parent[raiz1] = raiz2;
        uf->size[raiz2] += uf->size[raiz1];
    } else {

        uf->parent[raiz2] = raiz1;
        uf->size[raiz1] += uf->size[raiz2];
    }
    uf->count--;

#include <stdlib.h>
#include "Unionfind.h"

int findroot(UnionFind *uf, int city) {
    int root = city;

    while (root != uf->parent[root]) {
        root = uf->parent[root];
    }

    while (city != uf ->parent[city]) {
        int next = uf->parent[city];
        uf->parent[city] = root;
        city = next;
    }
    return root;
}

void unionCities(UnionFind *uf, int city1, int city2) {
    int raiz1 = findroot(uf, city1);
    int raiz2 = findroot(uf, city2);

    if (raiz1 == raiz2) {
        return;
    }

    if (uf->size[raiz1] < uf->size[raiz2]) {

        uf->parent[raiz1] = raiz2;
        uf->size[raiz2] += uf->size[raiz1];
    } else {

        uf->parent[raiz2] = raiz1;
        uf->size[raiz1] += uf->size[raiz2];
    }
    uf->count--;
 main
}   