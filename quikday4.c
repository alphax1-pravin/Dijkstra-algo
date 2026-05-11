#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b) {
int t = *a;
*a = *b;
*b = t;
}
int partition(int arr[], int low, int high, long long *comp) {
int pivot = arr[high];
int i = low - 1;
for (int j = low; j < high; j++) {
(*comp)++;
if (arr[j] < pivot) {
i++;
swap(&arr[i], &arr[j]);
}
}
swap(&arr[i + 1], &arr[high]);
return i + 1;
}
void quickSort(int arr[], int low, int high, long long *comp) {
if (low < high) {
int pi = partition(arr, low, high, comp);
quickSort(arr, low, pi - 1, comp);
quickSort(arr, pi + 1, high, comp);
}
}
void generateInputFile(int m, int n) {
FILE *fp = fopen("input1.txt", "w");
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++) {
fprintf(fp, "%d ", rand() % 100);
}
fprintf(fp, "\n");
}
fclose(fp);
}
void processFile(int m, int n) {
FILE *in = fopen("input1.txt", "r");
FILE *out = fopen("output1.txt", "w");
long long total = 0;
for (int i = 0; i < m; i++) {
int arr[n];
long long comp = 0;
for (int j = 0; j < n; j++) {
fscanf(in, "%d", &arr[j]);
}
quickSort(arr, 0, n - 1, &comp);
fprintf(out, "Sorted Array %d: ", i + 1);
for (int j = 0; j < n; j++) {
fprintf(out, "%d ", arr[j]);
}
fprintf(out, "\nComparisons: %lld\n\n", comp);
total += comp;
}
fprintf(out, "Total Comparisons: %lld\n", total);
fprintf(out, "Average Comparisons: %.2lf\n", (double)total / m);
fclose(in);
fclose(out);
printf("Check output1.txt\n");
}
int main() {
srand(time(NULL));
int m, n;
printf("Enter number of arrays (m): ");
scanf("%d", &m);
printf("Enter number of elements (n): ");
scanf("%d", &n);
generateInputFile(m, n);
processFile(m, n);
return 0;
}