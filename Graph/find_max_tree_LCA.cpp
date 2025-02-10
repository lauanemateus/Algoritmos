// original problem: https://codeforces.com/problemset/problem/609/E

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
const int N = 2e5+5;
const int K = 25;
const int INF = N;
const ll inf = 1e15;

struct Edges{
    int a, b, id;
    ll w;
    bool operator <(const Edges e){
        return this->w < e.w;
    }
};

ll st_pai[N][K], st_max[N][K];
vector<pair<int, ll>> adj[N];
Edges edges[N];
int pai[N], ct, tin[N], tout[N];


int acha(int a){
    if(a == pai[a]) return a;
    return pai[a] = acha(pai[a]);
}

void une(int a, int b){
    a = acha(a), b = acha(b);
    if(a == b) return;
    pai[a] = b;
}

void dfs(int v, int bef, ll w){
    tin[v] = ++ct;

    st_pai[v][0] = bef, st_max[v][0] = w;
    for(int i=1; i<K; i++){
        st_pai[v][i] = st_pai[st_pai[v][i-1]][i-1];
        st_max[v][i] = max(w, max(st_max[v][i-1], st_max[st_pai[v][i-1]][i-1]));
    }
    for(auto u:adj[v]){
        if(u.ft != bef)
            dfs(u.ft, v, u.sd);
    }

    tout[v] = ++ct;
}

int ancestral(int a, int b){ // se a é ancestral de b
    return tin[a]<=tin[b] && tout[a]>=tout[b];
}

ll find_max_lca(int a, int b){
    ll maior = 0;
    if(ancestral(a, b)) {
        swap(a, b);
    }
    for(int i=K-1; i>=0; i--){
        if(!ancestral(st_pai[a][i], b)) maior = max(maior, st_max[a][i]), a = st_pai[a][i];
    }
    for(int i=K-1; i>=0; i--){
        if(!ancestral(st_pai[b][i], a)) maior = max(maior, st_max[b][i]), b = st_pai[b][i];
    }
    maior = max(maior, st_max[a][0]);
    if(!ancestral(b, a)) maior = max(maior, st_max[b][0]);
    // LCA is st_pai[a][0]
    return maior;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    ll a, b, w;
    for (int i = 0; i < m; i++)
    {
        cin>>a>>b>>w;
        edges[i].w = w, edges[i].a = a, edges[i].b = b;
        edges[i].id = i;
    }
    sort(edges, edges+m);
    for (int i = 1; i <= n; i++)
    {
        pai[i] = i;
    }
    ll ans = 0;
    for (int i = 0; i < m; i++)
    {
        a = acha(edges[i].a);
        b = acha(edges[i].b);
        if(a == b) continue;
        une(a, b);
        ans += edges[i].w;
        adj[edges[i].a].pb({edges[i].b, edges[i].w});
        adj[edges[i].b].pb({edges[i].a, edges[i].w});
    }
    dfs(1, 1, 0);
    vector<ll>print(m);
    for (int i = 0; i < m; i++)
    {
        print[edges[i].id] = ans - find_max_lca(edges[i].a, edges[i].b) + edges[i].w; // a ideia é tirar a maior aresta do ciclo formado com a adição ao MST da aresta i 
    }
    for (int i = 0; i < m; i++)
    {
        cout<<print[i]<<"\n";
    }
    
    return 0;
}