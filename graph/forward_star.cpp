// Forward Star Graph Representation Template
// Works for directed and undirected graphs

#include <bits/stdc++.h>
using namespace std;

// ================== CONSTANTS ==================
const int MAXN = 1e5 + 5;   // maximum number of nodes
const int MAXM = 2e5 + 5;   // maximum number of edges (double it for undirected)

// ================== DATA STRUCTURES ==================

// head[u] = index of the first edge from node u
int head[MAXN];

// to[i] = destination node of edge i
int to[MAXM];

// nxt[i] = next edge index (linked list style)
int nxt[MAXM];

// optional: store weights
int weight[MAXM];

// total number of edges added
int edgeCount;

// ================== INITIALIZATION ==================

void init(int n) {
    // initialize all heads to -1 (means no edges)
    for (int i = 1; i <= n; i++)
        head[i] = -1;

    edgeCount = 0;
}

// ================== ADD EDGE ==================

// add a directed edge u → v
void add_edge(int u, int v) {
    to[edgeCount] = v;          // store destination
    nxt[edgeCount] = head[u];   // link to previous first edge
    head[u] = edgeCount;        // update head to new edge
    edgeCount++;
}

// add a directed weighted edge u → v with weight w
void add_edge(int u, int v, int w) {
    to[edgeCount] = v;
    weight[edgeCount] = w;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
    edgeCount++;
}

// ================== TRAVERSAL ==================

void traverse(int u) {
    // iterate over all edges from node u
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];          // destination node
        // int w = weight[i];   // use if weighted

        // process edge (u → v)
        cout << u << " -> " << v << "\n";
    }
}

// ================== EXAMPLE USAGE ==================

int main() {
    int n = 5; // number of nodes
    init(n);

    // add edges
    add_edge(1, 2);
    add_edge(1, 3);
    add_edge(2, 4);
    add_edge(3, 5);

    // for undirected graph:
    // add_edge(u, v);
    // add_edge(v, u);

    // traverse all nodes
    for (int u = 1; u <= n; u++) {
        traverse(u);
    }

    return 0;
}
