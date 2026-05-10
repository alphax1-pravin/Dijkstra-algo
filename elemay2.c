#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalComparisons = 0;
int permutationCount = 0;

// Swap function
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Swap for integers
void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quick Sort Partition
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
            swapInt(&arr[i], &arr[j]);
        }
    }

    swapInt(&arr[i + 1], &arr[high]);

    return i + 1;
}

// Quick Sort
void quickSort(int arr[], int low, int high, int *comparisons)
{
    if(low < high)
    {
        int pi = partition(arr, low, high, comparisons);

        quickSort(arr, low, pi - 1, comparisons);
        quickSort(arr, pi + 1, high, comparisons);
    }
}

// Print integer array to file
void printArray(FILE *fp, int arr[], int n)
{
    for(int i = 0; i < n; i++)
        fprintf(fp, "%d", arr[i]);

    fprintf(fp, "\n");
}

// Process each permutation
void processPermutation(char str[], int n, FILE *fp)
{
    int arr[20];

    // Convert char array to int array
    for(int i = 0; i < n; i++)
        arr[i] = str[i] - '0';

    fprintf(fp, "Permutation: ");
    printArray(fp, arr, n);

    int comparisons = 0;

    quickSort(arr, 0, n - 1, &comparisons);

    fprintf(fp, "Sorted:      ");
    printArray(fp, arr, n);

    fprintf(fp, "Comparisons = %d\n", comparisons);
    fprintf(fp, "--------------------------\n");

    totalComparisons += comparisons;
    permutationCount++;
}

// Generate permutations
void permute(char str[], int l, int r, FILE *fp)
{
    if(l == r)
    {
        processPermutation(str, r + 1, fp);
        return;
    }

    for(int i = l; i <= r; i++)
    {
        swap(&str[l], &str[i]);

        permute(str, l + 1, r, fp);

        // Backtracking
        swap(&str[l], &str[i]);
    }
}

int main()
{
    char str[20];

    printf("Enter digits without space: ");
    scanf("%s", str);

    int n = strlen(str);

    FILE *fp = fopen("output.txt", "w");

    if(fp == NULL)
    {
        printf("File cannot open!\n");
        return 1;
    }

    fprintf(fp, "QUICK SORT COMPARISON FOR ALL PERMUTATIONS\n");
    fprintf(fp, "==========================================\n\n");

    permute(str, 0, n - 1, fp);

    double average = (double)totalComparisons / permutationCount;

    fprintf(fp, "\nTotal permutations = %d\n", permutationCount);
    fprintf(fp, "Total comparisons = %d\n", totalComparisons);
    fprintf(fp, "Average comparisons = %.2lf\n", average);

    fclose(fp);

    printf("\nOutput stored in output.txt\n");

    return 0;
}