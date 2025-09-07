#include <iostream>
#include <vector>
using namespace std;
struct Edge { int u, v; long long w; };
const long long INF = 1000000000000000000LL;
bool bellmanFord(int n, int src, const vector<Edge>& edges, vector<long long>& dist){
    dist.assign(n+1, INF);
    dist[src] = 0;
    for(int i = 1; i <= n-1; ++i){
        bool changed = false;
        for(size_t j = 0; j < edges.size(); ++j){
            int u = edges[j].u;
            int v = edges[j].v;
            long long w = edges[j].w;
            if(dist[u] < INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if(!changed) break;
    }
    for(size_t j = 0; j < edges.size(); ++j){
        int u = edges[j].u;
        int v = edges[j].v;
        long long w = edges[j].w;
        if(dist[u] < INF && dist[u] + w < dist[v]) return false;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if(!(cin >> n >> m)) return 0;
    int src;
    cin >> src;
    vector<Edge> edges(m);
    for(int i = 0; i < m; ++i) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    vector<long long> dist;
    bool ok = bellmanFord(n, src, edges, dist);
    if(!ok){ cout << "Negative cycle detected\n"; return 0; }
    for(int i = 1; i <= n; ++i){
        if(dist[i] == INF) cout << "INF\n"; else cout << dist[i] << "\n";
    }
    return 0;
}
