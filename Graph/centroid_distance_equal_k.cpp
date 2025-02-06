// how many paths on a tree equal to k? 
// the ideia is to find the solution for each centroid. There is no need to construct a centroid tree.

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
const ll inf = 1e15;
 
vector<vector<int>> graph;

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
    int k; // uma certa distancia
    ll qtd_caminhos_equal_k=0;
    map<ll, ll> count_caminhos; // qtd de caminhos com uma distância, dado uma raiz

    // grafo como referência!
    Centroid(int n, vector<vector<int>> & graph, int k) : graph(graph), n(n), k(k){
        tam.resize(n+10);
        vis.resize(n+10);
        best.resize(n+10);
        p.resize(n+10);
        r=build(1, k);  
    }

    void print(int v, int ant, int dist){
        cout<<"v="<<v<<" qtd de caminhos com dist = "<<dist<<" eh "<< count_caminhos[dist] <<"\n";  
        for(auto u:graph[v]){
            if(u==ant || vis[u]) continue;
            print(u, v, dist+1);
        }
    }

    // constroi o centroid decomposition
    int build(int u, int k){
        set_tam(u,u);
        u = find_centroid(u);
        vis[u]=1;

        count_caminhos.clear();
        count_caminhos[0] = 1;
        // cout<<"centroid = "<<u<<"\n";
        solve(u, u, 0, 1, k); // adiciona a arvore
        // print(u, u, 0);
        for(auto v: graph[u]){
            if(vis[v]) continue;
            // cout<<"remove\n";
            solve(v, u, 1, 0, k); // remove a subarvore
            // print(v, u, 1);
            // cout<<"calcula\n";
            solve(v, u, 1, 2, k); // calcula a resposta em relação à subarvore
            // print(v, u, 1);
            // cout<<"adiciona de volta\n";
            solve(v, u, 1, 1, k); // adiciona a subarvore
            // print(v, u, 1);
        } 
        // cout<<"\n";

        p[u]=u;
        for(auto v: graph[u]){
            if(vis[v]) continue;
            int x=build(v, k);
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
                    tam[u]-=tam[v];
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

    void solve(int v, int ant, ll dist, int flag, int k){  
        if(flag == 0){ // if flag = 0, remove that subtree
            count_caminhos[dist]--;
        }
        else if(flag==1){ // if flag = 1, add the subtree
            count_caminhos[dist]++;
        }
        else{ // if flag = 2, update answer
            qtd_caminhos_equal_k += count_caminhos[k-dist];
        }
        for(auto u:graph[v]){
            if(u==ant || vis[u]) continue;
            solve(u, v, dist+1, flag, k);
        }
    }
};

void test() {
    int n, k;
    cin >> n >> k;

    graph.resize(n+1);
    for(int i=1; i<n; i++){
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    Centroid c(n+1, graph, k);
    cout<< c.qtd_caminhos_equal_k/2;

    cout<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
 
    test();
    
    return 0;
}