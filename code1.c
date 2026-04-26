#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 5 // s,t,x,y,z
// Adjacency List Node
struct Node {
 int dest, weight;
 struct Node* next;
};
// Graph
struct Graph {
 struct Node* head[V];
};
// Min Heap Node
struct HeapNode {
 int v, dist;
};
// Min Heap
struct MinHeap {
 int size;
 int pos[V];
 struct HeapNode* array[V];
};
// Create Graph
struct Graph* createGraph() {
 struct Graph* graph = malloc(sizeof(struct Graph));
 for (int i = 0; i < V; i++)
 graph->head[i] = NULL;
 return graph;
}
// Add Edge (Directed)
void addEdge(struct Graph* graph, int src, int dest, int weight) {
 struct Node* newNode = malloc(sizeof(struct Node));
 newNode->dest = dest;
 newNode->weight = weight;
 newNode->next = graph->head[src];
 graph->head[src] = newNode;
}
// Swap
void swap(struct HeapNode** a, struct HeapNode** b) {
 struct HeapNode* temp = *a;
 *a = *b;
 *b = temp;
}
// Heapify
void heapify(struct MinHeap* heap, int idx) {
 int smallest = idx, l = 2*idx+1, r = 2*idx+2;
 if (l < heap->size && heap->array[l]->dist < heap->array[smallest]->dist) smallest = l;
 if (r < heap->size && heap->array[r]->dist < heap->array[smallest]->dist)
 smallest = r;
 if (smallest != idx) {
 heap->pos[heap->array[smallest]->v] = idx;
 heap->pos[heap->array[idx]->v] = smallest;
 swap(&heap->array[smallest], &heap->array[idx]);
 heapify(heap, smallest);
 }
}
// Extract Min
struct HeapNode* extractMin(struct MinHeap* heap) {
 struct HeapNode* root = heap->array[0];
 struct HeapNode* last = heap->array[heap->size - 1];
 heap->array[0] = last;
 heap->pos[root->v] = heap->size - 1;
 heap->pos[last->v] = 0;
 heap->size--;
 heapify(heap, 0);
 return root;
}
// Decrease Key
void decreaseKey(struct MinHeap* heap, int v, int dist) {
 int i = heap->pos[v];
 heap->array[i]->dist = dist;
 while (i && heap->array[i]->dist < heap->array[(i-1)/2]->dist) {
 heap->pos[heap->array[i]->v] = (i-1)/2;
 heap->pos[heap->array[(i-1)/2]->v] = i;
 swap(&heap->array[i], &heap->array[(i-1)/2]);
 i = (i-1)/2;
 }
}
// Dijkstra
void dijkstra(struct Graph* graph, int src) {
 int dist[V];
 struct MinHeap* heap = malloc(sizeof(struct MinHeap));
 heap->size = V;
 for (int v = 0; v < V; v++) {
 dist[v] = INT_MAX;
 heap->array[v] = malloc(sizeof(struct HeapNode)); heap->array[v]->v = v;
 heap->array[v]->dist = dist[v];
 heap->pos[v] = v;
 }
 dist[src] = 0;
 heap->array[src]->dist = 0;
 while (heap->size > 0) {
 struct HeapNode* minNode = extractMin(heap);
 int u = minNode->v;
 struct Node* temp = graph->head[u];
 while (temp) {
 int v = temp->dest;
 if (dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
 dist[v] = dist[u] + temp->weight;
 decreaseKey(heap, v, dist[v]);
 }
 temp = temp->next;
 }
 }
 printf("Vertex Distance from Source\n");
 for (int i = 0; i < V; i++)
 printf("%d \t\t %d\n", i, dist[i]);
}
void printGraph(struct Graph* graph) {
 char name[] = {'s','t','x','y','z'};
 printf("Adjacency List:\n");
 for (int i = 0; i < V; i++) {
 printf("%c -> ", name[i]);
 struct Node* temp = graph->head[i];
 while (temp) {
 printf("(%c, w=%d) -> ", name[temp->dest], temp->weight);
 temp = temp->next;
 }
 printf("NULL\n");
 }
}
// Main
int main() {
 struct Graph* graph = createGraph();
 // s=0, t=1, x=2, y=3, z=4
 addEdge(graph, 0,1,10);
 addEdge(graph, 0,3,5); addEdge(graph, 1,2,1);
 addEdge(graph, 1,3,2);
 addEdge(graph, 2,4,4);
 addEdge(graph, 3,1,3);
 addEdge(graph, 3,2,9);
 addEdge(graph, 3,4,2);
 addEdge(graph, 4,0,7);
 addEdge(graph, 4,2,6);
 printGraph(graph); 
 dijkstra(graph, 0);
 return 0;
}