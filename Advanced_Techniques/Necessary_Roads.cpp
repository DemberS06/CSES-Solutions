#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0;
    cin>>n>>m;

    vector<vector<int>> adj(n+1), jda(n+1);
    vector<int> col(n+1, 0), st; st.reserve(n);
    
    function<void(int, int, int, vector<int>&, vector<vector<int>>&)> kosaraju = [&](int x, int y, int f, vector<int>& vis, vector<vector<int>>& adj){
        k+=f;
        vis[x]=k;
        for(auto& u:adj[x]){
            if(f && u!=y)jda[u].push_back(x);
            if(vis[u])continue;
            kosaraju(u, x, f, vis, adj);
        }
        if(f)st.push_back(x);
    };
    
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
 
    for(int i=1; i<=n; i++){
        if(!col[i])kosaraju(i, i, 1, col, adj);
    }
 
    k=0; for(auto &u:col)u=0;
    while(!st.empty()){
        auto x=st.back();
        st.pop_back();
        if(!col[x])k++, kosaraju(x, x, 0, col, jda);
    }

    vector<pair<int, int>> ans; ans.reserve(m);

    for(int i=1; i<=n; i++){
        for(auto& u:jda[i]){
            if(col[i]!=col[u])ans.push_back({u, i});
        }
    }

    cout<<ans.size()<<"\n";
    for(auto& [x, y]:ans)cout<<x<<' '<<y<<"\n";

    return 0;
}