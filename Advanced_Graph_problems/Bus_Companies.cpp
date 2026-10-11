#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m; cin>>n>>m;
    vector<vector<pair<int, long long>>> adj(n+m+1);
    vector<long long> c(m), dis(n+m+1, -1), vis(n+m+1, 0);
    for(auto& u:c)cin>>u;

    for(int i=0, k; i<m; i++){
        cin>>k;
        for(int j=0, x; j<k; j++){
            cin>>x;
            adj[x].push_back({i+n+1, c[i]});
            adj[i+n+1].push_back({x, 0});
        }
    }


    set<pair<long long, int>> f;
    f.insert({0, 1});
    while(!f.empty()){
        auto [w, x]=*f.begin();
        f.erase(f.begin());
        if(vis[x])continue;
        dis[x]=w; vis[x]=1;
        for(auto& [u, c]:adj[x]){
            if(vis[u])continue;
            f.insert({w+c, u});
        }
    }

    for(int i=1; i<=n; i++)cout<<dis[i]<<' ';

    return 0;
}