#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, ok=1;
    cin>>n>>m;
    vector<vector<pair<int, long long>>> adj(n+1);
    vector<long long> p(n+1, 0);
    vector<int> vis(n+1, 0);

    function<void(int x)> dfs = [&](int x){
        vis[x]=1;
        for(auto& [u, w]:adj[x]){
            if(vis[u]){
                if(p[u]!=p[x]+w)ok=0;
                continue;
            }
            p[u]=p[x]+w;
            dfs(u);
        }
    };

    for(int i=0, l, r, s; i<m; i++){
        cin>>l>>r>>s;
        adj[l-1].push_back({r, s});
        adj[r].push_back({l-1, -s});
    }

    for(int i=0; i<=n; i++){
        if(vis[i])continue;
        dfs(i);
    }

    if(!ok){
        cout<<"NO\n";
        return 0;
    }

    cout<<"YES\n";
    for(int i=1; i<=n; i++)cout<<p[i]-p[i-1]<<" ";

    return 0;
}