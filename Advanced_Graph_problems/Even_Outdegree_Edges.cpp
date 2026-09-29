#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m;
    cin>>n>>m;
    if(m&1){
        cout<<"IMPOSSIBLE";
        return 0;
    }

    vector<pair<int, int>> ans; ans.reserve(m);
    vector<vector<int>> adj(n+1);
    vector<int> p(n+1, 0), d(n+1), vis(n+1, 0);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int y){
        vis[x]=1;
        for(auto& u:adj[x]){
            if(u==y)continue;
            if(vis[u]){
                if(d[u]>d[x])ans.push_back({x, u}), p[x]++;
                continue;
            }
            d[u]=d[x]+1;
            dfs(u, x);
        }
        if(!y)return;
        if(p[x]&1)ans.push_back({x, y}), p[x]++;
        else ans.push_back({y, x}), p[y]++;
        return;
    };

    
    for(int i=1; i<=n; i++){
        if(vis[i])continue;
        dfs(i, 0);
        if(p[i]&1){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
    }

    for(auto& [x, y]:ans)cout<<x<<' '<<y<<"\n";

    return 0;
}