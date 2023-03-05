#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nrq=0,nri=0;

struct moment{
    int ora,minut,secunda;
};

void print(int *arr,int dim)
{
    int i;

    printf("\n");

    for(i=0;i<dim;i++)
        printf("%d ",*(arr+i));
}

void printchar(char s[10][5],int dim)
{
    int i;

    printf("\n");

    for(i=0;i<dim;i++)
        printf("%s\n",s[i]);

}

void printstruct(struct moment *t,int dim)
{
    int i;

    for(i=0;i<dim;i++)
        printf("%d:%d:%d\n",(t+i)->ora,(t+i)->minut,(t+i)->secunda);
}

void merge(int *arr, int left, int middle, int right)
{
    int *l,*r,x,y;

    x=middle-left+1;
    y=right-middle;

    l=(int *)malloc(x*sizeof(int));
    r=(int *)malloc(y*sizeof(int));

    int i,j;

    for(i=0;i<x;i++)
        *(l+i)=*(arr+left+i);

    for(j=0;j<y;j++)
        *(r+j)=*(arr+middle+1+j);

    int k=left;
    i=0;
    j=0;

    while(i<x && j<y)
    {
        if(*(l+i)<=*(r+j))
            {
                *(arr+k)=*(l+i);
                i++;
            }
        else 
            {
                *(arr+k)=*(r+j);
                j++;
            }
        k++;
        nrq++;
    }

    while(i<x)
    {
        *(arr+k)=*(l+i);
        i++;
        k++;
    }

    while(j<y)
    {
        *(arr+k)=*(r+j);
        j++;
        k++;
    }

    free(l);
    free(r);
}

void mergesort(int *arr, int left, int right)
{
    int middle;

    if(left<right)
    {
        middle=left+(right-left)/2;
        mergesort(arr,left,middle);
        mergesort(arr,middle+1,right);

        merge(arr,left,middle,right);
    }
}

void selectionsort(int *arr,int dim)
{
    int i,j,aux;

    for(i=0;i<dim-1;i++)
        for(j=i+1;j<dim;j++)
            {
                if(*(arr+i)>*(arr+j))
                {
                 aux=*(arr+i);
                 *(arr+i)=*(arr+j);
                 *(arr+j)=aux;
                }
                nri++;
            }
}

void selectionsort_char(char s[10][5],int dim)
{
    int i=1,j;
    char *aux;

    aux=(char *)malloc(4*sizeof(char));

    for(i=0;i<dim-1;i++)
    {
        for(j=i+1;j<dim;j++)
            {
                if(strcmp(s[i],s[j])>0)
                {
                 strcpy(aux,s[i]);
                 strcpy(s[i],s[j]);
                 strcpy(s[j],aux);
                }
            }
    }
}

void countingSort(int *arr, int dim, int ex)
{
   int *f,i,*newarr;

   f=(int *)malloc(10*sizeof(int));

    for(i=0;i<dim;i++)
        {
            *(f+(*(arr+i)/ex)%10)+=1;
        }

    for(i=0;i<10;i++)
    {
        *(f+i)+=*(f+i-1);
    }

    newarr=(int *)malloc(dim*sizeof(int));
    
    /*for(i=0;i<dim;i++)
    printf("%d ",*(arr+i));*/

    for(i=dim-1;i>=0;i--)
    {
        *(newarr+*(f+(*(arr+i)/ex)%10)-1)=*(arr+i);
        //printf("newarr+%d=%d ",f[*(arr+i)]-1,*(arr+i));
        *(f+(*(arr+i)/ex)%10)-=1;
    }

    for (i=0;i<dim;i++) 
        *(arr+i)=*(newarr+i);

}

void radixsort(int *arr,int dim)
{
    int mx=0,i,ex;

    for(i=0;i<dim;i++)
    {
        if(mx<*(arr+i))
            mx=*(arr+i);
    }

    for(ex=1;mx/ex>0;ex*=10)
        countingSort(arr,dim,ex);

    
   
}