#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dualSearch(int[], int, int, int[]);

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

    printf("K: %d, arr size: %d, 3rd: %d", K, size, A[2]);

    // dual search
    clock_t begin = clock();
    dualSearch(A, size, K, index);
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

void dualSearch(int A[], int size, int K, int dualIndex[])
{
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (A[i] + A[j] == K) {
                dualIndex[0] = i;
                dualIndex[1] = j;
                return;
            }
        }
    }
}
