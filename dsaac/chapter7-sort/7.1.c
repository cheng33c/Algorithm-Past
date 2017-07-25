#include <stdio.h>

typedef int ElementType;

void InsertionSort(ElementType A[], int N)
{
  int j;
  ElementType tmp;

  for (int i = 1; i < N; i++) {
    tmp = A[i];
    for (j = i; j > 0 && A[j - 1] > tmp; j--)
      A[j] = A[j-1];
    A[j] = tmp;
  }
}

int main()
{
  int A[9] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
  InsertionSort(A, 9);

  for (int i = 0; i < 9; i++)
    printf("%d ", A[i]);

  return 0;
}
