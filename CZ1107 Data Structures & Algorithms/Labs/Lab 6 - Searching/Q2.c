#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quickSort(int A[], int low, int high);
int partition(int A[], int low, int high);

void dualSortedSearch(int[], int, int, int[]);

int main()
{
    int i, size, K;
    int *A;
    int index[2] = {-1, -1};

    //Search key
    printf("input K: ");
    scanf("%d", &K);

    //create an array
    printf("input array size: ");
    scanf("%d", &size);
    A = (int *)malloc(sizeof(int) * size);
    printf("input array elements: ");
    for (i = 0; i < size; i++)
    {
        scanf("%d", &A[i]);
    }

    quickSort(A, 0, size - 1);

    // dual search
    clock_t begin = clock();
    dualSortedSearch(A, size, K, index);
    clock_t end = clock();
    double runtime = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Program run time: %f\n", runtime);

    if (index[0] != -1)
        printf("%d %d\n", index[0], index[1]);
    else
        printf("Not found");

    free(A);
    return 0;
}

void dualSortedSearch(int A[], int size, int K, int dualIndex[])
{
    // start with smallest and largest number
    int a = 0, b = size - 1, sum;

    // loop until the smaller number surpasses the larger number
    while (a < b) {
        sum = A[a] + A[b];

        if (sum == K) {
            dualIndex[0] = A[a];
            dualIndex[1] = A[b];
            return;
        }
        else if (sum < K)
            a++;
        else
            b--;
    }
}

int partition(int A[], int low, int high)
{
    int pivot = A[high];
    int i = (low - 1);

    int temp;
    for (int j = low; j <= high - 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;
    return (i + 1);
}

void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);

        quickSort(A, low, pivot - 1);
        quickSort(A, pivot + 1, high);
    }
}
