#include<bits/stdc++.h>
using namespace std;

//Kruskal-MST -> Minimum spanning tree
//nesse exemplo, queremos minimizar os pesos/distancias(de vertices vizinhos) da arvore geradora minima
//a prioridade aqui é a qtd min de arestas, e nao os pesos em si (diferente do dijkstra, o numero de aresta indepente, e o importante é o peso dos vertcies ate a origem)

typedef pair<int,int> pii;
const int MAXN = 100010;
int pai[MAXN], qtd[MAXN];

void inicia(int n){
    for(int i=0;i<=n;i++){
        pai[i]=i, qtd[i]=1;
    }
}
int acha(int x){
    if(pai[x] == x) return x;
    return pai[x] = acha(pai[x]); 
}
void une(int x,int y){
    x = acha(x);
    y = acha(y);
    if(x==y) return ;
    qtd[x]+=qtd[y];
    pai[y] = x;   
}

int main(){
    int n,m, peso_min=0; // vertices(de 0 a n-1) e m arestas
    cin>>n>>m;
    vector< pair<int, pii> > arestas;
    inicia(n);
    for(int i=0;i<m;i++){
        int a,b,p;
        cin>>a>>b>>p;
        arestas.push_back({p, {a,b}});
    }
    sort(arestas.begin(), arestas.end());
    for(int i=0;i<arestas.size();i++){
        int a = arestas[i].second.first;
        int b = arestas[i].second.second;
        int peso = arestas[i].first;
        if( acha(a) != acha(b) ) {
            cout << "unindo " << a << " e " << b << "\n";
            une(a,b);
            peso_min+=peso;
            cout << "peso_min agora eh " << peso_min << "\n";
        }
    }
    cout << peso_min << "\n";
    return 0;
}
