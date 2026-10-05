#include <bits/stdc++.h>

using namespace std;

struct UnionFind{
    int n, cnt;
    vector<int> tam, par;
    vector<tuple<int, pair<int, int>, pair<int, int>>> his;
    UnionFind(int _n):n(_n), cnt(_n), tam(n+1, 1), par(n+1){
        for(int i=1; i<=n; i++)par[i]=i;
    }

    int find(int x){
        while(par[x]!=x)x=par[x];
        return x;
    }

    void push(int x, int y, int t){
        x=find(x); y=find(y);
        if(x==y)return;
        if(tam[x]>tam[y])swap(x, y);
        his.push_back({t, {x, tam[x]}, {y, tam[y]}});
        tam[y]=max(tam[y], tam[x]+1);
        par[x]=y;
        cnt--;
    }
    void pop(int x){
        while(!his.empty()){
            auto [t, p, q]=his.back();
            if(t!=x)break;
            his.pop_back();
            par[p.first]=p.first;
            tam[p.first]=p.second;
            tam[q.first]=q.second;
            cnt++;
        }
    }
};

struct SGT{
    int n;
    vector<vector<pair<int, int>>> sgt;
    UnionFind G;
    SGT(int _m, int _n):n(_n), sgt(4*n), G(_m){}

    void update(int i, int l, int r, int p, int q, pair<int, int> x){
        if(l>r || p>r || q<l)return;
        if(l>=p && q>=r){
            sgt[i].push_back(x);
            return;
        }
        int mt=(l+r)/2;
        update(2*i, l, mt, p, q, x);
        update(2*i+1, mt+1, r, p, q, x);
    }

    void push(pair<int, int> p, int l, int r){
        update(1,1,n,l,r,p);
    }

    vector<int> get_ans(){
        vector<int> res;
        function<void(int, int, int)> dfs=[&](int i, int l, int r){
            if(l>r)return;
            for(auto& [x, y]:sgt[i])G.push(x, y, i);
            if(l==r)res.push_back(G.cnt);
            else{
                dfs(2*i, l, (l+r)/2);
                dfs(2*i+1, (l+r)/2+1, r);
            }
            G.pop(i);
        };
        dfs(1,1,n);
        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    cin>>n>>m>>q;
    SGT S(n, q+1);

    map<pair<int, int>, vector<int>> mp;

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        if(x>y)swap(x, y);
        mp[{x, y}].push_back(1);
    }
    for(int i=1, t, x, y; i<=q; i++){
        cin>>t>>x>>y;
        if(x>y)swap(x, y);
        mp[{x, y}].push_back(i+1);
    }

    for(auto& [u, v]:mp){
        if(v.size()&1)v.push_back(q+2);
        
        for(int i=1; i<v.size(); i+=2){
            S.push(u, v[i-1], v[i]-1);
        }
    }

    for(auto& u:S.get_ans())cout<<u<<' ';

    return 0;
}