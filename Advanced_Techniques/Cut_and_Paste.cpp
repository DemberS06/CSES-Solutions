#include <bits/stdc++.h>

using namespace std;

struct Treap{
    int n, cnt=0, root=0;
    vector<int> l, r, t, p;
    Treap(int _n):n(_n), l(n+1, 0), r(n+1, 0), t(n+1, 0), p(n+1, 0){
        random_device rd;
        mt19937 gen(rd());
        for(int i=1; i<=n; i++)p[i]=gen(), push();
    }

    void update(int x){
        t[x]=1+t[l[x]]+t[r[x]];
    }

    int merge(int x, int y){
        if(y==0)return x;
        if(x==0)return y;
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
        cnt++;
        t[cnt]=1;
        root=merge(root, cnt);
    }

    pair<int, int> split(int x, int y){
        if(!x)return {0, 0};
        if(t[l[x]]>=y){
            auto [ll, lr]=split(l[x], y);
            l[x]=lr;
            update(x);
            return {ll, x};
        }
        auto [rl, rr]=split(r[x], y-t[l[x]]-1);
        r[x]=rl;
        update(x);
        return {x, rr};
    }

    void cut(int a, int b){
        auto [x, y]=split(root, b);
        auto [f, g]=split(x, a-1);

        root=merge(f, y);
        root=merge(root, g);
    }

    vector<int> ans(){
        vector<int> res;

        function<void(int)> dfs = [&](int x){
            if(x==0)return;
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
    
    for(auto& u:T.ans())cout<<s[u-1];cout<<"\n";

    return 0;
}