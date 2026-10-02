#include <bits/stdc++.h>

using namespace std;

struct DSU{
    int n;
    vector<vector<int>> cmp;
    vector<int> id;

    DSU(int _n){
        n=_n;
        cmp.resize(n+1);
        id.resize(n+1);

        for(int i=1; i<=n; i++)id[i]=i, cmp[i].push_back(i);
    }

    void merge(int x, int y){
        if(cmp[x].size()>cmp[y].size())swap(x, y);
        for(auto& u:cmp[x]){
            id[u]=y;
            cmp[y].push_back(u);
        }cmp[x].clear();
    }

    void add(int x, int y){
        x=id[x], y=id[y];
        if(x==y)return;
        merge(x, y);
    }

    bool query(int x, int y){
        return id[x]!=id[y];
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    
    vector<int> ans(m, 0), x(m), y(m);
    map<int, vector<int>> mp;
    DSU G(n);

    for(int i=0, w; i<m; i++){
        cin>>x[i]>>y[i]>>w;
        mp[w].push_back(i);
    }

    for(auto& [_, v]:mp){
        for(auto& i:v)ans[i]=G.query(x[i], y[i]);
        for(auto& i:v)G.add(x[i], y[i]);
    }

    for(auto& u:ans){
        if(u)cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}