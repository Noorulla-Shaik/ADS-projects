//12. Implement Travelling Sales Person problem using Branch and Bound approach. 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#define MAX_CITIES 5  // Change this to the number of cities 
#define CITY_COUNT MAX_CITIES 
int cities[CITY_COUNT][CITY_COUNT] = { 
    {0, 10, 15, 20, 25}, 
    {10, 0, 35, 30, 24}, 
    {15, 35, 0, 28, 16}, 
    {20, 30, 28, 0, 14}, 
    {25, 24, 16, 14, 0} 
}; 
int minVal = INT_MAX; 
int visited[CITY_COUNT]; 
int level = 0; 
int curr_pathWeight = 0; 
int bestPath[CITY_COUNT]; 
void TSP_BranchAndBound(int curr_city) 
 { 
    if (level == CITY_COUNT) { 
        curr_pathWeight += cities[curr_city][0]; 
        if (curr_pathWeight < minVal) { 
            minVal = curr_pathWeight; 
            for (int i = 0; i < CITY_COUNT; i++) 
                bestPath[i] = visited[i]; 
            bestPath[level] = 0;  // Close the tour 
        } 
        curr_pathWeight -= cities[curr_city][0]; 
        return; 
    } 
    for (int i = 0; i < CITY_COUNT; i++) 
 { 
        if (visited[i] == 0 && cities[curr_city][i] != 0)  
{ 
            visited[i] = 1; 
            level++; 
            curr_pathWeight += cities[curr_city][i]; 
            TSP_BranchAndBound(i); 
            level--; 
            visited[i] = 0; 
            curr_pathWeight -= cities[curr_city][i]; 
        } 
    } 
} 
int main() 
 { 
    visited[0] = 1; 
    TSP_BranchAndBound(0); 
    printf("Minimum cost path: "); 
    for (int i = 0; i <= CITY_COUNT; i++) 
        printf("%d ", bestPath[i]); 
    printf("\nMinimum cost: %d\n", minVal); 
    return 0; 
}