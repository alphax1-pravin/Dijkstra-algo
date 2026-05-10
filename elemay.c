#include <stdio.h>
#include <limits.h>

int matrixChainOrder(int p[], int n)
{
    int m[n][n];

    // Cost is 0 when multiplying one matrix
    for(int i = 1; i < n; i++)
        m[i][i] = 0;

    // L = chain length
    for(int L = 2; L < n; L++)
    {
        for(int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for(int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k+1][j]
                        + p[i-1] * p[k] * p[j];

                if(q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n-1];
}

int main()
{
    int p[] = {13, 5, 89, 3, 34};

    int n = sizeof(p)/sizeof(p[0]);

    printf("Minimum multiplications = %d\n",
            matrixChainOrder(p, n));

    return 0;
}