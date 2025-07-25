//9. Write a program to solve 0/1 Knapsack problem Using Dynamic Programming.  another name
#include <stdio.h> 
int max(int a, int b) { 
    return (a > b) ? a : b; 
} 
void knapsack(int W, int n, int weights[], int values[])  
{ 
    int i, w; 
    int K[n + 1][W + 1]; 
    // Build table K[][] in a bottom-up manner 
    for (i = 0; i <= n; i++) 
     { 
        for (w = 0; w <= W; w++) 
          { 
            if (i == 0 || w == 0)  
         { 
                K[i][w] = 0; 
            }  
else if (weights[i - 1] <= w) 
     { 
                K[i][w] = max(values[i - 1] + K[i - 1][w - weights[i - 1]], K[i - 1][w]); 
            } 
 
 else  
{ 
 K[i][w] = K[i - 1][w]; 
            } 
       } 
    } 
    // Print the result 
    printf("Maximum value in Knapsack: %d\n", K[n][W]); 
    // Print the selected items 
    printf("Selected items:\n"); 
    w = W; 
    for (i = n; i > 0 && w > 0; i--)  
{ 
        if (K[i][w] != K[i - 1][w]) 
{ 
            printf("Item %d (weight: %d, value: %d)\n", i, weights[i - 1], values[i - 1]); 
            w -= weights[i - 1]; 
        } 
    } 
} 
int main() { 
    int weights[] = {10, 20, 30}; 
    int values[] = {60, 100, 120}; 
    int W = 50; 
    int n = sizeof(values) / sizeof(values[0]); 
    knapsack(W, n, weights, values); 
    return 0; 
}