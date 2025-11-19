// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;
// hola soy Dember :D
#include <bits/stdc++.h>
 
using namespace std;
 
struct Fenwick{
    int n;
    vector<long long> sum;
 
    Fenwick(int _n): n(_n), sum(n+1, 0){}
 
    void update(int i, long long delta){
        for(; i<=n; i+=-i&i)sum[i]+=delta;
    }
 
    long long query(int i){
        long long res=0;
        for(; i>0; i-=-i&i)res+=sum[i];
        return res;
    }
 
    long long query(int l, int r){
        return query(r)-query(l-1);
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, ord=0;
    cin>>n>>m;

    vector<vector<int>> adj(n);
    vector<int> pre(n), pos(n), a(n);

    for(auto& u:a)cin>>u;

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int p){
        pre[x]=++ord;

        for(auto& u:adj[x]){
            if(u==p)continue;
            dfs(u, x);
        }

        pos[x]=ord;
    }; dfs(0, 0);

    Fenwick fwk(ord+5);

    for(int i=0; i<n; i++)fwk.update(pre[i], a[i]);

    while(m--){
        int t, x, y;
        cin>>t>>x; x--;
        
        if(t==1){
            cin>>y;
            fwk.update(pre[x], y-a[x]);
            swap(a[x], y);
        }
        if(t==2)cout<<fwk.query(pre[x], pos[x])<<"\n";
    }

    return m+1;
}