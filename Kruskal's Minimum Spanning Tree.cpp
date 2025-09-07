#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge { int u, v; long long w; };
int findParent(vector<int>& parent, int x){
    while(parent[x] != x) x = parent[x];
    return x;
}
bool unite(vector<int>& parent, vector<int>& rankv, int a, int b){
    a = findParent(parent, a);
    b = findParent(parent, b);
    if(a == b) return false;
    if(rankv[a] < rankv[b]) swap(a,b);
    parent[b] = a;
    if(rankv[a] == rankv[b]) rankv[a]++;
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<Edge> edges(m);
    for(int i = 0; i < m; ++i) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b){ return a.w < b.w; });
    vector<int> parent(n+1), rankv(n+1, 0);
    for(int i = 1; i <= n; ++i) parent[i] = i;
    long long total = 0;
    vector<Edge> used;
    for(int i = 0; i < m; ++i){
        if(unite(parent, rankv, edges[i].u, edges[i].v)){
            used.push_back(edges[i]);
            total += edges[i].w;
        }
    }
    if((int)used.size() != n-1){ cout << "No MST\n"; return 0; }
    cout << total << "\n";
    for(size_t i = 0; i < used.size(); ++i) cout << used[i].u << " " << used[i].v << " " << used[i].w << "\n";
    return 0;
}
