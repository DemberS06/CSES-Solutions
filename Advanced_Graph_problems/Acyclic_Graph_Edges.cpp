#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);
    vector<int> dis(n+1, 0);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int)> bfs = [&](int s){
        queue<int> q; q.push(s);
        
        while(!q.empty()){
            auto x=q.front(); q.pop();
            for(auto& u:adj[x]){
                if(!dis[u]){
                    cout<<x<<' '<<u<<"\n";
                    dis[u]=dis[x]+1;
                    q.push(u);
                    continue;
                }
                if(dis[u]<dis[x])continue;
                if(dis[u]==dis[x]){
                    if(x<u)cout<<x<<' '<<u<<"\n";
                    continue;
                }
                cout<<x<<' '<<u<<"\n";
            }
        }
    };

    for(int i=1; i<=n; i++){
        if(!dis[i])dis[i]=1, bfs(i);
    }

    return 0;
}