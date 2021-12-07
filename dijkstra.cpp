#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int MAXN = 100010;
const int MAXM = 100010;
const int INF = (int)(1e9+5);
vector<pii> adj[MAXN];
set<pii> S; // para colocar o vertice e a distancia do momento ate a origem
int dist[MAXN], vis[MAXN];

void inicia(){
    for(int i=0;i<MAXN;i++)
        dist[i] = INF;
}

void dijkstra(int s){
    inicia();
    dist[s]=0;
    S.insert({0,s});
    while(!S.empty()){
        pii par = *S.begin();
        S.erase(*S.begin());
        int v = par.second;
        if(vis[v]==1) continue;
        vis[v]=1; // se estou olhando o vertice v que estava no set, é pq a menor distancia dele até a origem já está definida
        for(int i=0;i<adj[v].size();i++){
            int u = adj[v][i].first;
            int peso = adj[v][i].second;
            if(dist[u]>dist[v]+peso){
                dist[u] = dist[v]+peso;
                S.insert({dist[u], u}); // vou adicionando no set as dist atualizadas dos vizinhos de v
                // a distancia pode mudar conforme olhamos outros vertices que estao no set
            }
        }
    }
}

int main(){
    int n, m; 
    cin>>n>>m; // vertices de 1 a n
    for(int i=0;i<m;i++){
        int a,b,p;
        cin>>a>>b>>p;
        adj[a].push_back({b,p});
        // adj[b].push_back({a,p});
    }
    dijkstra(0);
    for(int i=0;i<n;i++){
       cout<< "dist da origem ate " << i << " = " << dist[i] << "\n";
    }
    return 0;
}