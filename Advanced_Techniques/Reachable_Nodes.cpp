#include <bits/stdc++.h>
 
using namespace std;
 
const int N=5e4+1;
 
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
 
    vector<vector<int>> adj(n+1);
    vector<bitset<N>> dp(n+1);
    vector<int> vis(n+1, 0);
 
    function<void(int)> dfs = [&](int x){
        vis[x]=1;
        for(auto& u:adj[x]){
            if(!vis[u])dfs(u);
            dp[x]|=dp[u];
        }
        dp[x][x].flip();;
    };
 
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
    }
 
    for(int i=1; i<=n; i++)if(!vis[i])dfs(i);
    for(int i=1; i<=n; i++)cout<<dp[i].count()<<' ';
 
    return 0;
}