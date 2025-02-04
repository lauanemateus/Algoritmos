#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5+5;
const ll INF = 1e15;

struct no{
    int val_min, val_max, id_min, id_max;
    no(){
        val_min = N, val_max = -N, id_min = id_max = -1; // quando um no é inicializado, são atribuidos esses valores (nulos)
    }
};

int teste;
int n;
no t[4*N], vetor[N], nulo;

no merge(no esq, no dir){ // nulo impacta aqui
    no ans;
    // atualiza id's
    if(esq.val_min<dir.val_min){
        ans.id_min = esq.id_min;
    }
    else ans.id_min = dir.id_min;
    if(esq.val_max>dir.val_max){
        ans.id_max = esq.id_max;
    }
    else ans.id_max = dir.id_max;
    // atualiza outros valores
    ans.val_min = min(esq.val_min, dir.val_min);
    ans.val_max = max(esq.val_max, dir.val_max);
    return ans;
}

void build(no vetor[], no t[], int v, int tl, int tr) { // v começa de 1
    if (tl == tr) {
        t[v]=vetor[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(vetor, t, v*2, tl, tm);
        build(vetor, t, v*2+1, tm+1, tr);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
}

no query(no vetor[], no t[], int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return nulo;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return merge(query(vetor, t, v*2, tl, tm, l, min(r, tm))
           , query(vetor, t, v*2+1, tm+1, tr, max(l, tm+1), r));
}

// tl e tr se referem à árvore
void update(no vetor[], no t[], int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v].val_min = t[v].val_max = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(vetor, t, v*2, tl, tm, pos, new_val);
        else
            update(vetor, t, v*2+1, tm+1, tr, pos, new_val);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
}

void solve(){
    cin>>n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin>>x;
        vetor[i].val_max = vetor[i].val_min = x;
        vetor[i].id_min = vetor[i].id_max = i;
    }
    build(vetor, t, 1, 0, n-1);

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>teste;
    while(teste--) solve();
    return 0;
}
