#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0;
    cin>>n>>m;

    vector<vector<int>> adj(n+1), dis(n+1, vector<int> (20)), par=dis;
    vector<int> vis(n+1, 0), pre(n+1), pos(n+1);
    queue<int> q;

    for(int i=1, x; i<=n; i++){
        cin>>x; 
        if(x)q.push(i), vis[i]=1, dis[i][0]=0;
    }

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    while(!q.empty()){
        auto x=q.front(); q.pop();
        for(auto& u:adj[x]){
            if(vis[u])continue;
            vis[u]=1;
            dis[u][0]=dis[x][0]+1;
            q.push(u);
        }
    }

    function<void(int, int)> dfs = [&](int x, int y){
        pre[x]=++k; par[x][0]=y;
        for(int h=1, p=y; h<20; h++){
            dis[x][h]=min(dis[x][h-1], dis[p][h-1]);
            p=par[x][h]=par[p][h-1];
        }
        for(auto& u:adj[x]){
            if(u==y)continue;
            dfs(u, x);
        }
        pos[x]=k;
    }; dfs(1,1);

    function<bool(int, int)> is_parent = [&](int x, int y){
        return pre[x]<=pre[y]&&pos[y]<=pos[x];
    };

    function<int(int, int)> query = [&](int x, int y){
        int ans=0, mn=min(dis[x][0], dis[y][0]);
        for(int h=19; h>=0; h--){
            if(!is_parent(par[x][h], y)){
                ans+=(1<<h);
                mn=min(mn, dis[x][h]);
                x=par[x][h];
            }
            if(!is_parent(par[y][h], x)){
                ans+=(1<<h);
                mn=min(mn, dis[y][h]);
                y=par[y][h];
            }
        }
        if(!is_parent(x, y))ans++, mn=min(mn, dis[x][1]);
        if(!is_parent(y, x))ans++, mn=min(mn, dis[y][1]);

        return ans+2*mn;
    };
    
    for(int x, y; m--;){
        cin>>x>>y;
        cout<<query(x, y)<<'\n';
        continue;
    }

    return 0;
}