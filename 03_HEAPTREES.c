#include <stdio.h> 
#include <stdlib.h> 
 
#define MAX_SIZE 100 
 
void swap(int *a, int *b) 
 { 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
 
// Min Heap functions 
void minHeapify(int arr[], int n, int i) { 
    int smallest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 
 
    if (left < n && arr[left] < arr[smallest]) 
        smallest = left; 
 
    if (right < n && arr[right] < arr[smallest]) 
        smallest = right; 
 
    if (smallest != i) { 
        swap(&arr[i], &arr[smallest]); 
        minHeapify(arr, n, smallest); 
    } 
} 
 
void buildMinHeap(int arr[], int n) 
 { 
    int i; 
    for (i= n / 2 - 1;i>=0;i--) 
        minHeapify(arr, n, i); 
} 
 
void deleteMinHeapElement(int arr[], int *n, int value) { 
    int i; 
    for (i = 0; i < *n; i++) { 
        if (arr[i] == value) 
            break; 
    } 
 
    if (i == *n) { 
        printf("Element not found in Min Heap\n"); 
        return; 
    } 
 
    arr[i] = arr[*n - 1]; 
    (*n)--; 
    buildMinHeap(arr, *n); 
} 
 
// Max Heap functions 
void maxHeapify(int arr[], int n, int i) { 
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 
 
    if (left < n && arr[left] > arr[largest]) 
        largest = left; 
 
    if (right < n && arr[right] > arr[largest]) 
        largest = right; 
 
    if (largest != i) { 
        swap(&arr[i], &arr[largest]); 
        maxHeapify(arr, n, largest); 
    } 
} 
 
void buildMaxHeap(int arr[], int n) 
 { int i; 
    for (i = n / 2 - 1; i >= 0; i--) 
        maxHeapify(arr, n, i); 
} 
 
void deleteMaxHeapElement(int arr[], int *n, int value) { 
    int i; 
    for (i = 0; i < *n; i++) { 
        if (arr[i] == value) 
            break; 
    } 
 
    if (i == *n) { 
        printf("Element not found in Max Heap\n"); 
        return; 
    } 
 
    arr[i] = arr[*n - 1]; 
    (*n)--; 
    buildMaxHeap(arr, *n); 
} 
 
void displayHeap(int arr[], int n) 
 { int i; 
    for (i= 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
 
int main() { 
    int minHeap[MAX_SIZE], maxHeap[MAX_SIZE]; 
    int n, i, value; 
 
    printf("Enter number of elements: "); 
    scanf("%d", &n); 
 
    printf("Enter elements: "); 
    for (i = 0; i < n; i++) { 
        scanf("%d", &minHeap[i]); 
        maxHeap[i] = minHeap[i]; 
    } 
 
    buildMinHeap(minHeap, n); 
    buildMaxHeap(maxHeap, n); 
 
    printf("Min Heap: "); 
    displayHeap(minHeap, n); 
 
    printf("Max Heap: "); 
    displayHeap(maxHeap, n); 
 
    printf("Enter element to delete: "); 
    scanf("%d", &value); 
 
    deleteMinHeapElement(minHeap, &n, value); 
    deleteMaxHeapElement(maxHeap, &n, value); 
 
    printf("Min Heap after deletion: "); 
    displayHeap(minHeap, n); 
 
    printf("Max Heap after deletion: "); 
    displayHeap(maxHeap, n); 
 
    return 0; 
} 