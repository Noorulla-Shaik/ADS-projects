//8. Implement Job Sequencing with deadlines using Greedy strategy.
 #include <stdio.h> 
#include <stdlib.h> 
// A structure to represent a job 
typedef struct Job 
 { 
    char id;     // Job Id 
    int deadline; // Deadline of job 
    int profit;  // Profit if job is completed before or on deadline 
} Job; 
// Function to compare two jobs according to their profit 
int compare(const void *a, const void *b)  
{ 
    Job *job1 = (Job *)a; 
    Job *job2 = (Job *)b; 
    return (job2->profit - job1->profit); 
} 
 
// Function to find the maximum deadline in the job list 
int findMaxDeadline(Job jobs[], int n)  
{ 
    int max = jobs[0].deadline; 
    for (int i = 1; i < n; i++) 
 { 
        if (jobs[i].deadline > max) 
 { 
            max = jobs[i].deadline; 
        } 
    } 
    return max; 
} 
// Function to schedule jobs to maximize profit 
void jobSequencing(Job jobs[ ], int n)  
{ 
    // Sort jobs in descending order of profit 
    qsort(jobs, n, sizeof(Job), compare); 
 
    // Find the maximum deadline 
    int maxDeadline = findMaxDeadline(jobs, n); 
 
    // Create an array to keep track of free time slots 
    int slot[maxDeadline + 1]; 
    for (int i = 0; i <= maxDeadline; i++)  
{ 
        slot[i] = -1; // Initialize all slots to be free 
    } 
 
    // Iterate through all given jobs 
    for (int i = 0; i < n; i++)  
{ 
        // Find a free slot for this job (starting from the last possible slot) 
        for (int j = jobs[i].deadline; j > 0; j--)  
{ 
            if (slot[j] == -1) 
 { 
                slot[j] = i; // Assign this job to the free slot 
                break; 
            } 
        } 
    } 
 
    // Print the scheduled jobs 
    printf("Scheduled jobs:\n"); 
    for (int i = 1; i <= maxDeadline; i++)  
{ 
        if (slot[i] != -1) 
 { 
            printf("%c ", jobs[slot[i]].id); 
        } 
    } 
    printf("\n"); 
} 
 
int main() { 
    Job jobs[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15} }; 
    int n = sizeof(jobs) / sizeof(jobs[0]); 
 
    jobSequencing(jobs, n); 
 
    return 0; 
}