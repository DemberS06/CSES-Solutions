#include <bits/stdc++.h>

using namespace std;
struct Treap{
    int n, root=0;
    vector<int> p, L, R, par, lzy, t;
    Treap(int _n):n(_n), p(n+1), t(n+1, 0){
        random_device rd; 
        mt19937 gen(rd());
        for(int i=1; i<=n; i++)p[i]=gen();
        L=R=par=lzy=t;
    }

    void update(int x){
        t[x]=t[L[x]]+t[R[x]]+1;
        par[L[x]]=par[R[x]]=x;
    }

    void rev(int x){
        if(!lzy[x])return;
        lzy[L[x]]^=1;
        lzy[R[x]]^=1;
        lzy[x]=0;
        swap(L[x], R[x]);
    }

    int merge(int x, int y){
        if(!x || !y)return x?x:y;
        rev(x); rev(y);
        if(p[x]>p[y]){
            R[x]=merge(R[x], y);
            update(x); return x;
        }
        L[y]=merge(x, L[y]);
        update(y); return y;
    }

    void push(int x){
        t[x]=1;
        root=merge(root, x);
    }

    pair<int, int> split(int x, int k){
        if(!x)return {0, 0};
        rev(x);
        if(t[L[x]]>=k){
            auto [ll,lr]=split(L[x], k);
            L[x]=lr;
            update(x);
            return {ll, x};
        }
        auto [rl,rr]=split(R[x], k-t[L[x]]-1);
        R[x]=rl;
        update(x);
        return {x, rr};
    }

    void cut(int a, int b){
        auto [p, q]=split(root, b);
        auto [f, g]=split(p, a-1);
        lzy[g]^=1;
        root=merge(f, g);
        root=merge(root, q);

    }
    int query(int x){
        int a=t[L[x]]+1, b=t[R[x]]+1;
        if(lzy[x])swap(a, b);
        while(par[x]){
            int y=par[x];
            if(x==L[y])b+=t[R[y]]+1;
            else a+=t[L[y]]+1;
            if(lzy[y])swap(a, b);
            x=y;
        }
        return a;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<pair<int, int>> ans;
    Treap T(n);

    for(int i=1, x; i<=n; i++){
        cin>>x; T.push(x);
    }

    for(int i=1, x; i<=n; i++){
        x=T.query(i);
        if(x==i)continue;
        ans.push_back({i, x});
        T.cut(i, x);
    }

    cout<<ans.size()<<"\n";
    for(auto& [x, y]:ans)cout<<x<<' '<<y<<"\n";

    return 0;
}