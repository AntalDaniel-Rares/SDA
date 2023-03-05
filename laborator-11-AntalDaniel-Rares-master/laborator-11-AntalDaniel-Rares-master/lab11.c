#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 20
#define N_cartezian 6
#define N 9
 
int findMin(int cost, int bani[], int size, FILE *f)
{
    int *list;

    list = calloc(size, sizeof(int));

    int i, k = 0;
 
    for (i = size - 1; i >= 0; i--) 
    {
        list[i] = cost/bani[i];
        cost %=bani[i];
        k += list[i]; 
    }
 
    fprintf(f, "Restul este format din:");
    for (i = size - 1; i >= 0; i--) 
    {
        if(list[i] != 0)
            fprintf(f, "\n%d X %d lei", list[i], bani[i]);
    }

    return k;
}

void print(int *arr, int n, FILE *f)
{
    for (int i = n - 1; i >= 0; i--)
        fprintf(f, "%d", arr[i]);

    fprintf(f, "\n");
   
}

void produs_cartezian(int arr[], int n, int lenght, int results[], FILE *f)
{
    if(n >= 0)
    {
        for (int i = 0; i < lenght; i++)
        {
            results[n] = arr[i];
            produs_cartezian(arr, n - 1, lenght, results, f);
        }
        
    }
    else print(results, N_cartezian, f);

    return;

}

void Afis(int x[], int counter, FILE *f)
{

    for( int j = 0; j < counter; j++)
        fprintf(f, "%d ", x[j]);
    fprintf(f, "\n");
}

int OK(int x[], int counter)
{
    for(int i = 0; i < counter; i++)
        if(x[counter] == x[i])
            return 0;
    return 1;
}

void perm(int x[], int n, int counter, int k, FILE *f)
{
    for(int i = 1; i <= n ; i++)
    {
        x[counter] = i;
        if(OK(x, counter))
            if(counter == k - 1)
                Afis(x, k, f);
            else
                perm(x, n, counter + 1, k, f);
    }
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int k, FILE *f)
{
    if (index == k)
    {
        Afis(data, k, f);
        return;
    }
 
    for (int i = start; i <= end && end - i + 1 >= k - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1, end, index + 1, k, f);
    }
}

void printCombination(int arr[], int n, int k, FILE *f)
{
    int data[k];
 
    combinationUtil(arr, data, 0, n - 1, 0, k, f);
}

void print_matrix(int arr[N][N], FILE *f)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fprintf(f, "%d ",arr[i][j]);
            if((j + 1)%3 == 0)
                fprintf(f, " | ");
        }

       if((i + 1)%3 == 0)
            fprintf(f, "\n───────+────────+────────+");

        fprintf(f, "\n");
    }
}
 
int isSafe(int grid[N][N], int row, int col, int num)
{ 
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;

    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
 
    int startRow = row - row % 3,
                 startCol = col - col % 3;
   
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
 
    return 1;
}

int solveSuduko(int grid[N][N], int row, int col)
{
    if (row == N - 1 && col == N)
        return 1;

    if (col == N)
    {
        row++;
        col = 0;
    }

    if (grid[row][col] > 0)
        return solveSuduko(grid, row, col + 1);
 
    for (int num = 1; num <= N; num++)
    {

        if (isSafe(grid, row, col, num)==1)
        {
            grid[row][col] = num;

            if (solveSuduko(grid, row, col + 1)==1)
                return 1;
        }

        grid[row][col] = 0;
    }
    return 0;
}
 
int main()
{
    int n = 78, nr = 0, bani[] = { 1, 5, 10, 50, 100,};
    int size = sizeof(bani)/sizeof(int);

    FILE *f = fopen("ex1-2.txt", "wt");

    fprintf(f, "--------ex1--------\n");
    fprintf(f, "Suma de bani: %d\n", n);
    nr = findMin(n, bani, size, f);
    fprintf(f, "\nA fost nevoie de %d bancnote.\n", nr);
    
    int bani2[] = {1, 3, 5, 15, 30, 50, 150};
    size = sizeof(bani2)/sizeof(int);
    fprintf(f, "\n--------ex2--------\n");
    n = 90;
    fprintf(f, "Suma de bani: %d\n", n);
    nr = findMin(n, bani2, size, f);
    
    fprintf(f, "\nA fost nevoie de %d bancnote.\n", nr);
    fprintf(f, "\nTehnica greedy nu mai este optima in acest caz deoarece algoritmul incepe de la cele mai mari bancnote.\nRaspunsul corect este 3 bancnote: 30 30 30.");
    fclose(f);

    int arr[] = {1, 2, 3}, lenght = sizeof(arr)/sizeof(int), results[N_cartezian];
    n = N_cartezian;

    f = fopen("ex3.txt", "wt");
    fprintf(f, "=================\n=======ex3=======\n=================\n\n");
    produs_cartezian(arr, n - 1 , lenght, results, f);

    fclose(f);

    int a[10];

    f = fopen("ex4.txt", "wt");
    fprintf(f, "=================\n=======ex4=======\n=================\n");
    n = 4;
    fprintf(f, "\nPermutari de %d:\n", n);
    perm(a, n, 0, n, f);
    fclose(f);

    int array[] = {1, 2, 3, 4};
    int k = 3;
    n = sizeof(array)/sizeof(array[0]);

    f = fopen("ex5.txt", "wt");
    fprintf(f, "==================\n=======ex5a=======\n==================\n");
    n = 4;
    fprintf(f, "\nCombinari de %d luate de cate %d:\n", n, k);

    printCombination(array, n, k, f);

    fprintf(f, "\n==================\n=======ex5b=======\n==================\n");
    n = 4;
    k = 3;
    fprintf(f, "\nAranjamente de %d luate de cate %d:\n", n, k);
    perm(array, n, 0, k, f);
    fclose(f);

    f = fopen("ex6.txt", "wt");
    fprintf(f, "=================\n=======ex6=======\n=================\n\n");

    int grid[N][N] = { { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
                       { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
                       { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
                       { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
                       { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
                       { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
                       { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
                       { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
                       { 0, 0, 0, 0, 8, 0, 0, 7, 9 } };
 
    if (solveSuduko(grid, 0, 0)==1)
        print_matrix(grid, f);
    else
        fprintf(f, "No solution exists");

    fclose(f);

    return 0;
}