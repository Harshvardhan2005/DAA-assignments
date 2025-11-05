// Harshvardhan Borude
// 123B1F013
// 22|08|2025
/*
PROBLEM STATEMENT:
Scenario: Smart Traffic Management for Emergency Vehicles
A smart city is implementing an intelligent traffic management system to assist ambulances
in reaching hospitals as quickly as possible. The city’s road network is represented as a
graph, where:
● Intersections (junctions) are nodes.
● Roads between intersections are edges with weights representing travel time (in minutes)
considering traffic congestion.
An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination
D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road
segment may change in real time.
As a transportation engineer, you are assigned to:
1. Implement Dijkstra’s algorithm to find the shortest path from the ambulance's current
location (S) to all possible hospitals.
2. Account for dynamic weight updates as traffic conditions change.
3. Optimize the system to work efficiently for a large city with thousands of intersections
and roads.
4. Provide a visual representation of the optimal path for navigation.
Expected Outcome:
The system should suggest the quickest route for the ambulance, updating dynamically
based on real-time traffic conditions, ensuring minimal response time to emergencies.
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double weight; 
};

struct Node {
    int id;
    double dist;
    bool operator>(const Node& other) const { return dist > other.dist; }
};

vector<double> dijkstra(int N, int source, vector<vector<Edge>>& adj, vector<int>& parent) {
    vector<double> dist(N, 1e9);
    dist[source] = 0.0;
    parent.assign(N, -1);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({source, 0.0});

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int u = current.id;
        double d = current.dist;

        if (d > dist[u]) continue; 

        for (auto &edge : adj[u]) {
            int v = edge.to;
            double w = edge.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }
    return dist;
}

vector<int> reconstructPath(int dest, const vector<int>& parent) {
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int N, M; 
    cout << "Enter number of intersections (nodes) and roads (edges): ";
    cin >> N >> M;

    vector<vector<Edge>> adj(N);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < M; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w; 
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); 
    }

    int source;
    cout << "Enter ambulance starting location (source node): ";
    cin >> source;

    int H; 
    cout << "Enter number of hospitals: ";
    cin >> H;
    vector<int> hospitals(H);
    cout << "Enter hospital node indices:\n";
    for (int i = 0; i < H; i++) cin >> hospitals[i];

    vector<int> parent;
    vector<double> dist = dijkstra(N, source, adj, parent);

    double minDist = 1e9;
    int nearestHospital = -1;
    for (int h : hospitals) {
        if (dist[h] < minDist) {
            minDist = dist[h];
            nearestHospital = h;
        }
    }

    vector<int> path = reconstructPath(nearestHospital, parent);

    cout << "\nNearest hospital: Node " << nearestHospital << "\n";
    cout << "Shortest travel time: " << minDist << " minutes\n";
    cout << "Path: ";
    for (int v : path) cout << v << " ";
    cout << "\n";

    return 0;
}
