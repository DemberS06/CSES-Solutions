#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, ans;
    cin>>n>>m; ans=n;

    vector<vector<int>> adj(n+1), jda(n+1);
    vector<int> vis(n+1, 0), a(n+1, 0);

    function<void(int)> dfs = [&](int x){
        if(vis[x]==1)a[x]=1;
        if(vis[x])return;
        vis[x]=1;
        for(auto& u:adj[x])dfs(u);
        vis[x]=2;
    };

    function<int(int)> check = [&](int x){
        if(!vis[x])return 1;
        if(a[x])return 0;
        vis[x]=0;
        int res=1;
        for(auto& u:jda[x])res&=check(u);
        return res;
    };

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        jda[x].push_back(y);
        jda[y].push_back(x);
    }

    for(int i=1; i<=n; i++)dfs(i);
    for(int i=1; i<=n; i++)if(vis[i])ans-=check(i);

    cout<<ans;

    return 0;
}