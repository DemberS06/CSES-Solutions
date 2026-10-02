#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);
    vector<int> low(n+1, n+1), pre(n+1, 0);
    vector<int> ans; ans.reserve(n);

    function<void(int, int)> dfs = [&](int x, int y){
        low[x]=pre[x]=++k;
        int cnt=0, ok=0;
        for(auto& u:adj[x]){
            if(u==y)continue;
            if(pre[u])low[x]=min(low[x], pre[u]);
            else {
                dfs(u, x), low[x]=min(low[x], low[u]), cnt++;
                if(low[u]>=pre[x])ok=1;
            }
        }

        if(x==y){
            if(cnt>1)ans.push_back(x);
            return;
        }
        if(ok)ans.push_back(x);
    };

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for(int i=1; i<=n; i++)if(!pre[i])dfs(i, i);

    cout<<ans.size()<<"\n";
    for(auto& u:ans)cout<<u<<' ';

    return 0;
}