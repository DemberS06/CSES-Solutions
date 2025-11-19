// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<vector<long long>> dp(n, vector<long long> (2, 0));
    vector<vector<int>> adj(n);
    vector<int> a(n, 0);
    
    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int p){
        for(auto& u:adj[x]){
            if(u==p)continue;
            dfs(u, x);
            a[x]+=a[u]+1;
            dp[x][0]+=dp[u][0];
        }dp[x][0]+=a[x];
        
    };
    
    function<void(int, int)> dfs2 = [&](int x, int p){
        long long b=dp[x][1]+dp[x][0];
        for(auto& u:adj[x]){
            if(u==p)continue;
            b-=dp[u][0]+a[u]+1;
            dp[u][1]=b+n-a[u]-1;
            b+=dp[u][0]+a[u]+1;
            dfs2(u, x);
        }
    };

    dfs(0, 0);
    dfs2(0, 0);

    for(auto& u:dp)cout<<u[0]+u[1]<<' ';

    return 0;
}