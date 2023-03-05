int nrq,nri;

struct moment;

void print(int *arr,int dim);

void printchar(char s[10][5],int dim);

void printstruct(struct moment *t,int dim);

void merge(int *arr, int left, int middle, int right);

void mergesort(int *arr, int left, int right);

void selectionsort(int *arr,int dim);

void selectionsort_char(char s[10][5],int dim);

void countingSort(int *arr, int dim, int ex);

void radixsort(int *arr,int dim);