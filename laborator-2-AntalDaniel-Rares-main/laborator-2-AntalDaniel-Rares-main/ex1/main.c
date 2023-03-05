#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

struct moment{
    int ora,minut,secunda;
};

int main()
{
    int *arr,*copy,i,j=0;

    struct moment *t;

    char s[10][5];

    srand(time(NULL));

    arr=(int *)malloc(20*sizeof(int));
    copy=(int *)malloc(20*sizeof(int));

    for(i=0;i<20;i++)
    {
        *(arr+i)=rand()%100;
    }
    
    copy=arr;

    print(arr,20);

    mergesort(arr,0,19);

    selectionsort(copy,20);

    printf("\nquicksort->%d comparatii\ninsertionsort->%d comparatii",nrq,nri);

    print(arr,20);

   free(copy);
   free(arr);

    for(i=0;i<10;i++)
        {   
            for(j=0;j<4;j++)
            {
                if(strlen(s[i])<=2 && rand()%2)
                    s[i][j]=(rand()%('a'-'z')+'a');
            }
            //s[i][5]='\0';
        }
    
    printchar(s,10);

    selectionsort_char(s,10);

    printchar(s,10);

    t=(struct moment *)malloc(10*sizeof(struct moment));
    arr=(int*)malloc(10*sizeof(int));

    for(i=0;i<10;i++)
    {
        (t+i)->secunda=rand()%60;
        (t+i)->minut=rand()%60;
        (t+i)->ora=rand()%24;
    }

    for(i=0;i<10;i++)
        *(arr+i)=(t+i)->ora*3600+(t+i)->minut*60+(t+i)->secunda;

    printstruct(t,10);

    mergesort(arr,0,9);

    for(i=0;i<10;i++)
    {
        (t+i)->secunda=*(arr+i)%3600%60;
        (t+i)->minut=*(arr+i)%3600/60;
        (t+i)->ora=*(arr+i)/3600;
    }

    printf("\n");

    printstruct(t,10);

    free(arr);

    arr=(int*)malloc(50*sizeof(int));

    for(i=0;i<50;i++)
        *(arr+i)=rand()%1001;

    print(arr,50);

    radixsort(arr,50);

    print(arr,50);

    free(arr);

    return 0;

}