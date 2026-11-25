luis
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "Unionfind.h"
#include "Healkristin.h"

int extensaoexists(char *filename,  char*extensao){
    int lenfilename = strlen(filename);
    int lenextensao = strlen(extensao);
    if(lenfilename < lenextensao){
        return 0;
    }
    return strcmp(filename + lenfilename - lenextensao, extensao) == 0; 
}

int linkcompare (const void *a, const void *b) {
    const Ligacao *linkA = (const Ligacao *)a;
    const Ligacao *linkB = (const Ligacao *)b;

    if (linkA->dist2 < linkB->dist2) {
        return -1;
    } else if (linkA->dist2 > linkB->dist2) {
        return 1;
    } else {
        return 0;
    }
}

void freeGrafo(No **grafo, int C) {
    for (int i = 1; i <= C; i++) {
        No *atual = grafo[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->next;
            free(temp);
        }
    }
    free(grafo);
}

void uffrees(UnionFind uf){
    free(uf.parent);
    free(uf.size);
}
void fcloses(FILE *questsFILE, FILE *positionFILE, FILE *mapFILE){
    fclose(questsFILE);
    fclose(mapFILE);
    fclose(positionFILE);
}

void doTask1(UnionFind *uf, FILE *resultsFILE, int *firstOutput){

    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    fprintf(resultsFILE, "Task1 %d\n", uf->count);
    *firstOutput = 0;
}

void doTask2(UnionFind *uf, int C, FILE *resultsFILE, int* firstOutput) {

    int *task2_root=calloc(C + 1, sizeof(int));

    if (task2_root == NULL) {
        return;
    }

    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    fprintf(resultsFILE, "Task2 %d\n", uf->count);
    *firstOutput = 0;

    for(int i = 1; i <= C; i++) {
        int root = findroot(uf, i);

        if(task2_root[root] == 0){
            fprintf(resultsFILE, "Cluster:");

                for(int j = 1; j <= C; j++) {
                    if(findroot(uf, j) == root){
                        fprintf(resultsFILE, " %d", j);
                    }
                }
            fprintf(resultsFILE, "\n");

            task2_root[root] = 1; // Aqui assinalo final da lista
        }
    }  

    free(task2_root);
}

void doTask3(UnionFind *uf, int *X, int *Y, int C, int city, FILE *resultsFILE, int* firstOutput) {
    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    *firstOutput = 0;

    if(city < 1 || city > C || uf->count == 1){
        fprintf(resultsFILE, "Task3 %d -2\n", city);
        return;
    }

    int rootcity = findroot(uf, city);
    int bestroot = -1;
    long long bestdistance = -1;

    for(int i=1; i <= C; i++){

        if (i == city) {
            continue;
        }
        if(findroot(uf, i) == rootcity){
            continue;
        }
        long long distanceX = (long long)(X[city] - X[i]);
        long long distanceY = (long long)(Y[city] - Y[i]);

        long long distance = (distanceX * distanceX + distanceY * distanceY);

        if(bestdistance < 0 || distance < bestdistance || (distance == bestdistance && i < bestroot)){
            bestdistance = distance;
            bestroot = i;
        }
    }
    fprintf(resultsFILE, "Task3 %d %d\n", city, bestroot);
}

void doTask4 (UnionFind *uf, int *X, int *Y, int C, int city, FILE *resultsFILE, int *FisrtOutput) {
    if(!*FisrtOutput){
        fprintf(resultsFILE, "\n");
    }
    *FisrtOutput = 0;

    if(city < 1 || city > C || uf->count == 1){
        fprintf(resultsFILE, "Task4 %d -2\n", city);
        return;

    }

    int rootcity = findroot(uf, city);
    int *roots = malloc((C + 1) * sizeof(int));
    if (roots == NULL) {
        fprintf(resultsFILE, "Task4 %d -2\n", city);
        return;
    }

    for (int i = 1; i <= C; i++) {
        roots[i] = findroot(uf, i);
    }

    long long bestdistance = -1;
    int bestroot = -1;

    for (int i = 1; i <=C; i++){

        if(roots[i] != rootcity){
            continue;
        }
        for(int j = 1; j <= C; j++){
            if(roots[j] == rootcity){
                continue;

            }
            long long distanceX = (long long)(X[i] - X[j]);
            long long distanceY = (long long)(Y[i] - Y[j]);
            long long distance = (distanceX * distanceX + distanceY * distanceY);
            if(bestdistance < 0 || distance < bestdistance || (distance == bestdistance && j < bestroot)){
                bestdistance = distance;
                bestroot = j;

            }

        }
    }
    free(roots);
    fprintf(resultsFILE, "Task4 %d %d\n", city, bestroot);    
}

void doTask5(UnionFind *uf, int *X, int *Y, int C, FILE *resultsFILE, int *firstOutput) {
    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    int ligacoespossiveis = C * (C - 1) / 2;

    Ligacao *candidatas = malloc(ligacoespossiveis * sizeof(Ligacao));
    Ligacao *escolhidas = malloc( C * sizeof(Ligacao));
    UnionFind tempUF;

    tempUF.parent = malloc((C + 1) * sizeof(int));
    tempUF.size = malloc((C + 1) * sizeof(int));

    if (candidatas == NULL || escolhidas == NULL || tempUF.parent == NULL || tempUF.size == NULL) {
        free(candidatas);
        free(escolhidas);
        free(tempUF.parent);
        free(tempUF.size);
        return;
    }

    for (int i = 1; i <= C; i++) {
        tempUF.parent[i] = uf->parent[i];
        tempUF.size[i] = uf->size[i];
    }

    int numcandidatas = 0;
    for(int i = 1; i <= C; i++) {
        int rootA = findroot(&tempUF, i);
        for(int j = i + 1; j <= C; j++) {
            int rootB = findroot(&tempUF, j);
            if(rootA != rootB) {
                long long distanceX = (long long)(X[i] - X[j]);
                long long distanceY = (long long)(Y[i] - Y[j]);
                long long dist2 = distanceX * distanceX + distanceY * distanceY;

                candidatas[numcandidatas].city1 = i;
                candidatas[numcandidatas].city2 = j;
                candidatas[numcandidatas].dist2 = dist2;
                numcandidatas++;
            }
        }
    }
    qsort(candidatas, numcandidatas, sizeof(Ligacao), linkcompare);
}


int main(int argc, char *argv[]){
     //-------Invocação:1.2------//
    if(argc != 4){
        return 0;
    }
    
    if (!extensaoexists(argv[1], ".quests") || 
        !extensaoexists(argv[2], ".map") || 
        !extensaoexists(argv[3], ".position")){

        return 0;
    }

    FILE *questsFILE = fopen(argv[1], "r");
    if(questsFILE == NULL){
        return 0;
    }
    FILE *mapFILE = fopen(argv[2], "r");
    if(mapFILE == NULL){
        fclose(questsFILE);
        return 0;
    }
    FILE *positionFILE = fopen(argv[3], "r");
    if(positionFILE == NULL){
        fclose(questsFILE);
        fclose(mapFILE);
        return 0;
    }
    //-------FIM 1.2------//

    //-------ler cabeçalho  2.2 1)------//
    int C; //nmr de cidades
    int L; //nmr de ligações


    if (fscanf(mapFILE, "%d %d", &C, &L) != 2) {
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    if(C<1 || L<0){
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }
    //-------FIM cabeçalho  2.2 1)------//

    //-------task1----------------------//
    UnionFind uf;
    uf.parent = malloc((C + 1) * sizeof(int));
    uf.size = malloc((C + 1) * sizeof(int));

    if (uf.parent == NULL || uf.size == NULL) {
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }
    uf.count = C;
    for (int i = 1; i <= C; i++) {
        uf.parent[i] = i;
        uf.size[i] = 1;
    }



    No**grafo=calloc(C + 1, sizeof(No*));
    if (grafo == NULL) {
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }  
    //-------FIM task1----------------------//

    //-------pares de cidades  2.2 2)------//
    for(int i = 0; i < L; i++) {
        int city1, city2;
        if (fscanf(mapFILE, "%d %d", &city1, &city2) != 2) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(city1 < 1 || city1 > C || city2 < 1 || city2 > C){
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        unionCities(&uf, city1, city2);

        No*novo1=malloc(sizeof(No));
        if (novo1 == NULL) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        novo1->city=city2;
        novo1->next=grafo[city1];
        grafo[city1]=novo1;

        No*novo2=malloc(sizeof(No));
        if (novo2 == NULL) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        novo2->city=city1;
        novo2->next=grafo[city2];
        grafo[city2]=novo2;
    }
    //-------FIM pares de cidades  2.2 2)------//

    //-------Ficheiro position: 2.3------//
    int Xmax, Ymax;
    if (fscanf(positionFILE, "%d %d", &Xmax, &Ymax) != 2) {
        freeGrafo(grafo, C);

        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    if (Ymax < 1 || Xmax < 1) {
        freeGrafo(grafo, C);

        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    int *X=calloc(C + 1, sizeof(int));
    int *Y=calloc(C + 1, sizeof(int));
    int *seen=calloc(C + 1, sizeof(int));

    if (X == NULL || Y == NULL || seen == NULL) {
        freeGrafo(grafo, C);
        free(X);
        free(Y);
        free(seen);
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    for(int i=0; i<C; i++){
        int id, x, y;
    
        if (fscanf(positionFILE, "%d %d %d", &id, &x, &y) != 3) {
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(id < 1 || id > C){
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(x < 1 || x > Xmax || y < 1 || y > Ymax){
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if (seen[id] == 1) {
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        X[id] = x;
        Y[id] = y;
        seen[id] = 1;
    }     
//-------FIM Ficheiro position: 2.3------//

//-------Ficheiro results------//
int lenQuests = strlen(argv[1]);
int lenExtQuests = strlen(".quests");
int lenExtResults = strlen(".results");

char *resultsName = malloc(
    (lenQuests - lenExtQuests + lenExtResults + 1) * sizeof(char)
);

if (resultsName == NULL) {
    free(X);
    free(Y);
    free(seen);

    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);

    return 0;
}

strcpy(resultsName, argv[1]);
resultsName[lenQuests - lenExtQuests] = '\0';
strcat(resultsName, ".results");

FILE *resultsFILE = fopen(resultsName, "w");

if (resultsFILE == NULL) {
    free(resultsName);
    free(X);
    free(Y);
    free(seen);
    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);

    return 0;
}

int firstOutput = 1;
//-------FIM Ficheiro results------//

//-------Ficheiro quests: 2.1------//
    char linha[100];

    while(fgets(linha, sizeof(linha), questsFILE) != NULL){
        char task[20];
        int city;

        int n = sscanf(linha, "%19s %d", task, &city);
        if (n < 1) {
            continue;
        }

        if (strcmp(task, "Task1")==0) {
            if (n != 1) {
                continue;
            }
            doTask1(&uf, resultsFILE, &firstOutput);
        }
        else if (strcmp(task, "Task2")==0) {
            if (n != 1) {
                continue;
            }
        //-----Task2 3.2-----//
         doTask2(&uf, C, resultsFILE, &firstOutput);  //função do Task2
        //-----Fim Task2: 3.2-----//
        }
        else if (strcmp(task, "Task3")==0) {
            if (n != 2) {
                continue;
            }   
        //-----Task3 3.3-----// 
         doTask3(&uf, X, Y, C, city, resultsFILE, &firstOutput);  //função do Task3
        //-----Fim Task3: 3.3-----//

        }
        else if (strcmp(task, "Task4")==0) {
            if (n != 2) {
                continue;
            }
            //-----Task4 3.4-----//
            doTask4(&uf, X, Y, C, city, resultsFILE, &firstOutput);  //função do Task4
           //-----Fim Task2: 3.4-----//
        
        }
        else if(strcmp(task,"Task5")==0){
            if(n!=1){
                continue;
            }
            //-----Task5 3.5-----//
            doTask5(&uf, X, Y, C, resultsFILE, &firstOutput);  //função do Task5
           //-----Fim Task5: 3.5-----// 
        }
        else if(strcmp(task,"Task6")==0){
            if(n!=2){
                continue;
            }
            //-----Task6 3.6-----//
            doTask6(&uf, X, Y, C, city, resultsFILE, &firstOutput);  //função do Task6
           //-----Fim Task6: 3.6-----// 
        }
        else {
        }


    }
//-------FIM 2.1------//
    free(X);
    free(Y);
    free(seen);

    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);
    fclose(resultsFILE);

    free(resultsName);

    return 0;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "Unionfind.h"
#include "Healkristin.h"

int extensaoexists(char *filename,  char*extensao){
    int lenfilename = strlen(filename);
    int lenextensao = strlen(extensao);
    if(lenfilename < lenextensao){
        return 0;
    }
    return strcmp(filename + lenfilename - lenextensao, extensao) == 0; 
}

void freeGrafo(No **grafo, int C) {
    for (int i = 1; i <= C; i++) {
        No *atual = grafo[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->next;
            free(temp);
        }
    }
    free(grafo);
}

void uffrees(UnionFind uf){
    free(uf.parent);
    free(uf.size);
}
void fcloses(FILE *questsFILE, FILE *positionFILE, FILE *mapFILE){
    fclose(questsFILE);
    fclose(mapFILE);
    fclose(positionFILE);
}

void doTask1(UnionFind *uf, FILE *resultsFILE, int *firstOutput){

    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    fprintf(resultsFILE, "Task1 %d\n", uf->count);
    *firstOutput = 0;
}

void doTask2(UnionFind *uf, int C, FILE *resultsFILE, int* firstOutput) {

    int *task2_root=calloc(C + 1, sizeof(int));

    if (task2_root == NULL) {
        return;
    }

    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    fprintf(resultsFILE, "Task2 %d\n", uf->count);
    *firstOutput = 0;

    for(int i = 1; i <= C; i++) {
        int root = findroot(uf, i);

        if(task2_root[root] == 0){
            fprintf(resultsFILE, "Cluster:");

                for(int j = 1; j <= C; j++) {
                    if(findroot(uf, j) == root){
                        fprintf(resultsFILE, " %d", j);
                    }
                }
            fprintf(resultsFILE, "\n");

            task2_root[root] = 1; // Aqui assinalo final da lista
        }
    }  

    free(task2_root);
}

void doTask3(UnionFind *uf, int *X, int *Y, int C, int city, FILE *resultsFILE, int* firstOutput) {
    if(!*firstOutput){
        fprintf(resultsFILE, "\n");
    }
    *firstOutput = 0;

    if(city < 1 || city > C || uf->count == 1){
        fprintf(resultsFILE, "Task3 %d -2\n", city);
        return;
    }

    int rootcity = findroot(uf, city);
    int bestroot = -1;
    long long bestdistance = -1;

    for(int i=1; i <= C; i++){

        if (i == city) {
            continue;
        }
        if(findroot(uf, i) == rootcity){
            continue;
        }
        long long distanceX = (long long)(X[city] - X[i]);
        long long distanceY = (long long)(Y[city] - Y[i]);

        long long distance = (distanceX * distanceX + distanceY * distanceY);

        if(bestdistance < 0 || distance < bestdistance || (distance == bestdistance && i < bestroot)){
            bestdistance = distance;
            bestroot = i;
        }
    }
    fprintf(resultsFILE, "Task3 %d %d\n", city, bestroot);
}

void doTask4 (UnionFind *uf, int *X, int *Y, int C, int city, FILE *resultsFILE, int *FisrtOutput) {
    if(!*FisrtOutput){
        fprintf(resultsFILE, "\n");
    }
    *FisrtOutput = 0;

    if(city < 1 || city > C || uf->count == 1){
        fprintf(resultsFILE, "Task4 %d -2\n", city);
        return;

    }

    int rootcity = findroot(uf, city);
    int *roots = malloc((C + 1) * sizeof(int));
    if (roots == NULL) {
        fprintf(resultsFILE, "Task4 %d -2\n", city);
        return;
    }

    for (int i = 1; i <= C; i++) {
        roots[i] = findroot(uf, i);
    }

    long long bestdistance = -1;
    int bestroot = -1;

    for (int i = 1; i <=C; i++){

        if(roots[i] != rootcity){
            continue;
        }
        for(int j = 1; j <= C; j++){
            if(roots[j] == rootcity){
                continue;

            }
            long long distanceX = (long long)(X[i] - X[j]);
            long long distanceY = (long long)(Y[i] - Y[j]);
            long long distance = (distanceX * distanceX + distanceY * distanceY);
            if(bestdistance < 0 || distance < bestdistance || (distance == bestdistance && j < bestroot)){
                bestdistance = distance;
                bestroot = j;

            }

        }
    }
    free(roots);
    fprintf(resultsFILE, "Task4 %d %d\n", city, bestroot);    
}

// Devolve 1 se a aresta x for "melhor" que y (ordem total: d2, depois a, depois b).
// O desempate determinístico garante que o Boruvka nunca cria ciclos.
static int melhorAresta(Edge x, Edge y) {
    if (x.d2 != y.d2) return x.d2 < y.d2;
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}

static int cmpEdge(const void *p, const void *q) {
    const Edge *x = p;
    const Edge *y = q;
    if (x->a != y->a) return x->a - y->a;
    return x->b - y->b;
}

// Calcula as arestas novas que unem todos os clusters (Boruvka).
// Trabalha numa COPIA do union-find para nao estragar as Tasks 1-4.
// Devolve array com *nEdges arestas (ordenado por a, b) ou NULL em erro.
Edge *calcularMST(UnionFind *uf, int *X, int *Y, int C, int *nEdges) {
    *nEdges = 0;

    UnionFind uf2;
    uf2.parent = malloc((C + 1) * sizeof(int));
    uf2.size = malloc((C + 1) * sizeof(int));
    int *root = malloc((C + 1) * sizeof(int));
    Edge *best = malloc((C + 1) * sizeof(Edge));
    char *has = malloc((C + 1) * sizeof(char));
    int maxEdges = uf->count > 1 ? uf->count - 1 : 1;
    Edge *mst = malloc(maxEdges * sizeof(Edge));

    if (!uf2.parent || !uf2.size || !root || !best || !has || !mst) {
        free(uf2.parent); free(uf2.size); free(root);
        free(best); free(has); free(mst);
        return NULL;
    }

    for (int i = 1; i <= C; i++) {
        uf2.parent[i] = uf->parent[i];
        uf2.size[i] = uf->size[i];
    }
    uf2.count = uf->count;

    while (uf2.count > 1) {
        for (int i = 1; i <= C; i++) {
            root[i] = findroot(&uf2, i);
            has[i] = 0;
        }

        // cada cluster procura a aresta mais barata para fora de si
        for (int i = 1; i <= C; i++) {
            for (int j = i + 1; j <= C; j++) {
                if (root[i] == root[j]) continue;

                long long dx = (long long)(X[i] - X[j]);
                long long dy = (long long)(Y[i] - Y[j]);
                Edge e = { i, j, dx * dx + dy * dy };

                if (!has[root[i]] || melhorAresta(e, best[root[i]])) {
                    best[root[i]] = e;
                    has[root[i]] = 1;
                }
                if (!has[root[j]] || melhorAresta(e, best[root[j]])) {
                    best[root[j]] = e;
                    has[root[j]] = 1;
                }
            }
        }

        // funde os clusters; revalida porque duas escolhas da mesma ronda
        // podem ligar os mesmos dois clusters
        for (int r = 1; r <= C; r++) {
            if (!has[r]) continue;
            if (findroot(&uf2, best[r].a) != findroot(&uf2, best[r].b)) {
                unionCities(&uf2, best[r].a, best[r].b);
                mst[(*nEdges)++] = best[r];
            }
        }
    }

    qsort(mst, *nEdges, sizeof(Edge), cmpEdge);

    free(uf2.parent); free(uf2.size); free(root);
    free(best); free(has);
    return mst;
}

void doTask5(UnionFind *uf, int *X, int *Y, int C, FILE *resultsFILE, int *firstOutput) {
    if (!*firstOutput) {
        fprintf(resultsFILE, "\n");
    }
    *firstOutput = 0;

    int nEdges = 0;
    Edge *mst = calcularMST(uf, X, Y, C, &nEdges);
    if (mst == NULL) {
        fprintf(resultsFILE, "Task5 -2\n");
        return;
    }

    double total = 0.0;
    for (int i = 0; i < nEdges; i++) {
        total += sqrt((double)mst[i].d2);
    }

    fprintf(resultsFILE, "Task5 %.2f\n", total);
    for (int i = 0; i < nEdges; i++) {
        fprintf(resultsFILE, "%d %d %.2f\n", mst[i].a, mst[i].b, sqrt((double)mst[i].d2));
    }

    free(mst);
}


int main(int argc, char *argv[]){
     //-------Invocação:1.2------//
    if(argc != 4){
        return 0;
    }
    
    if (!extensaoexists(argv[1], ".quests") || 
        !extensaoexists(argv[2], ".map") || 
        !extensaoexists(argv[3], ".position")){

        return 0;
    }

    FILE *questsFILE = fopen(argv[1], "r");
    if(questsFILE == NULL){
        return 0;
    }
    FILE *mapFILE = fopen(argv[2], "r");
    if(mapFILE == NULL){
        fclose(questsFILE);
        return 0;
    }
    FILE *positionFILE = fopen(argv[3], "r");
    if(positionFILE == NULL){
        fclose(questsFILE);
        fclose(mapFILE);
        return 0;
    }
    //-------FIM 1.2------//

    //-------ler cabeçalho  2.2 1)------//
    int C; //nmr de cidades
    int L; //nmr de ligações


    if (fscanf(mapFILE, "%d %d", &C, &L) != 2) {
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    if(C<1 || L<0){
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }
    //-------FIM cabeçalho  2.2 1)------//

    //-------task1----------------------//
    UnionFind uf;
    uf.parent = malloc((C + 1) * sizeof(int));
    uf.size = malloc((C + 1) * sizeof(int));

    if (uf.parent == NULL || uf.size == NULL) {
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }
    uf.count = C;
    for (int i = 1; i <= C; i++) {
        uf.parent[i] = i;
        uf.size[i] = 1;
    }



    No**grafo=calloc(C + 1, sizeof(No*));
    if (grafo == NULL) {
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }  
    //-------FIM task1----------------------//

    //-------pares de cidades  2.2 2)------//
    for(int i = 0; i < L; i++) {
        int city1, city2;
        if (fscanf(mapFILE, "%d %d", &city1, &city2) != 2) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(city1 < 1 || city1 > C || city2 < 1 || city2 > C){
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        unionCities(&uf, city1, city2);

        No*novo1=malloc(sizeof(No));
        if (novo1 == NULL) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        novo1->city=city2;
        novo1->next=grafo[city1];
        grafo[city1]=novo1;

        No*novo2=malloc(sizeof(No));
        if (novo2 == NULL) {
            freeGrafo(grafo, C);

            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        novo2->city=city1;
        novo2->next=grafo[city2];
        grafo[city2]=novo2;
    }
    //-------FIM pares de cidades  2.2 2)------//

    //-------Ficheiro position: 2.3------//
    int Xmax, Ymax;
    if (fscanf(positionFILE, "%d %d", &Xmax, &Ymax) != 2) {
        freeGrafo(grafo, C);

        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    if (Ymax < 1 || Xmax < 1) {
        freeGrafo(grafo, C);

        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    int *X=calloc(C + 1, sizeof(int));
    int *Y=calloc(C + 1, sizeof(int));
    int *seen=calloc(C + 1, sizeof(int));

    if (X == NULL || Y == NULL || seen == NULL) {
        freeGrafo(grafo, C);
        free(X);
        free(Y);
        free(seen);
        uffrees(uf);
        fcloses(questsFILE, positionFILE, mapFILE);
        return 0;
    }

    for(int i=0; i<C; i++){
        int id, x, y;
    
        if (fscanf(positionFILE, "%d %d %d", &id, &x, &y) != 3) {
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(id < 1 || id > C){
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if(x < 1 || x > Xmax || y < 1 || y > Ymax){
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }

        if (seen[id] == 1) {
            freeGrafo(grafo, C);
            free(X);
            free(Y);
            free(seen);
            uffrees(uf);
            fcloses(questsFILE, positionFILE, mapFILE);
            return 0;
        }
        X[id] = x;
        Y[id] = y;
        seen[id] = 1;
    }     
//-------FIM Ficheiro position: 2.3------//

//-------Ficheiro results------//
int lenQuests = strlen(argv[1]);
int lenExtQuests = strlen(".quests");
int lenExtResults = strlen(".results");

char *resultsName = malloc(
    (lenQuests - lenExtQuests + lenExtResults + 1) * sizeof(char)
);

if (resultsName == NULL) {
    free(X);
    free(Y);
    free(seen);

    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);

    return 0;
}

strcpy(resultsName, argv[1]);
resultsName[lenQuests - lenExtQuests] = '\0';
strcat(resultsName, ".results");

FILE *resultsFILE = fopen(resultsName, "w");

if (resultsFILE == NULL) {
    free(resultsName);
    free(X);
    free(Y);
    free(seen);
    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);

    return 0;
}

int firstOutput = 1;
//-------FIM Ficheiro results------//

//-------Ficheiro quests: 2.1------//
    char linha[100];

    while(fgets(linha, sizeof(linha), questsFILE) != NULL){
        char task[20];
        int city;

        int n = sscanf(linha, "%19s %d", task, &city);
        if (n < 1) {
            continue;
        }

        if (strcmp(task, "Task1")==0) {
            if (n != 1) {
                continue;
            }
            doTask1(&uf, resultsFILE, &firstOutput);
        }
        else if (strcmp(task, "Task2")==0) {
            if (n != 1) {
                continue;
            }
        //-----Task2 3.2-----//
         doTask2(&uf, C, resultsFILE, &firstOutput);  //função do Task2
        //-----Fim Task2: 3.2-----//
        }
        else if (strcmp(task, "Task3")==0) {
            if (n != 2) {
                continue;
            }   
        //-----Task3 3.3-----// 
         doTask3(&uf, X, Y, C, city, resultsFILE, &firstOutput);  //função do Task3
        //-----Fim Task3: 3.3-----//

        }
        else if (strcmp(task, "Task4")==0) {
            if (n != 2) {
                continue;
            }
            //-----Task4 3.4-----//
            doTask4(&uf, X, Y, C, city, resultsFILE, &firstOutput);  //função do Task4
           //-----Fim Task2: 3.4-----//
        
        }
        else if (strcmp(task, "Task5")==0) {
            if (n != 1) {
                continue;
            }
            //-----Task5 5.1.1-----//
            doTask5(&uf, X, Y, C, resultsFILE, &firstOutput);
            //-----Fim Task5-----//
        }
        else {
        }


    }
//-------FIM 2.1------//
    free(X);
    free(Y);
    free(seen);

    uffrees(uf);
    freeGrafo(grafo, C);

    fcloses(questsFILE, positionFILE, mapFILE);
    fclose(resultsFILE);

    free(resultsName);

    return 0;
    main
}