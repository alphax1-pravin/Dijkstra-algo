#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct AdjListNode {
int dest, weight;
struct AdjListNode* next;
};
struct Graph {
int V;
struct AdjListNode** array;
};
struct AdjListNode* newNode(int dest, int weight) {
struct AdjListNode* node = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
node->dest = dest;
node->weight = weight;
node->next = NULL;
return node;
}
struct Graph* createGraph(int V) {
struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
graph->V = V;
graph->array = (struct AdjListNode**)malloc(V * sizeof(struct AdjListNode*));
for (int i = 0; i < V; i++)
graph->array[i] = NULL;
return graph;
}
void addEdge(struct Graph* graph, int src, int dest, int weight) {
struct AdjListNode* node = newNode(dest, weight);
node->next = graph->array[src];
graph->array[src] = node;
}
struct MinHeapNode {
int v, key;
};
struct MinHeap {
int size, capacity;
int* pos;
struct MinHeapNode** array;
};
struct MinHeapNode* newMinHeapNode(int v, int key) {
struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
node->v = v;
node->key = key;
return node;
}
struct MinHeap* createMinHeap(int capacity) {
struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
heap->pos = (int*)malloc(capacity * sizeof(int));
heap->size = 0;
heap->capacity = capacity;
heap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
return heap;
}
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
struct MinHeapNode* t = *a;
*a = *b;
*b = t;
}
void minHeapify(struct MinHeap* heap, int idx) {
int smallest = idx;
int left = 2 * idx + 1;
int right = 2 * idx + 2;
if (left < heap->size && heap->array[left]->key < heap->array[smallest]->key)
smallest = left;
if (right < heap->size && heap->array[right]->key < heap->array[smallest]->key)
smallest = right;
if (smallest != idx) {
struct MinHeapNode* smallestNode = heap->array[smallest];
struct MinHeapNode* idxNode = heap->array[idx];
heap->pos[smallestNode->v] = idx;
heap->pos[idxNode->v] = smallest;
swapMinHeapNode(&heap->array[smallest], &heap->array[idx]);
minHeapify(heap, smallest);
}
}
int isEmpty(struct MinHeap* heap) {
return heap->size == 0;
}
struct MinHeapNode* extractMin(struct MinHeap* heap) {
if (isEmpty(heap))
return NULL;
struct MinHeapNode* root = heap->array[0];
struct MinHeapNode* lastNode = heap->array[heap->size - 1];
heap->array[0] = lastNode;
heap->pos[root->v] = heap->size - 1;
heap->pos[lastNode->v] = 0;
heap->size--;
minHeapify(heap, 0);
return root;
}
void decreaseKey(struct MinHeap* heap, int v, int key) {
int i = heap->pos[v];
heap->array[i]->key = key;
while (i && heap->array[i]->key < heap->array[(i - 1) / 2]->key) {
heap->pos[heap->array[i]->v] = (i - 1) / 2;
heap->pos[heap->array[(i - 1) / 2]->v] = i;
swapMinHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
i = (i - 1) / 2;
}
}
int isInMinHeap(struct MinHeap* heap, int v) {
return heap->pos[v] < heap->size;
}
void dijkstra(struct Graph* graph, int src) {
int V = graph->V;
int* dist = (int*)malloc(V * sizeof(int));
int* parent = (int*)malloc(V * sizeof(int));
struct MinHeap* heap = createMinHeap(V);
for (int v = 0; v < V; v++) {
dist[v] = INT_MAX;
parent[v] = -1;
heap->array[v] = newMinHeapNode(v, dist[v]);
heap->pos[v] = v;
}
dist[src] = 0;
heap->array[src]->key = 0;
heap->size = V;
while (!isEmpty(heap)) {
struct MinHeapNode* minNode = extractMin(heap);
int u = minNode->v;
struct AdjListNode* temp = graph->array[u];
while (temp != NULL) {
int v = temp->dest;
if (isInMinHeap(heap, v) &&
dist[u] != INT_MAX &&
temp->weight + dist[u] < dist[v]) {
dist[v] = dist[u] + temp->weight;
parent[v] = u;
decreaseKey(heap, v, dist[v]);
}
temp = temp->next;
}
}
printf("Vertex\tDistance\tParent\n");
for (int i = 0; i < V; i++)
printf("%d\t%d\t\t%d\n", i, dist[i], parent[i]);
}
int main() {
struct Graph* graph = createGraph(5);
addEdge(graph, 0, 1, 10);
addEdge(graph, 0, 3, 5);
addEdge(graph, 1, 2, 1);
addEdge(graph, 1, 3, 2);
addEdge(graph, 2, 4, 4);
addEdge(graph, 3, 1, 3);
addEdge(graph, 3, 2, 9);
addEdge(graph, 3, 4, 2);
addEdge(graph, 4, 0, 7);
addEdge(graph, 4, 2, 6);
dijkstra(graph, 0); // source = s
return 0;