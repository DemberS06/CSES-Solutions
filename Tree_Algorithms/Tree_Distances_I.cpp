// hola soy Dember :D
#include<bits/stdc++.h>

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
            dp[x][0]=max(dp[x][0], dp[u][0]+1);
        }
    };
    
    function<void(int, int)> dfs2 = [&](int x, int p){
        int a=dp[x][1],b=0;
        for(auto& u:adj[x]){
            if(u==p)continue;
            if(dp[u][0]+1>=a)b=a, a=dp[u][0]+1;
            else b=max(b, dp[u][0]+1);
        }
        for(auto& u:adj[x]){
            if(u==p)continue;
            if(dp[u][0]+1==a)dp[u][1]=b+1;
            else dp[u][1]=a+1;
            dfs2(u, x);
        }
    };

    dfs(0, 0);
    dfs2(0, 0);

    for(auto& u:dp)cout<<max(u[0], u[1])<<' ';

    return 0;
}