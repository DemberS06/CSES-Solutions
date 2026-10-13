#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, q, root, cnt=0, s=0; cin>>n>>q;
    vector<int> c(n+1), d(n+1, 0), p(n+1, 0), pre(n+1), pos(n+1);
    vector<vector<int>> par(n+1, vector<int> (20)), adj(n+1);

    for(int i=1; i<=n; i++){
        cin>>c[i];
        if(c[i])root=i;
    }

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<bool(int, int)> dfs = [&](int x, int y){
        pre[x]=++cnt; par[x][0]=y;
        for(int h=1; h<20; h++){
            par[x][h]=par[par[x][h-1]][h-1];
        }
        if(c[x])d[x]=1;
        for(auto& u:adj[x]){
            if(u==y)continue;
            p[u]=p[x]+1;
            d[x]|=dfs(u, x);
        }
        pos[x]=cnt;
        s+=d[x];
        return d[x];
    };dfs(root, root);

    function<void(int, int)> dfs2 = [&](int x, int y){
        if(d[x])d[x]=x;
        else d[x]=d[y];
        for(auto& u:adj[x]){
            if(u==y)continue;
            dfs2(u, x);
        }
    };dfs2(root, root);

    function<bool(int, int)> is_par = [&](int x, int y){
        return pre[x]<=pre[y] && pos[x]>=pos[y];
    };

    function<int(int, int)> lca = [&](int x, int y){
        if(is_par(x, y))return x;
        if(is_par(y, x))return y;
        for(int h=19; h>=0; h--){
            if(is_par(par[x][h], y))continue;
            x=par[x][h];
        }
        return par[x][0];
    };

    long long ans;
    
    for(int a, b, c; q--;){
        cin>>a>>b; c=lca(a, b);
        ans=2*(s-1-p[d[a]]-p[d[b]]+p[d[c]]);
        cout<<ans+p[a]+p[b]<<"\n";
    }

    return 0;
}