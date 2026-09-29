#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m;
    cin>>n>>m;

    vector<pair<int, int>> ans; ans.reserve(m);
    vector<set<int>> ady(n+1);
    vector<int> vis(n+1, 0), v; v.reserve(n);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        ady[x].insert(y);
        ady[y].insert(x);
    }

    for(int i=1; i<=n; i++){
        if(ady[i].size()<=1){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }

    function<void(int)> dfs = [&](int x){
        if(vis[x])return;
        vis[x]=1;

        while(!ady[x].empty()){
            auto u=*ady[x].begin();
            ady[x].erase(u);
            ady[u].erase(x);
            ans.push_back({x, u});
            dfs(u);
        }
    };

    dfs(1);

    if(ans.size()!=m){
        cout<<"IMPOSSIBLE";
        return 0;
    }

    int k=0;
    
    function<void(int, int, vector<int>&, vector<vector<int>>&)> kosaraju = [&](int x, int f, vector<int>& vis, vector<vector<int>>& adj){
        k+=f;
        vis[x]=k;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            kosaraju(u, f, vis, adj);
        }
        if(f)v.push_back(x);
    };
    vector<vector<int>> adj(n+1), jda(n+1);
    for(auto& [x, y]:ans)adj[x].push_back(y), jda[y].push_back(x);
    
    for(auto &u:vis)u=0;
    for(int i=1; i<=n; i++){
        if(!vis[i])kosaraju(i, 1, vis, adj);
    }
 
    k=0;
    for(auto &u:vis)u=0;
    while(!v.empty()){
        auto x=v.back();
        v.pop_back();
        if(!vis[x])k++, kosaraju(x, 0, vis, jda);
    }

    if(k>1){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }

    for(auto& [x, y]:ans)cout<<x<<' '<<y<<"\n";
    
    return 0;
}