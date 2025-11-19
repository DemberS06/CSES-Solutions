// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, root=0;
    cin>>n;

    vector<vector<int>> adj(n);
    vector<int> d(n, 0);
    
    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<int(int, int)> dfs = [&](int x, int p){
        int ans=x, w;

        for(auto& u:adj[x]){
            if(u==p)continue;
            d[u]=d[x]+1;
            w=dfs(u, x);
            if(d[w]>d[ans])ans=w;
        }
        
        return ans;
    };

    root=dfs(root, -1);
    d[root]=0;
    root=dfs(root, -1);

    cout<<d[root];

    return 0;
}