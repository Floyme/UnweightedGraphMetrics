#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define ll unsigned long long

using namespace std;

const ll INF = ULONG_LONG_MAX;

vector<ll> dijkstra(vector<vector<pair<ll, ll>>> &graph, int start) {
    vector<ll> dist(graph.size(), INF);
    set<pair<ll,ll>> q;
    dist[start] = 0;
    q.insert({dist[start], start});

    while(!q.empty()) {
        ll nearest = q.begin() -> second;
        q.erase(q.begin());

        for (auto &[weight, to]: graph[nearest]) {
            if (dist[to] > dist[nearest] + weight) {
                q.erase({dist[to], to});
                dist[to] = dist[nearest] + weight;
                q.insert({dist[to], to});
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;

    vector<vector<pair<ll,ll>>> graph(n);
    for (int e = 0; e < m; e++) {
        ll v1, v2;
        cin >> v1 >> v2;
        if (v1 == v2) continue;
        v1--;
        v2--;
        graph[v1].emplace_back(1, v2);
        graph[v2].emplace_back(1, v1);
    }

    vector<vector<ll>> distances;
    distances.reserve(n);
    for (int v = 0; v < n; v++) {
        distances.push_back(dijkstra(graph, v));
    }

    vector<ll> centres;
    ll Diameter = 0, Radius = INF;
    for (int v = 0; v < n; v++) {
        ll distance = 0;
        ll cntOfInf = 0;
        sort(distances[v].begin(), distances[v].end());
        for (ll dist: distances[v]) {
            if (dist != INF) {
                distance = max(distance, dist);
            } else {
                cntOfInf++;
            }
        }
        if (distance > Diameter && cntOfInf < distances[v].size() - 2) {
            Diameter = distance;
        }
        if (distance <= Radius && cntOfInf < distances[v].size() - 2) {
            Radius = distance;
            centres.push_back(v + 1);
        }
    }

    cout << "Diameter: " << Diameter << '\n';
    cout << "Radius: " << Radius << '\n';
    cout << "Centres: ";
    for (int i = 0; i < centres.size(); i++) {
        if (i == centres.size() - 1) {
            cout << centres[i] << '.';
            return 0;
        }
        cout << centres[i] << ',';
    }
}