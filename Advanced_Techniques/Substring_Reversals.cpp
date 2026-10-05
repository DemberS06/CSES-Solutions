#include <bits/stdc++.h>

using namespace std;

struct Treap{
    int n, cnt=0, root=0;
    vector<int> l, r, t, p, lzy;
    Treap(int _n):n(_n),l(n+1, 0){
        r=t=p=lzy=l;
        random_device rd;
        mt19937 gen(rd());
        for(int i=1; i<=n; i++)p[i]=gen(), push();
    }
    
    void update(int x){
        t[x]=t[l[x]]+t[r[x]]+1;
    }

    void rev(int x){
        if(!lzy[x])return;
        lzy[x]=0;
        lzy[r[x]]^=1;
        lzy[l[x]]^=1;
        swap(l[x], r[x]);
    }

    int merge(int x, int y){
        if(!x || !y)return x?x:y;
        rev(x); rev(y);
        if(p[x]>p[y]){
            r[x]=merge(r[x], y);
            update(x);
            return x;
        }
        l[y]=merge(x, l[y]);
        update(y);
        return y;
    }

    void push(){
        cnt++; t[cnt]=1;
        root=merge(root, cnt);
    }

    pair<int, int> split(int x, int k){
        if(!x)return {x, x};
        rev(x);
        if(t[l[x]]>=k){
            auto [ll, lr]=split(l[x], k);
            l[x]=lr;
            update(x);
            return {ll, x};
        }
        auto [rl, rr]=split(r[x], k-t[l[x]]-1);
        r[x]=rl;
        update(x);
        return {x, rr};
    }

    void cut(int a, int b){
        auto [p,q]=split(root, b);
        auto [f,g]=split(p, a-1);
        lzy[g]^=1; rev(g);
        root=merge(f, g);
        root=merge(root, q);
    }

    vector<int> ans(){
        vector<int> res;
        function<void(int)> dfs = [&](int x){
            if(!x)return;
            rev(x);
            dfs(l[x]);
            res.push_back(x);
            dfs(r[x]);
        }; dfs(root);
        return res;
    }

};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, q;
    string s;
    cin>>n>>q>>s;

    Treap T(n);
    for(int x, y; q--;){
        cin>>x>>y;
        T.cut(x, y);
    }
    
    for(auto& u:T.ans())cout<<s[u-1];

    return 0;
}