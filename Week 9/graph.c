/***************************************************************
 * Undirected graph using an adjacency matrix                  *
 ***************************************************************/

#include <stdio.h>

#define max 50

int vertex[max];
int adj[max][max];

int find(int n, int x);             //check if the vertex is present in the list of vertices and return its index, else return -1
void display(int n);                //display the adjacency matrix of the graph
void bfs(int n, int s);             //perform bfs on the graph starting from vertex s
void dfs(int n, int x, int seen[]); //perform dfs on the graph starting from vertex x, using the seen array to track visited vertices

int main(void) {
    int n, m, a, b;
    //n is number of vertices, m is number of edges, a and b are the two vertices of an edge
    printf("Maximum Number of vertices: %d\n Enter the number of vertices: ", max);
    scanf("%d", &n);
    if ( n < 1 || n > max) {
        printf("Error: invalid number of vertices\n");
        return 1;
    }
    //initialize the adjacency matrix to 0
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        adj[i][j] = 0;
    }
}
    printf("Enter the vertex labels:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i + 1);
        if (scanf("%d", &vertex[i]) != 1) {
            printf("Error: invalid vertex label\n");
            return 1;
        }
        for (int j = 0; j < i; j++) {
            if (vertex[i] == vertex[j]) {
                printf("Error: vertex labels must be unique\n");
                return 1;
            }
        }
    }

    printf("Enter Number of edges: ");
    scanf("%d", &m);
    if (m < 0||m> n*(n-1)/2) {
        printf("Error: invalid number of edges\n");
        return 1;
    }

    for (int i = 0; i < m; i++) {
        printf("Edge: %d \n", i + 1);
        printf("Enter the vertex 1: ");
        scanf("%d", &a);
        printf("Enter the vertex 2: ");
        scanf("%d", &b);

        int x = find(n, a);
        int y = find(n, b);
        if (x == -1 || y == -1 || x == y) {
            printf("Error: enter two different listed vertices\n");
            return 1;
        }

        adj[x][y] = 1;
        adj[y][x] = 1;
    }
    printf("Adjacency Matrix:\n\t");
    //show the adjacency matrix
    display(n);

    //show the BFS
    
    bfs(n, 0);
    
    //show the DFS
    int seen[max] = {0};
    printf("DFS: ");
    dfs(n, 0, seen);
    printf("\n");
    return 0;
}

int find(int n, int x) {
    for (int i = 0; i < n; i++)
        if (vertex[i] == x)
            return i;
    return -1;
}

void display(int n) {
    for (int i = 0; i < n; i++)
        printf("%d\t", vertex[i]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t", vertex[i]);
        for (int j = 0; j < n; j++)
            printf("%d\t", adj[i][j]);
        printf("\n");
    }
}

void bfs(int n, int s) {
    int queue[max], seen[max] = {0};
    int front = 0, back = 0;

    queue[back++] = s;
    seen[s] = 1;
    printf("BFS: ");

    while (front < back) {
        int x = queue[front++];
        printf("%d ", vertex[x]);
        for (int i = 0; i < n; i++) {
            if (adj[x][i] && !seen[i]) {
                queue[back++] = i;
                seen[i] = 1;
            }
        }
    }
    printf("\n");
}

void dfs(int n, int x, int seen[]) {
    seen[x] = 1;
    printf("%d ", vertex[x]);
    for (int i = 0; i < n; i++)
        if (adj[x][i] && !seen[i])
            dfs(n, i, seen);
}
