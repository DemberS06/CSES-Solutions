#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q, k=0;
    cin>>n>>m>>q;

    vector<vector<int>> adj(n+1), par(n+1, vector<int> (20));
    vector<int> pre(n+1, 0), pos(n+1, 0), low(n+1, 0), A(n+1, 0);

    function<void(int, int)> dfs = [&](int x, int y){
        int ok=0, cnt=0;
        low[x]=pre[x]=++k;
        par[x][0]=y;
        for(int h=1; h<20; h++){
            par[x][h]=par[par[x][h-1]][h-1];
        }

        for(auto& u:adj[x]){
            if(u==y)continue;
            if(pre[u])low[x]=min(low[x], pre[u]);
            else{
                dfs(u, x);
                cnt++;
                if(low[u]>=pre[x])ok=1;
                low[x]=min(low[x], low[u]);
            }
        }
        if(x==y && cnt>1)A[x]=1;
        if(x!=y && ok)A[x]=1;
        pos[x]=++k;
    };

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for(int i=1; i<=n; i++)if(!pre[i])dfs(i, i);

    function<bool(int, int)> is_parent = [&](int x, int y){
        return pre[x]<=pre[y] && pos[y]<=pos[x];
    };

    function<int(int, int)> get_parent = [&](int x, int y){
        for(int h=19; h>=0; h--){
            if(is_parent(par[y][h], x))continue;
            y=par[y][h];
        }
        return y;
    };

    for(int a, b, c, x, y; q--;){
        cin>>a>>b>>c;
        if(a==c || b==c){
            cout<<"NO\n";
            continue;
        }
        if(!A[c]){
            cout<<"YES\n";
            continue;
        }
        x=is_parent(c, a);
        y=is_parent(c, b);
        if(!x && !y){
            cout<<"YES\n";
            continue;
        }

        if(x)a=get_parent(c, a);
        if(y)b=get_parent(c, b);

        if((!y && low[a]<pre[c]) || (!x && low[b]<pre[c])){
            cout<<"YES\n";
            continue;
        }

        if(!x || !y){
            cout<<"NO\n";
            continue;
        }
        
        if(a==b || (low[b]<pre[c] && low[a]<pre[c])){
            cout<<"YES\n";
            continue;
        }

        cout<<"NO\n";
    }

    return 0;
}