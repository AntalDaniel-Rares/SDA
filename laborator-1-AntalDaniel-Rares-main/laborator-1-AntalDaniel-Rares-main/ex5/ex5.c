#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct student{
    char *nume, *prenume;
    char id[6];   //id student
    double note[5]; // aici se salveaza notele obtinute in semestrul anterior
};


void generare_nume(struct student *s,int i,int np[4][5])
{
    int j,k;
    char n[4][10]={"Paiu","Iliopolus","Musteata","Vranceanu"};
    char p[5][10]={"Radu","Andrei","Ana","Lucretia","Eustache"};

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
}

void generare_note(struct student *s,int i)
{
    int l=0;

    while(l<5)
    {
        (s+i)->note[l]=rand()%91/10.+1;
        l++;
    }
}

void generare_id(struct student *s,int i)
{
    int l,q;

    l=0;

    while(l<6)
    {
        q=rand()%10;
        (s+i)->id[l]='0'+q;
        l++;
    }
    (s+i)->id[6]='\0';

}

void afisare(struct student *s,int m)
{
    int i,j;

    for(i=0;i<m;i++)
    {
        printf("%s %s %s",(s+i)->id,(s+i)->nume,(s+i)->prenume);

            j=0;
            while(j<5)
            {
                printf(" %.2f ",(s+i)->note[j]);
                j++;
            }
            printf("\n");
    }
}

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
        while(j<5 && ok!=1)
        {
            if((s+i)->note[j]<5)
                ok=1;
            j++;
        }

        if(ok==1)
        {
            for(k=i;k<m-1;k++)
                {
                    *(s+k)=*(s+k+1);
                }
            m--;
            i--;
        }
    }

    s=realloc(s,m);
    printf("\n");

    afisare(s,m);

}

void adaugare(struct student *vector,int dimensiune,int poz)
{
    struct student stud;
    stud.nume=malloc(10*sizeof(char));
    stud.prenume=malloc(10*sizeof(char));
    
    printf("Id:");
    scanf("%s",stud.id);
    fflush(stdin);
    printf("Nume:");
    scanf("%s",stud.nume);
    fflush(stdin);
    printf("Prenume:");
    scanf("%s",stud.prenume);
    fflush(stdin);

    int i;
    for(i=0;i<5;i++)
    {
        printf("%d.Nota:",i+1);
        scanf("%lf",&stud.note[i]);
        fflush(stdin);
    }

    dimensiune=dimensiune+1;
    vector=realloc(vector,dimensiune);
    
    for(i=dimensiune;i>poz;i--)
            {
                *(vector+i)=*(vector+(i-1));
            }

    *(vector+poz)=stud;        

    afisare(vector,dimensiune);

}

void inlocuire(struct student *s,int m,int np[4][5])
{
    int i,j;
    char n[6];

    printf("ID-ul studentului pe care doriti sa il inlocutiti.\n");
    scanf("%s",n);

    for(i=0;i<m;i++)
        if(strcmp((s+i)->id,n)==0)
            {
                generare_nume(s,i,np);
                generare_note(s,i);
                generare_id(s,i);
            } 

    afisare(s,m);

}


int main()
{
    struct student *s;
    int m;

    printf("Cati studenti doriti sa adaugati?\n");
    scanf("%d",&m);

    s=malloc(m*sizeof(struct student));

    int i=0,l,np[4][5]={0};

    srand(time(NULL));

    while(i<m && i<20)
    {
        (s+i)->nume=malloc(10*sizeof(char));
        (s+i)->prenume=malloc(10*sizeof(char));

        generare_nume(s,i,np);

        generare_note(s,i);

        generare_id(s,i);
       
        i++;
    }

    afisare(s,m);
   
    restante(s,m);

    stergere(s,m);

    adaugare(s,m,1);//adauga un student pe pozitia 1

    inlocuire(s,m,np);
    
    return 0;

}
