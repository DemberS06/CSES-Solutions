#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n,m, ans=1e9;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int)> bfs = [&](int s){
        vector<int> dis(n+1, 0);
        queue<pair<int, int>> q; q.push({s, s}); dis[s]=1;

        while(!q.empty()){
            auto [x, y] = q.front(); q.pop();
            for(auto& u:adj[x]){
                if(u==y)continue;
                if(dis[u])ans=min(ans, dis[x]+dis[u]-1);
                else dis[u]=dis[x]+1, q.push({u, x});
            }
        }
    };

    for(int i=1; i<=n; i++)bfs(i);

    if(ans==1e9)cout<<"-1";
    else cout<<ans;

    return 0;
}