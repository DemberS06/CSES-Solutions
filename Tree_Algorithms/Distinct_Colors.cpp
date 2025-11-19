// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<set<int>> f(n);
    vector<vector<int>> adj(n);
    vector<int> ans(n);

    for(int i=0, x; i<n; i++){
        cin>>x;
        f[i].insert(x);
    }

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dsu = [&](int x, int y){
        if(f[x].size()<f[y].size())swap(f[x], f[y]);
        for(auto& u:f[y])f[x].insert(u);
        f[y].clear();
    };

    function<void(int, int)> dfs = [&](int x, int p){
        for(auto& u:adj[x]){
            if(p==u)continue;
            dfs(u, x);
            dsu(x, u);
        }
        ans[x]=f[x].size();
    };

    dfs(0, 0);
    
    for(auto& u:ans)cout<<u<<' ';

    return 0;
}