#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    int n, m, k;
    cin>>n>>m>>k;

    vector<int> vis(n+1, 0), v(n+1, 0);
    vector<vector<int>> adj(n+1), dis(n+1, vector<int> (2, 1e9));
    queue<int> q;

    for(int i=0, x; i<k; i++){
        cin>>x;
        v[x]=1;
        dis[x][0]=0; vis[x]=x;
        q.push(x);
    }

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    while(!q.empty()){
        auto x=q.front(); q.pop();

        for(auto& u:adj[x]){
            if(!vis[u]){
                vis[u]=vis[x];
                dis[u][0]=dis[x][0]+1;
                q.push(u);
                continue;
            }
            if(vis[x]==vis[u])continue;
            dis[vis[u]][1]=min(dis[vis[u]][1], dis[u][0]+dis[x][0]+1);
            dis[vis[x]][1]=min(dis[vis[x]][1], dis[u][0]+dis[x][0]+1);
        }
    }

    for(int i=1; i<=n; i++){
        if(dis[i][v[i]]==1e9)cout<<"-1 ";
        else cout<<dis[i][v[i]]<<' ';
    }

    return 0;
}