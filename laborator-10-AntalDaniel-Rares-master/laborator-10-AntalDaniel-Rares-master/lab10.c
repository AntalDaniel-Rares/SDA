#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge{
    int v1, v2, cost;
}Edge;

typedef struct g{
    int V;
    int E;        
    Edge *edg;
}Graph;

void swap(Edge* a, Edge* b)
{ 
    Edge aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int partition(Edge* arr, int low, int high)
{
    int j, i = low - 1;
    Edge aux;
    Edge pivot = arr[high];

    for(j = low; j <= high - 1; j++)   
        if(arr[j].cost <= pivot.cost)    
        {
            i++;
            swap(&arr[i], &arr[j]);
        } 
    
    swap(&arr[i + 1], &arr[high]);
    
    return i + 1;

}

void quickSort(Edge* arr, int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi -1);
        quickSort(arr, pi + 1, high);
    }
    
}

void Kruskal(Graph *g, char **list)
{
    int i, j, min, max, nrMuchiiSelectate = -1;
    int c[g->V]; 

    for(i = 0; i < g->V; i++) 
        c[i] = i;    

    Edge a[g->V - 1];

    quickSort(g->edg, 0, (g->E)-1);

    for(i = 0; nrMuchiiSelectate < g->V - 1 && i < g->E; i++)
    {
        if(c[g->edg[i].v1] != c[g->edg[i].v2]) 
            a[++nrMuchiiSelectate] = g->edg[i];

        if(c[g->edg[i].v1] < c[g->edg[i].v2])
        {
            min = c[g->edg[i].v1];
            max = c[g->edg[i].v2];
        }
        else
        {
            max = c[g->edg[i].v1];
            min = c[g->edg[i].v2];
        }
        
        for(j = 0; j < g->V; j++) 
            if(c[j] == max) 
                c[j] = min;
                
    }

    if(!list)
        for(i = 0; i < g->V - 1; i++) 
            printf("%d %d %d\n", a[i].v1, a[i].v2, a[i].cost);
    else for(i = 0; i < g->V - 1; i++) 
            printf("%s->%s %d\n", list[a[i].v1], list[a[i].v2], a[i].cost);

}


Graph *graphcreate(Graph *g, FILE *f)
{
    g = (Graph*) malloc (sizeof(Graph));

    fscanf(f, "%d", &g->V);
    fscanf(f, "%d", &g->E);

    g->edg = (Edge*) malloc(g->E * sizeof(Edge));

    int i = 0;
    while(i < g->E)
    {
        fscanf(f, "%d", &g->edg[i].v1);
        fscanf(f, "%d", &g->edg[i].v2);
        fscanf(f, "%d", &g->edg[i].cost);

        i++;
    }

    return g;
}

void print_matrix(int **a, int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            printf("%d ", a[i][j]);
        }

        printf("\n");
        
    }
    
}

int main()
{
    FILE *f;

    f = fopen("date.txt", "rt");

    int i = 0, j, k, cost;
    char **list;
    Graph *g;

    g = graphcreate(g, f);

    //print_matrix(g->a, g->V);

    list = NULL;

    Kruskal(g, list);

    fclose(f);

    f = fopen("graph_trains.txt", "rt");

    Graph *graph_trains;

    graph_trains = graphcreate(graph_trains, f);

    fclose(f);

    list = (char**) malloc(2 * graph_trains->V * sizeof(char*));
    for ( i = 0; i < graph_trains->V; i++)
    {
        list[i] = (char*) malloc(20 * sizeof(char));
    }
    

    f = fopen("trains.txt", "rt");

    i = 0;
    while(fscanf(f, "%[^\n] ", list[i++]) != EOF);

    Kruskal(graph_trains, list);

    fclose(f);
    
    return 0;
}