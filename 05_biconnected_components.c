// 5.Write A Program For Finding Biconnected Components In A Given Graph 
#include <stdio.h> 
#include <stdlib.h> 
#define MAX 100 
// Stack structure 
typedef struct { 
    int data[MAX]; 
    int top; 
} Stack; 
void initStack(Stack *s)  
{ 
    s->top = -1; 
} 
void push(Stack *s, int item) 
 { 
    if (s->top < MAX - 1) { 
        s->data[++(s->top)] = item; 
    } else { 
        printf("Stack overflow\n"); 
    } 
} 
int pop(Stack *s) { 
    if (s->top >= 0) { 
        return s->data[(s->top)--]; 
    } else { 
        printf("Stack underflow\n"); 
        return -1; 
    } 
} 
int isStackEmpty(Stack *s) { 
    return s->top == -1; 
} 
void printBiconnectedComponent(Stack *st, int u, int v) { 
    int w; 
    printf("Biconnected Component: "); 
    do { 
        w = pop(st); 
        printf("%d ", w); 
    } while (w != u && w != v); 
    printf("\n"); 
} 
void DFS(int u, int disc[], int low[], int parent[], int graph[MAX][MAX], int n, Stack *st, int 
*time) 
 { 
    static int timeCounter = 0; 
    disc[u] = low[u] = ++timeCounter; 
    int children = 0; 
 
    for (int v = 0; v < n; v++) { 
        if (graph[u][v]) { // If v is adjacent to u 
            if (disc[v] == -1) { // v is not visited 
                children++; 
                parent[v] = u; 
                push(st, u); 
                push(st, v); 
                DFS(v, disc, low, parent, graph, n, st, time); 
        // Check if the subtree rooted at v has a connection back to one of the ancestors of u 
                low[u] = (low[u] < low[v]) ? low[u] : low[v]; 
 
                // If u is an articulation point 
                if ((disc[u] == 1 && children > 1) || (disc[u] != 1 && low[v] >= disc[u])) { 
                    printBiconnectedComponent(st, u, v); 
                } 
            }  
else if (v != parent[u] && disc[v] < disc[u])  
{ 
 // Update low value of u for parent function calls 
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v]; 
                push(st, u); 
                push(st, v); 
            } 
        } 
    } 
} 
void findBiconnectedComponents(int graph[MAX][MAX], int n) { 
    int disc[MAX], low[MAX], parent[MAX]; 
    Stack st; 
    initStack(&st); 
    int time = 0; 
    for (int i = 0; i < n; i++) { 
        disc[i] = -1; 
        low[i] = -1; 
        parent[i] = -1; 
    } 
 
    for (int i = 0; i < n; i++) 
 { 
        if (disc[i] == -1) 
 { 
            DFS(i, disc, low, parent, graph, n, &st, &time); 
            // If stack is not empty, pop all remaining edges 
            while (!isStackEmpty(&st))  
{ 
                int v = pop(&st); 
                int u = pop(&st); 
                printBiconnectedComponent(&st, u, v); 
            } 
        } 
    } 
} 
int main() 
 { 
    int n, e; 
    int graph[MAX][MAX] = {0}; 
    printf("Enter number of vertices: "); 
    scanf("%d", &n); 
 
    printf("Enter number of edges: "); 
    scanf("%d", &e); 
    printf("Enter edges (u v) format:\n"); 
    for (int i = 0; i < e; i++) { 
        int u, v; 
        scanf("%d %d", &u, &v); 
        graph[u][v] = 1; 
        graph[v][u] = 1; 
    } 
    findBiconnectedComponents(graph, n); 
    return 0; 
}