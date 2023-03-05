#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define BYTE 8
#define COUNT_BYTE 256

int NR = 0;

void schimba(int a[],int i,int j) //functie auxiliara
{
    int aux;
    aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}
void cerne(int a[],int n,int k)
{
    NR++;

    int fiuStanga = 2 * k + 1, //pozitia primului copil
        fiuDreapta = 2 * k + 2,
        pozMax = fiuStanga; //pozitia copilului mai mare
    if(fiuStanga >= n)
        return; //"nodul" k este frunza
    if(fiuDreapta < n) {
        if(a[fiuDreapta] > a[fiuStanga] ) {
            pozMax = fiuDreapta;
        }
    }//am ales copilul mai mare
    if(a[k] < a[pozMax]) {
        schimba(a,k,pozMax); //nodul k este "cernut" - coboara
        cerne(a,n,pozMax); //cernem la noua lui pozitie
    }
}
void makeHeap(int a[],int n) //functia mai e numita "heapify"
{
    //pentru i > n / 2, i este cu siguranta nod frunza
    for(int i = n / 2;i >= 0;i--) { //ne asiguram ca exista ordine
        cerne(a,n,i); // pentru orice nod de la i la n-1
    }
}
void heapSort(int a[],int n)
{
    makeHeap(a,n); //construim un heap
    printf("%d apelari a functiei \"cerne\" pentru crearea heapului.", NR);

    while(n > 1) {
        schimba(a,0,n-1); //mutam maximul pe ultima pozitie
        n--; //am asezat un element pe pozitia finala
        cerne(a,n,0); //elementul pus in locul maximului trebuie "cernut"
        //obtinem din nou forma de heap
    }
 
}

int obtineOctetul(int n,int byteNr)
{   //cautam octetul de la pozitia byteNr
    //octetul de pe pozitia 0 este LSD = octetul cel mai din dreapta(pentru int)
    int bitsNr =  BYTE * byteNr;
    int mask = COUNT_BYTE - 1;
    return (n >> bitsNr) & mask;
}
void rad(int *a,int *b, int byteNr,int n)
{   //sortare dupa octetul de pe pozitia byteNr,
    // pe pozitia 0 este LSD = octetul cel mai din dreapta
    int i,
        count[COUNT_BYTE] = {0}, //numaram cate elemente au "car." i pe pozitia byteNr
        index[COUNT_BYTE] = {0}; //pozitia la care vom pune urmatorul element cu "car." i
    for(i = 0; i < n;i++) {
        int car = obtineOctetul(a[i],byteNr);
        count[car]++;
    }
    for(i = 1;i < COUNT_BYTE;i++) //sectionam vectorul b
        index[i] = index[i-1] + count[i-1];
    for(i = 0; i < n; i++) { //umplem sectiunile
        int car = obtineOctetul(a[i],byteNr);

        b[index[car]++] = a[i];
    }
}
void radixSort(int *a,int n)
{
    int *b, //vector folosit la copiere
        byteNr, //pozitia curenta
        k = sizeof(a[0]); //numarul de "caractere"

    b = (int*) malloc(n*sizeof(int));
    
    for(byteNr = 0; byteNr < k; byteNr += 2) {
        rad(a, b, byteNr, n); //in loc sa copiem b inapoi in a la fiecare pas
        rad(b, a, byteNr + 1, n); //copiem doar o data la 2 pasi
    }
    free(b);
}

void rotate(int arr[], int n)
{
   int temp = arr[0], i;

   for (i = 0; i < n; i++)
      arr[i] = arr[i + 1];

   arr[n - 1] = temp;
}

int main()
{
    int n = 1e6, *a, *b, i = 0;

    a = (int*) malloc(n*sizeof(int));
    b = (int*) malloc(n*sizeof(int));

    srand(time(0));

    while(i < n)
    {
        a[i] = rand()%10000;
        i++;
    }

    b = a;

    clock_t begin = clock();

    heapSort(a, n);

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTimpul pentru Heapsort: %f", time_spent);

    begin = clock();

    radixSort(b, n);

    end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTimpul pentru Radixsort: %f", time_spent);

    printf("\n%d apelari a functiei \"cerne\" in total.", NR);
    printf("\n");

    b = (int*)realloc(b,10);

    i = 0;
    while(i < 10)
    {
        b[i] = (int)pow((-1),rand()%2)*rand()%11;
        i++;
    }

    i = 0;
    while(i < 10)
    {
        printf("%d ", b[i]);
        i++;
    }printf("\n");

    radixSort(b, 10);

    i = 0;
    while(b[i] >= 0)
        i++;

    while(i != 0)
    {
        rotate(b, 10);
        i--;
    }

    i = 0;
    while(i < 10)
    {
        printf("%d ", b[i]);
        i++;
    }printf("\n");

    //free(a); nu stiu de ce daca apelez free() programul nu se mai inchide cu succes
    //free(b);

    return 0;

}