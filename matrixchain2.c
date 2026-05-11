#include <stdio.h>
#include <limits.h>

void printOptimalParens(int s[][5], int i, int j)
{
    if (i == j)
        printf("M%d", i);
    else
    {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

int matrixChainOrder(int p[], int n, int s[][5])
{
    int m[n][n];
    
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    
    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    // Print cost table
    printf("\nCost Table (m[i][j]):\n");
    printf("      ");
    for (int j = 1; j <= 4; j++)
        printf("M%d     ", j);
    printf("\n");
    for (int i = 1; i <= 4; i++)
    {
        printf("M%d   ", i);
        for (int j = 1; j <= 4; j++)
        {
            if (j >= i)
                printf("%-6d ", m[i][j]);
            else
                printf("       ");
        }
        printf("\n");
    }
    
    return m[1][n - 1];
}

int main()
{
    int p[] = {13, 5, 89, 3, 34};
    int n = sizeof(p) / sizeof(p[0]);
    int s[5][5];
    
    printf("Matrix Chain: M1(13x5), M2(5x89), M3(89x3), M4(3x34)\n");
    
    int minMultiplications = matrixChainOrder(p, n, s);
    
    printf("\nMinimum scalar multiplications: %d\n", minMultiplications);
    printf("Optimal Parenthesization: ");
    printOptimalParens(s, 1, n - 1);
    printf("\n");
    
    return 0;
}