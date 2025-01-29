// Ideia do Project Selection: temos M projetos e N ferramentas. Cada projeto usa algumas ferramentas,
// que podem também ser usadas em outros projetos. Cada projeto tem um ganho l_i e cada ferramenta tem um
// custo c_i. Qual o lucro máximo?

// Esse código resolve o problema "Petya and Graph" do codeforces. Nesse caso, os projetos são interpretados como
// as arestas e as ferramentas como os vértices.

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define ft first
#define sd second
const int N = 1000+5;
const ll mod = 1e9+7;
const ll inf = 1e9;

ll v[N];

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
  
    int n, m;
    cin>>n>>m;
    int s = n+m+1, add = m, t = n+m+2;
    Dinic grafo(n+m+10, s, t);
    ll ans=0;

    for (int i = 1; i <= n; i++)
    {
        cin>>v[i];
        // adiciona os vertices ate o sink
        grafo.add_edge(i+add, t, v[i]);
    }
    
    int a, b;
    ll c;

    for(int i=1; i<=m; i++){
        cin>>a>>b>>c;
        a+=add, b+=add;
        ans+=c; // soma o ganho máximo
        // adiciona as arestas saindo do source
        grafo.add_edge(s, i, c);
        // adiciona as arestas ligando nos vértices
        grafo.add_edge(i, a, inf);
        grafo.add_edge(i, b, inf);
    }

    ll fluxo = grafo.flow();
    ans -= fluxo; // subtrai do ganho máximo o custo
    cout<<ans<<"\n";
    return 0;
}