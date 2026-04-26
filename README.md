# Dijkstra's Algorithm in C

A clean implementation of **Dijkstra's Shortest Path Algorithm** using an **Adjacency List** and a **Min-Heap (Priority Queue)** in C.

## Graph (from CLRS)

Vertices: `s(0), t(1), x(2), y(3), z(4)`

Edges (directed, weighted):
| From | To | Weight |
|------|----|--------|
| s    | t  | 10     |
| s    | y  | 5      |
| t    | x  | 1      |
| t    | y  | 2      |
| x    | z  | 4      |
| y    | t  | 3      |
| y    | x  | 9      |
| y    | z  | 2      |
| z    | s  | 7      |
| z    | x  | 6      |

## How to Compile & Run

```bash
gcc dijkstra.c -o dijkstra
./dijkstra
```

## Expected Output

```
Adjacency List:
s -> (y, w=5) -> (t, w=10) -> NULL
t -> (y, w=2) -> (x, w=1) -> NULL
x -> (z, w=4) -> NULL
y -> (z, w=2) -> (x, w=9) -> (t, w=3) -> NULL
z -> (x, w=6) -> (s, w=7) -> NULL
Vertex Distance from Source
0        0
1        8
2        9
3        5
4        7
```

## Files

- `dijkstra.c` — Main implementation with adjacency list graph, min-heap, and Dijkstra's algorithm
