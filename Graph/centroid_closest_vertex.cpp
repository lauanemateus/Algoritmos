// https://codeforces.com/contest/342/problem/E
// We want to paint some vertices, and sometimes ask for the closest painted vertex to another especific vertex
// The idea is to construct a centroid tree, and save for each vertex, the best answers by looking at the descendants

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

vector<vector<int>> graph;
vector<int> in, out, dist;
vector<vector<int>> st;
int cc;
int pai[N], cor[N];

// fazer todos os cálculos de LCA necessários.
void dfs_lca(int x, int p) {
    st[x][0]=p;
    for(int i=1; i<=K; i++){
        st[x][i]=st[st[x][i-1]][i-1];
    }
    in[x]=cc++;
    for(auto i: graph[x]){
        if(i != p) {
            dist[i] = dist[x] + 1;
            dfs_lca(i, x);
        }
    }
    out[x]=cc++;
}

// função para inicializar o LCA de todos os caras.
void lca_init(int n) {
    in.resize(n);
    out.resize(n);
    dist.assign(n, 0);
    st.resize(n);
    for(int i=0; i<n; i++){
        st[i].resize(K+1, 0);
    }
    cc = 1;
    dist[1]=0;
    dfs_lca(1,1);
}

// u é ancestral de v
bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v];
}

// achar o LCA entre dois vértices.
int lca(int u, int v) {
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;

    for(int i=K; i>=0; i--){
        if(!is_ancestor(st[u][i], v)){
            u = st[u][i];
        }
    }
    return st[u][0];
}

int get_dist(int u, int v) {
    return dist[u] + dist[v] - 2*dist[lca(u,v)];
}


/*
    Indexado de 1
*/
struct Centroid{
    vector<int> p; // o pai de cada cara no centroide
    vector<bool> vis; // visitado para construir o centroide
    vector<int> tam; // tam da subarvore
    vector<vector<int>> & graph; // referencia da arvore original
    vector<pair<int,int>> best; // melhores distancias.
    int n; // qtd de vertices 
    int r; // raiz do centroide

    // grafo como referência!
    Centroid(int n, vector<vector<int>> & graph) : graph(graph), n(n){
        tam.resize(n+10);
        vis.resize(n+10);
        best.resize(n+10);
        for(int i=0; i<=n; i++){
            best[i] = make_pair(INF, INF);
        }
        // qtd.resize(n+10);
        p.resize(n+10);
        r=build(1);
    }

    // constroi o centroid decomposition
    int build(int u){
        set_tam(u,u);
        u = find_centroid(u);
        vis[u]=1;

        p[u]=u;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            int x=build(v);
            p[x]=u;
        }    
        return u;
    }

    // ajusta os tamanhos das subárvores.
    void set_tam(int u,int ant){
        tam[u]=1;
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            set_tam(v,u);
            tam[u]+=tam[v];
        }
    }
    int find_centroid(int u){
        while(1){
            int flag=1;
            for(auto v: graph[u]){
                if(vis[v]) continue;
                if(tam[v]*2 > tam[u]){
                    tam[u]-=tam[v]; // rerooting
                    tam[v]+=tam[u];
                    u=v;
                    flag=0;
                    break;
                }
            }
            if(flag) break;
        }
        return u;
    }

    // pintar um cara, quer dizer que estou colocando a distância dele como 0
    void update(int u,int ant){
        best[u]={0, u};
        int x = u; // quando dou update em x, só preciso mudar os que estão em cima, os pais
        while(u!=p[u]){
            u = p[u];
            int tmp = get_dist(u,x);
            if(best[u].ft > tmp){
                best[u].ft = tmp;
                best[u].sd = x;
            }
        }
        for(auto v: graph[u]){
            if(v == ant || vis[v]) continue;
            update(v,u);
        }
    }

    // buscar o 0 mais próximo de u.
    pair<int,int> query(int u, int ant) {
        pair<int,int> rs = best[u];
        int x = u;
        while(u!=p[u]){ // os pais guardam a melhor resposta em relação a todos seus descendentes. Logo, na query, só preciso olhar para os pais
            u=p[u];
            int tmp = best[u].ft+get_dist(u,x);
            if(rs.ft > tmp){
                rs.ft = tmp;
                rs.sd = best[u].sd;
            }
        }
        return rs;
    }
};

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
 
    int n, q;
    cin >> n >> q;

    graph.resize(n+1);
    for(int i=1; i<n; i++){
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    lca_init(n+1);
    Centroid c(n+1, graph);

    c.update(1, 1);
    int t, v;
    for(int i=0; i<q; i++) {
        cin>>t>>v;
        if(t==1){
            c.update(v, v);
        }
        else{
            cout << c.query(v, v).ft <<"\n";
        }
    }
    return 0;
}