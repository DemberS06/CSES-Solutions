#include <bits/stdc++.h>

using namespace std;

struct DSU{
    int n;
    vector<int> id, vis;
    vector<vector<int>> cmp, adj;

    DSU(int _n):n(_n), id(n+1), cmp(n+1), vis(n+1, 0), adj(n+1){
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

    bool query(vector<pair<int, int>>& v){
        int ok=1, cnt=v.size();
        for(auto& [x, y]:v){
            x=id[x], y=id[y];
            if(x==y)ok=0;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        function<void(int, int)> dfs = [&](int x, int y){
            vis[x]=1; cnt--;
            for(auto& u:adj[x]){
                if(u==y)continue;
                if(vis[u]){ok=0; continue;}
                dfs(u, x);
            }
        };

        for(auto& [x, y]:v){
            if(!vis[x])dfs(x, x), cnt++;
        }
        if(cnt!=0)ok=0;

        for(auto& [x, y]:v){
            adj[x].clear(); vis[x]=0;
            adj[y].clear(); vis[y]=0;
        }
        return ok;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    cin>>n>>m>>q;
    
    vector<int> x(m), y(m), w(m), p(m), ans(q, 1);
    vector<vector<pair<int, int>>> query; 
    map<int, vector<pair<int, int>>> mp;
    map<int, vector<int>> f, edge;
    DSU G(n);

    for(int i=0; i<m; i++){
        cin>>x[i]>>y[i]>>w[i];
        p[i]=i;
        edge[w[i]].push_back(i);
    }

    for(int i=0, k, t; i<q; i++){
        cin>>k;
        while(k--){
            cin>>t;
            f[w[t-1]].push_back(t-1);
        }
        for(auto& [u, v]:f){
            mp[u].push_back({i, query.size()});
            query.push_back({});
            for(auto& h:v)query.back().push_back({x[h], y[h]});
        }f.clear();
    }

    for(auto& [_, v]:edge){
        for(auto& [i, j]:mp[_])ans[i]&=G.query(query[j]);
        for(auto& i:v)G.add(x[i], y[i]);
    }

    for(auto& u:ans){
        if(u)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}