#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct student{
    char *nume, *prenume;
    char id[6];   //id student
    double note[5]; // aici se salveaza notele obtinute in semestrul anterior
};


void restante(struct student *s,int m)
{
    FILE* f;
    int i,j,nr;
    
    f=fopen("restanta.txt","wt");

    for(i=0;i<m;i++)
    {   
        j=0;
        nr=0;
        while(j<5)
           {
            if((s+i)->note[j]<5)
                nr++;
            j++;
           }

        if(nr>0)
        fprintf(f,"%s %s %s cu %d restante\n",(s+i)->id,(s+i)->nume,(s+i)->prenume,nr);
    }

    fclose(f);

}

void stergere(struct student *s,int m)
{
    int i,j,ok,k,nr=0;

    for(i=0;i<m;i++)
    {
        j=0;
        ok=0;
        while(j<5)
        {
            if((s+i)->note[j]<5)
                ok=1;
            j++;
        }

        if(ok==1)
        {
            for(k=i;k<m-1;k++)
                {
                    s+k=s+k+1;
                }
            nr++;
            i--;
        }
    }

    s=realloc(s,nr);

}



int main()
{
    struct student *s;
    int m;

    printf("Cati studenti doriti sa adaugati?\n");
    scanf("%d",&m);

    s=malloc(m*sizeof(struct student));

    char n[4][10]={"Paiu","Iliopolus","Musteata","Vranceanu"},p[5][10]={"Radu","Andrei","Ana","Lucretia","Eustache"};

    int i=0,np[4][6]={0},j,k,l,q;

    srand(time(NULL));

    while(i<m && i<20)
    {
        (s+i)->nume=malloc(sizeof(char));
        (s+i)->prenume=malloc(sizeof(char));
        j=rand()%4;
        k=rand()%5;
        while(np[j][k]!=0)
        {
            j=rand()%4;
            k=rand()%5;
        }
        strcpy((s+i)->nume,n[j]);
        strcpy((s+i)->prenume,p[k]);
        np[j][k]=1;
    
        l=0;
        while(l<5)
        {
            (s+i)->note[l]=rand()%91/10.+1;
            l++;
        }

        l=0;
        while(l<6)
        {
            q=rand()%10;
            (s+i)->id[l]='0'+q;
            l++;
        }
       
        i++;
    }

    for(i=0;i<m;i++)
        {
            printf("%s %s %s",(s+i)->id,(s+i)->nume,(s+i)->prenume);

            l=0;
            while(l<5)
            {
                printf(" %.2f ",(s+i)->note[l]);
                l++;
            }
            printf("\n");
        }
   
   restante(s,m);

    return 0;

}

