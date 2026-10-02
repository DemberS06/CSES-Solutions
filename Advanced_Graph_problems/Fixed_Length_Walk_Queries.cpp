#include <bits/stdc++.h>

using namespace std;

const int N=2501;
long long dis[N][N][2];
vector<int> adj[N];

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    cin>>n>>m>>q;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            dis[i][j][0]=dis[i][j][1]=1e9+7;
        }
    }

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<vector<int>> vis(n+1, vector<int> (2, 0));

    auto bfs = [&] (int s){
        fill(vis.begin(), vis.end(), vector<int> (2, 0));
        queue<pair<int, int>> q; 
        vis[s][0]=1; dis[s][s][0]=0; q.push({s, 0});
        while(!q.empty()){
            auto [x, f]=q.front(); q.pop();
            for(auto& u:adj[x]){
                if(vis[u][f^1])continue;
                dis[s][u][f^1]=dis[s][x][f]+1;
                vis[u][f^1]=1;
                q.push({u, f^1});
            }
        }
    };

    for(int i=1; i<=n; i++){
        bfs(i);
    }

    for(int a, b, x; q--; ){
        cin>>a>>b>>x;
        if(dis[a][b][x&1]<=x)cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}