#include <stdio.h> 
#include <stdlib.h> 
#define MAX 4 
#define MIN 2 
struct BTreeNode { 
    int keys[MAX + 1], count; 
    struct BTreeNode *children[MAX + 1]; 
}; 
 
struct BTreeNode *root; 
// Function prototypes 
struct BTreeNode *createNode(int key, struct BTreeNode *child); 
void insert(int key); 
void insertNode(int key, int pos, struct BTreeNode *node, struct BTreeNode *child); 
void splitNode(int key, int *pval, int pos, struct BTreeNode *node, struct BTreeNode 
*child, struct BTreeNode **newNode); 
int setValue(int key, int *pval, struct BTreeNode *node, struct BTreeNode **child); 
void search(int key); 
void deletion(int key); 
void removeVal(struct BTreeNode *node, int pos); 
void doRightShift(struct BTreeNode *node, int pos); 
void doLeftShift(struct BTreeNode *node, int pos); 
void mergeNodes(struct BTreeNode *node, int pos); 
void adjustNode(struct BTreeNode *node, int pos); 
int predecessor(struct BTreeNode *node); 
int successor(struct BTreeNode *node); 
void traversal(struct BTreeNode *node); 
 
int main() { 
    int i, r, num; 
    int array[100]; 
 
    // Generating 100 random elements 
    srand(time(NULL)); 
    for (i = 0; i < 100; i++) { 
        array[i] = rand() % 1000; 
        insert(array[i]); 
    } 
    printf("B-Tree of order 5 constructed with 100 random elements:\n"); 
    traversal(root); 
    printf("\n"); 
    // Searching 
    printf("Enter element to search: "); 
    scanf("%d", &num); 
    search(num); 
    // Deletion 
    printf("Enter element to delete: "); 
    scanf("%d", &num); 
    deletion(num); 
    printf("B-Tree after deletion:\n"); 
    traversal(root); 
    printf("\n"); 
    return 0; 
} 
struct BTreeNode *createNode(int key, struct BTreeNode *child) { 
    struct BTreeNode *newNode; 
    newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode)); 
    newNode->keys[1] = key; 
    newNode->count = 1; 
    newNode->children[0] = root; 
    newNode->children[1] = child; 
    return newNode; 
} 
void insert(int key) { 
    int flag, i; 
    struct BTreeNode *child; 
 
    flag = setValue(key, &i, root, &child); 
    if (flag) 
        root = createNode(i, child); 
} 
void insertNode(int key, int pos, struct BTreeNode *node, struct BTreeNode *child) { 
    int j = node->count; 
    while (j > pos) { 
        node->keys[j + 1] = node->keys[j]; 
        node->children[j + 1] = node->children[j]; 
        j--; 
    } 
    node->keys[j + 1] = key; 
    node->children[j + 1] = child; 
    node->count++; 
} 
 
void splitNode(int key, int *pval, int pos, struct BTreeNode *node, struct BTreeNode 
*child, struct BTreeNode **newNode) { 
    int median, j; 
    if (pos > MIN) 
        median = MIN + 1; 
    else 
        median = MIN; 
    *newNode = (struct BTreeNode *)malloc(sizeof(struct BTreeNode)); 
    j = median + 1; 
    while (j <= MAX) { 
        (*newNode)->keys[j - median] = node->keys[j]; 
        (*newNode)->children[j - median] = node->children[j]; 
        j++; 
    } 
    node->count = median; 
    (*newNode)->count = MAX - median; 
 
    if (pos <= MIN) 
        insertNode(key, pos, node, child); 
    else 
        insertNode(key, pos - median, *newNode, child); 
 
    *pval = node->keys[node->count]; 
    (*newNode)->children[0] = node->children[node->count]; 
    node->count--; 
} 
int setValue(int key, int *pval, struct BTreeNode *node, struct BTreeNode **child) { 
    int pos; 
    if (!node) { 
        *pval = key; 
        *child = NULL; 
        return 1; 
    } 
 
    if (key < node->keys[1]) { 
        pos = 0; 
    } else { 
        for (pos = node->count; (key < node->keys[pos] && pos > 1); pos--); 
        if (key == node->keys[pos]) { 
            printf("Duplicates not allowed\n"); 
            return 0; 
        } 
    } 
    if (setValue(key, pval, node->children[pos], child)) { 
        if (node->count < MAX) { 
            insertNode(*pval, pos, node, *child); 
            return 0; 
        } else { 
            splitNode(*pval, pval, pos, node, *child, child); 
            return 1; 
        } 
    } 
    return 0; 
} 
void search(int key) { 
    int pos, flag = 0; 
    struct BTreeNode *node = root; 
 
    while (node) { 
        for (pos = 0; pos < node->count && key > node->keys[pos + 1]; pos++); 
        if (pos <= node->count && key == node->keys[pos + 1]) { 
            printf("Element %d found in the B-Tree\n", key); 
            flag = 1; 
            break; 
        } 
        node = node->children[pos]; 
    } 
    if (!flag) 
        printf("Element %d not found in the B-Tree\n", key); 
} 
void deletion(int key) { 
    struct BTreeNode *node = root; 
    struct BTreeNode *temp; 
    int pos, flag = 0; 
 
    while (node) { 
        for (pos = 0; pos < node->count && key > node->keys[pos + 1]; pos++); 
        if (pos <= node->count && key == node->keys[pos + 1]) { 
            flag = 1; 
            break; 
        } 
        node = node->children[pos]; 
    } 
 
    if (flag) { 
        printf("Element %d deleted from the B-Tree\n", key); 
        removeVal(root, pos); 
    } else { 
        printf("Element %d not found in the B-Tree\n", key); 
    } 
 
    if (root->count == 0) { 
        temp = root; 
        root = root->children[0]; 
        free(temp); 
    } 
} 
 
void removeVal(struct BTreeNode *node, int pos) { 
    int i; 
    struct BTreeNode *temp; 
 
    if (node->children[pos - 1]) { 
        temp = node->children[pos]; 
        node->keys[pos] = predecessor(node); 
        removeVal(node->children[pos], node->count); 
    } else { 
        for (i = pos + 1; i <= node->count; i++) { 
            node->keys[i - 1] = node->keys[i]; 
            node->children[i - 1] = node->children[i]; 
        } 
        node->count--; 
    } 
} 
 
int predecessor(struct BTreeNode *node) { 
    while (node->children[node->count]) 
        node = node->children[node->count]; 
    return node->keys[node->count]; 
} 
 
int successor(struct BTreeNode *node) { 
    while (node->children[0]) 
        node = node->children[0]; 
    return node->keys[1]; 
} 
void traversal(struct BTreeNode *node) { 
    int i; 
    if (node) { 
        for (i = 0; i < node->count; i++) { 
            traversal(node->children[i]); 
            printf("%d ", node->keys[i + 1]); 
        } 
        traversal(node->children[i]); 
    } 
} 