 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
int totalComparisons = 0;
int permutationCount = 0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high, int *comparisons)
{
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++)
    {
        (*comparisons)++;
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
int randomizedPartition(int arr[],int low,int high,int *comparisons)
{
    int randomIndex =
    low + rand() % (high - low + 1);
    swap(&arr[randomIndex], &arr[high]);
    return partition(arr,low,high,comparisons);
}

void quickSort(int arr[],int low,int high,int *comparisons)
{
    if(low < high)
    {
        int pi = randomizedPartition(arr,low,high,comparisons);
        quickSort(arr,low,pi - 1,comparisons);
        quickSort(arr,pi + 1,high,comparisons);
    }
}
void printArray(FILE *fp, int arr[], int n)
{
    for(int i = 0; i < n; i++)
        fprintf(fp, "%d ", arr[i]);
    fprintf(fp, "\n");
}
void permute(int arr[], int l,int r,int n, FILE *fp)
{
    if(l == r)
    {
        int temp[20];
        for(int i = 0; i < n; i++)
            temp[i] = arr[i];
        fprintf(fp, "Permutation: ");
        printArray(fp, temp, n);
        int comparisons = 0;
        quickSort(temp,0,n - 1,&comparisons);
        fprintf(fp, "Sorted:      ");
        printArray(fp, temp, n);
        fprintf(fp,"Comparisons = %d\n",comparisons);
        fprintf(fp,"----------------------\n");
        totalComparisons += comparisons;
        permutationCount++;
        return;
    }
    for(int i = l; i <= r; i++)
    {
        swap(&arr[l], &arr[i]);
        permute(arr,l + 1,r,n,fp);
        swap(&arr[l], &arr[i]);
    }
}
int main()
{
    srand(time(NULL));
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[20];
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    FILE *fp = fopen("output.txt", "w");
    if(fp == NULL)
    {
        printf("File cannot open!\n");
        return 1;
    }
    permute(arr,0,n - 1,n,fp);
    double average =
    (double)totalComparisons /
    permutationCount;
    fprintf(fp,"\nTotal permutations = %d\n",permutationCount);
    fprintf(fp,"Total comparisons = %d\n",totalComparisons);
    fprintf(fp,"Average comparisons = %.2lf\n",average);
    fclose(fp);
    printf("\nOutput stored in output.txt\n");
    return 0;
}