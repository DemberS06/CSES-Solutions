#include <bits/stdc++.h>

using namespace std;

const int N=5e4+1;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q, k=0;
    cin>>n>>m>>q;

    vector<vector<int>> adj(n+1), jda(n+1);
    vector<int> col(n+1, 0), st; st.reserve(n);
    
    function<void(int, int, vector<int>&, vector<vector<int>>&)> kosaraju = [&](int x, int f, vector<int>& vis, vector<vector<int>>& adj){
        k+=f;
        vis[x]=k;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            kosaraju(u, f, vis, adj);
        }
        if(f)st.push_back(x);
    };
    
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        jda[y].push_back(x);
    }

    for(int i=1; i<=n; i++){
        if(!col[i])kosaraju(i, 1, col, adj);
    }

    k=0; for(auto &u:col)u=0;
    while(!st.empty()){
        auto x=st.back();
        st.pop_back();
        if(!col[x])k++, kosaraju(x, 0, col, jda);
    }
    
    vector<vector<int>> ady(k+1);
    vector<bitset<N>> dp(k+1);
    vector<int> vis(k+1, 0);
    
    function<void(int)> dfs = [&](int x){
        vis[x]=1;
        for(auto& u:ady[x]){
            if(!vis[u])dfs(u);
            dp[x]|=dp[u];
        }
        dp[x][x]=1;
    };

    for(int i=1; i<=n; i++){
        for(auto& u:adj[i]){
            if(col[u]==col[i])continue;
            ady[col[i]].push_back(col[u]);
        }
    }
    
    for(int i=1; i<=k; i++)if(!vis[i])dfs(i);

    for(int x, y; q--; ){
        cin>>x>>y;
        if(col[x]==col[y] || dp[col[x]][col[y]])cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}