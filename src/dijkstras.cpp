#include <algorithm>
#include "dijkstras.h"
using namespace std;

struct Node {
    int vertex;
    int weight;
    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVert = G.numVertices;
    vector<int> distance(numVert, INF);
    previous.assign(numVert, -1);
    vector<bool> visited(numVert, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[source] = 0;
    pq.push(Node(source, 0));

    while(!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        int u = curr.vertex;

        if(visited[u]) {continue;}
        visited[u] = true;

        for (const Edge & edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if(distances[destination] == INF) {
        return path;
    }

    int current = destination;
    while(current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total) {
    if(!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i] << " ";
        }
        cout << endl;
    } else {
        cout << endl;
    }
    cout << "Total cost is " << total << endl;
}