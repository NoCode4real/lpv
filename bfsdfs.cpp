#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph {
	int V;
	vector<vector<int>> adj;

public:
	Graph(int V) : V(V), adj(V) {}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void parallelBFS(int start) {
		vector<bool> visited(V, false);
		queue<int> q;

		visited[start] = true;
		q.push(start);

		while (!q.empty()) {
			int curr = q.front(); q.pop();
			cout << curr << " ";

			#pragma omp parallel for
			for (int i = 0; i < adj[curr].size(); ++i) {
				int neighbor = adj[curr][i];
				if (!visited[neighbor]) {
					#pragma omp critical
					if (!visited[neighbor]) {
						visited[neighbor] = true;
						q.push(neighbor);
					}
				}
			}
		}
	}

	void parallelDFS(int start) {
		vector<bool> visited(V, false);
		#pragma omp parallel
		#pragma omp single nowait
		dfsUtil(start, visited);
	}

	void dfsUtil(int u, vector<bool>& visited) {
		visited[u] = true;
		cout << u << " ";

		#pragma omp parallel for
		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			if (!visited[v]) {
				#pragma omp critical
				if (!visited[v]) dfsUtil(v, visited);
			}
		}
	}
};

int main() {
	int V, E, u, v, start;
	cout << "Enter number of vertices and edges: ";
	cin >> V >> E;

	Graph g(V);
	cout << "Enter " << E << " edges (u v):\n";
	for (int i = 0; i < E; ++i) {
		cin >> u >> v;
		g.addEdge(u, v);
	}

	cout << "Enter starting vertex: ";
	cin >> start;

	cout << "\nParallel BFS: ";
	g.parallelBFS(start);

	cout << "\nParallel DFS: ";
	g.parallelDFS(start);

	cout << endl;
	return 0;
}
