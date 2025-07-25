///11.Use Backtracking strategy to solve 0/1 Knapsack problem.
#include <stdio.h> 
#define MAX_ITEMS 100 
 int maxProfit = 0; 
 int currentWeight = 0; 
 int currentProfit = 0; 
 int bestSet[MAX_ITEMS]; 
 int include[MAX_ITEMS]; 
void knapsack(int i, int profit, int weight, int capacity, int n, int weights[], int values[]) 
{ 
    if (weight <= capacity && profit > maxProfit)  
{ 
        maxProfit = profit; 
        for (int j = 0; j < n; j++)  
{ 
            bestSet[j] = include[j]; 
        } 
    } 
    if (i < n)  
{ 
        include[i] = 1; 
      knapsack(i + 1, profit + values[i], weight + weights[i], capacity, n, weights, values); 
        include[i] = 0; 
        knapsack(i + 1, profit, weight, capacity, n, weights, values); 
    } 
} 
int main()  
{ 
    int weights[] = {10, 20, 30}; 
    int values[] = {60, 100, 120}; 
    int capacity = 50; 
    int n = sizeof(values) / sizeof(values[0]); 
    knapsack(0, 0, 0, capacity, n, weights, values); 
    printf("Maximum profit: %d\n", maxProfit); 
    printf("Selected items:\n"); 
    for (int i = 0; i < n; i++)  
{ 
        if (bestSet[i]) 
 { 
            printf("Item %d (weight: %d, value: %d)\n", i + 1, weights[i], values[i]); 
        } 
    } 
    return 0; 
}