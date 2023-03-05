#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double radical(float N, int ordin)
{
    double low = 1, middle = N/2, high = N;
    float n;
    int nr = 0;
    const int err = 1000000;

    if(ordin == 2)
         n = (float)(middle * middle);
    else if(ordin == 3)
        n = (float)(middle * middle * middle);
    else {
        printf("Ordin invalid!\n");
        middle = -1;
        return middle;
    }

    while((int)(n * err) != (int)(N * err))
    {
        nr++;

        if(n > N)
        {
            high = middle;
            middle = (high + low)/2;
        }
        else {
                low = middle;
                middle = (high + low)/2;
            }
        
        if(ordin == 2)
            n = (float)(middle * middle);
        else if(ordin == 3)
            n = (float)(middle * middle * middle);

    }

    //printf("nr = %d", nr);
    
    return middle;
}

double logaritm(float N)
{
    double low = 1, middle = N/2, high = N;
    float n;
    int nr = 0;
    const int err = 1000;

    n = pow(10, middle);

    while((int)(n * err) != (int)(N * err))
    {
        nr++;

        if(n > N)
        {
            high = middle;
            middle = (high + low)/2;
        }
        else {
                low = middle;
                middle = (high + low)/2;
            }
        
        n = pow(10, middle);

    }

    //printf("nr = %d", nr);
    
    return middle;
}

int fib_mem(int n, int memo[])
{   
    if ((n == 0) || (n == 1)) 
        return memo[n] = n;

    if (memo[n] == 0)
        memo[n] = fib_mem(n - 1, memo) + fib_mem(n - 2, memo);
        
    return memo[n];
}

int fib(int n)
{
    int a = 0, b = 1, c, i;

    if (n == 0)
        return a;

    for (i = 2; i <= n; i++) 
    {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int da_rest(int rest, int *monede, int tip_moneda, int cate_tipuri_monede)
{ 
    if (tip_moneda >= cate_tipuri_monede - 1) 
        if(rest%monede[tip_moneda] == 0)//in caz ca moneda cu valoarea cea mai mica nu este 1
            return 1;
        else return 0;

    int cate_moduri = 0;
    int val = monede[tip_moneda];
    int i, ce_ramane;

    for(i = 0; i * val <= rest; i++) 
    {
        ce_ramane = rest - (i * val);
        cate_moduri += da_rest(ce_ramane, monede, tip_moneda + 1, cate_tipuri_monede); 
    }

    return cate_moduri;
}

void varianta_print(int *aux, int cate_tipuri_monede, int *monede)
{
    printf("\n");    
    
    for (int i = 0; i < cate_tipuri_monede; i++)
    {
        if(aux[i] != 0)
            printf("%d RON X %d ", monede[i], aux[i]);
    }

}

int da_rest_mem(int rest, int *monede, int tip_moneda, int cate_tipuri_monede, int *aux)
{ 

    if (tip_moneda >= cate_tipuri_monede - 1) 
        if(rest%monede[tip_moneda] == 0)//in caz ca moneda cu valoarea cea mai mica nu este 1
        {
            aux[tip_moneda] = rest / monede[tip_moneda];
            varianta_print(aux, cate_tipuri_monede, monede);
            return 1;
        }
        else return 0;

    int cate_moduri = 0;
    int val = monede[tip_moneda];
    int i, ce_ramane;

    for(i = 0; i * val <= rest; i++) 
    {
        aux[tip_moneda] = i;

        ce_ramane = rest - (i * val);
        cate_moduri += da_rest_mem(ce_ramane, monede, tip_moneda + 1, cate_tipuri_monede, aux);;
    }

    return cate_moduri;
}

int main()
{
    float N = 3;
    double rad;
    int ordin = 2;

    rad = radical(N, ordin);

    if(rad != -1)
        printf("Radical din %f de ordin %d este %f.\n", N, ordin, rad);

    N = 120;
    double log;

    log = logaritm(N);
    printf("Logaritm in baza 10 din %f este %f.\n", N, log);

    int n = 40;
    int *v = (int*) calloc(n + 1, sizeof(int));

    clock_t start, end;
    double cpu_time_used;

    start = clock();    
    int f = fib_mem(n, v);
    end = clock();

    printf("\nSirul lui Fibonacci:\n");
    for(int i = 0; i <= n; i++)
        printf("%d ", v[i]);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTimpul scurs la rualarea algoritmului care include memorarea elementelor este %fs.\n", cpu_time_used);

    start = clock();
    f = fib(n);
    end = clock();
    printf("\nElementul de pe pozitia %d din sirul lui Fibonacci este %d.\n", n, f);

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTimpul scurs la rualarea algoritmului care nu include memorarea elementelor este %fs.\n", cpu_time_used);

    int arr[] = {25, 10, 5, 1};
    int m = sizeof(arr)/sizeof(arr[0]);
    n = 100;
    printf("\nExista %d posibilitati prin care se poate ajunge la restul %d.\n", da_rest(n, arr, 0, m), n);

    n = 100;

    int *aux;
    aux = (int*) calloc(m, sizeof(int));

    printf("\nExista %d posibilitati prin care se poate ajunge la restul %d.\n", da_rest_mem(n, arr, 0, m, aux), n);
    
    return 0;

}