#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct g{
    int V;
    int E;        
    int **a;
    int size;
}Graph;

void resize(Graph *g)
{
    g->size = 2 * g->size;

    int **matrix;

    matrix = (int**) realloc(g->a, g->size*g->size*sizeof(int*));
    if(matrix)
        g->a = matrix;
    else printf("Eroare la alocare!");

    int *b;

    for(int i = 0; i < g->size; i++)
    {
        b = (int*) realloc(g->a[i], g->size*sizeof(int));

        if(b)
            g->a[i] = b;
        else printf("Eroare la alocare!");

    }

    int i = 0, j = g->size / 2;

    while(i < g->size)
    {
        j = g->size / 2;
        while (j < g->size)
        {
            g->a[i][j] = 0;
            j++;
        }
        i++;
    }

    j = 0; i = g->size / 2;

    while(i < g->size)
    {
        j = 0;
        while (j < g->size / 2)
        {
            g->a[i][j] = 0;
            j++;
        }
        i++;
    }   

}

Graph *graphcreate(Graph *g)
{
    g = (Graph*) malloc (sizeof(Graph));
    g->E = 0;
    g->V = 0;

    g->size = 1;

    resize(g);

    g->a[0][0] = 0;

    return g;
}

int search(char *station, char **list, int k, int *i)
{
    *i = 0;
    int ok = 0;

    while(*i < k)
        {
            if(strcmp(station, list[*i]) == 0)
            {
                ok = 1;
                break;
            }
                    
            (*i)++;
        }

    return ok;

}

int minmaxsum(Graph *g, char **list)
{
    int i, j, *poz, sum = 0, max, min;

    poz = (int*) malloc(4*sizeof(int));

    min = max = g->a[0][1];

    for(i = 0; i < g->V; i++)
        for (j = 0; j < g->V; j++)
        {
            if(g->a[i][j] != 0)
            {
                sum = sum + g->a[i][j];

                if(max < g->a[i][j])
                    {
                        max = g->a[i][j];
                        poz[0] = i;
                        poz[1] = j;
                    }

                if(min > g->a[i][j])
                    {
                        min = g->a[i][j];
                        poz[2] = i;
                        poz[3] = j;
                    }
            }
        }

    FILE *f;

    f = fopen("min.txt", "wt");
    fprintf(f, "%s->%s (%d km)", list[poz[2]], list[poz[3]], min);
    fclose(f);

    f = fopen("max.txt", "wt");
    fprintf(f, "%s->%s (%d km)", list[poz[0]], list[poz[1]], max);
    fclose(f);

    f = fopen("total.txt", "wt");
    fprintf(f, "In baza noastra de date exista %d km.",sum/2);
    fclose(f);

    free(poz);

    return max;
        
}

int minDistance(int dist[], int ok[], int n) 
{
   int min = INT_MAX, min_index;
   for (int v = 0; v < n; v++)
   if (ok[v] == 0 && dist[v] <= min)
      min = dist[v], min_index = v;
   return min_index;
}

void printSolution(int dist[], int n) 
{
   printf("Vertex Distance from Source\n");
   for (int i = 0; i < n; i++)
      printf("%d \t %d\n", i, dist[i]);
}

int dijkstra(int **graph, int src, int n, char **list, int target, int *max_destination) 
{
    int *dist = (int *) malloc(n*sizeof(int));
    int *ok = (int *) malloc(n*sizeof(int));
    int *parent = (int *) malloc(n*sizeof(int));
    int max_index = src;

    for (int i = 0; i < n; i++)
    dist[i] = INT_MAX, ok[i] = 0, parent[i] = -1;
        
    dist[src] = 0;

   for (int count = 0; count < n - 1; count++) 
   {
        int u = minDistance(dist, ok, n);
        ok[u] = 1;

        for (int v = 0; v < n; v++)
            if (!ok[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) 
                dist[v] = dist[u] + graph[u][v], parent[v] = u;
   }

    for (int i = 0; i < n; i++)
    if(dist[max_index] < dist[i])
            max_index = i;

    if(target == -1)
    {
        *max_destination = max_index;
        return dist[max_index];
    }

    FILE *f = fopen("ruta.txt", "wt");

    fprintf(f, "%d km\n", dist[target]);

    int k = target;
    while(k != -1)
    {
        if(parent[k] != -1)
            fprintf(f, "%s->", list[k]); 
        else fprintf(f, "%s", list[k]);
        k = parent[k];
    }

    fclose(f);

    f = fopen("departe.txt", "wt");        
    fprintf(f, "%d km\n", dist[max_index]);

    k = max_index;
    while(k != -1)
    {
        if(parent[k] != -1)
            fprintf(f, "%s->", list[k]); 
        else fprintf(f, "%s", list[k]);
        k = parent[k];
    }

    fclose(f);

    //printSolution(dist, n);
}

int main()
{
    char **list, *filename, *station, *input;

    FILE* f;
    Graph *g, *go, *costs;

    g = graphcreate(g);
    go = graphcreate(go);
    costs = graphcreate(costs);

    f = fopen("trains_with_km/_all_files.txt","rt");
    filename = (char*) malloc (10*sizeof(char));
    input = (char*) malloc (40*sizeof(char));
    list = (char**) malloc (g->size*sizeof(char*));

    while(fscanf(f, "%s", filename) != EOF)
    {
        int first = 1, poz, i, last = 0;

        char prefix[16] = "trains_with_km/";
        strcat(prefix, filename);
        strcpy(filename, prefix);

        FILE* F;
        if(fopen(filename,"rt") != NULL)
            F = fopen(filename,"rt");
        else continue;

        while(fscanf(F, "%[^\n] ", input) != EOF)
            {
                if(input[strlen(input) - 1] == '\n' || input[strlen(input) - 1] == '\r')
                    input[strlen(input) - 1] = '\0';

                station = strtok(input, ",");

                if(!search(station, list, g->V, &i))
                {
                    list[g->V++] = strdup(station);
                    go->V++;
                    costs->V++;
                }

                if(g->V > g->size)
                {
                    resize(g);
                    list = (char**) realloc (list, g->size*sizeof(char*));
                    resize(go);
                    resize(costs);
                }

                if(!first) 
                {
                    if(g->a[poz][i] != 1)
                    {
                        g->a[poz][i] = 1;
                        g->a[i][poz] = 1;
                        g->E++;
                    }

                    if(go->a[poz][i] != 1)                   
                    {
                        go->a[poz][i] = 1;
                        go->E++;
                    }

                    costs->a[i][poz] = strtol(input + strlen(station)+1, NULL, 10);
                    costs->a[poz][i] =  costs->a[i][poz] - last;
                    last = costs->a[i][poz];
                    costs->a[i][poz] = costs->a[poz][i];
                }

                poz = i;
                first = 0;

            }
        
        fclose(F);
            
    }

    fclose(f);

    int i = 0, j = 0;

    /*while(i < g->V)
    {
        printf("%s %d\n", list[i], i);
        i++;
    }*/

    int max, index = 0;

    max = minmaxsum(costs, list);

    f = fopen("cost.txt", "wt");

    for(i = 0; i < g->V; i++)
        {for (j = 0; j < g->V; j++)
            fprintf(f, "%d ", costs->a[i][j]);
        fprintf(f, "\n");}

    fclose(f);

    dijkstra(costs->a, 0, costs->V, list, 213, &index);

    int dj, max_index;
    max = 0;
    for(i = 0; i < g->V; i++)
    {
        dj = dijkstra(costs->a, i, costs->V, list, -1, &index);
        if(max < dj)
        max = dj, j = i, max_index = index;
    }

    f = fopen("drum_lung.txt", "wt");
    fprintf(f, "%s(statia %d)->%s(statia %d) %dkm\n", list[j], j, list[max_index], max_index, max);
    fclose(f);
        
    return 0;

}