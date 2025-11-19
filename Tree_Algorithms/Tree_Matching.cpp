// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<vector<int>> adj(n), dp(n, vector<int> (2, 0));

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int p){
        for(auto& u:adj[x]){
            if(u==p)continue;
            dfs(u, x);
            dp[x][1]+=dp[u][0];
        }
        for(auto& u:adj[x]){
            if(u==p)continue;
            dp[x][0]=max(dp[x][0], dp[x][1]+dp[u][1]-dp[u][0]+1);
        }
    };

    dfs(0, 0);
    
    cout<<dp[0][0];
   
    return 0;
}