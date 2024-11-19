#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5+5;
const ll INF = 1e15;

struct no{
    int val_min, val_max, id_min, id_max;
    no(){
        val_min = N, val_max = -N, id_min = id_max = -1;
    }
};

int teste;
int n;
no t[4*N], vetor[N], nulo;
int nulo_min = n, nulo_max = n+1;

no merge(no esq, no dir){
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

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v]=vetor[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        t[v] = merge(t[v*2], t[v*2+1]);
    }
}

no query(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return nulo;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return merge(query(v*2, tl, tm, l, min(r, tm))
           , query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

// tl e tr se referem à árvore
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v].val_min = t[v].val_max = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
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
    build(1, 0, n-1);

    int q;
    cin>>q;
    while(q--){
        int l, r;
        cin>>l>>r;
        no ans = query(1, 0, n-1, l, r);
        cout<<ans.val_max<<" "<<ans.val_min<<"\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
