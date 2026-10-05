#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);
    vector<int> vis(n+1, 0);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }m-=n;

    function<void(int)> dfs = [&](int x){
        vis[x]=1;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            dfs(u);
        }
    };

    for(int i=1; i<=n; i++){
        if(vis[i])continue;
        dfs(i);
        m++;
    }

    long long res=1;
    while(m--){
        res+=res;
        if(res>=md)res-=md;
    }

    cout<<res;

    return 0;
}