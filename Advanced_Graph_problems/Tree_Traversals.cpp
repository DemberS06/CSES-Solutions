#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n;
    cin>>n;
    vector<int> pre(n), in(n+1), pos; pos.reserve(n);
    vector<vector<int>> adj(n+1);

    for(auto& u:pre)cin>>u;
    for(int i=0, x; i<n; i++){
        cin>>x;
        in[x]=i;
    }
    
    function<void(int, int, int)> solve = [&](int l, int r, int d){
        if(l>=r)return;
        int x=pre[l+d], p=in[x];
        solve(l, p-1, d+1);
        solve(p+1, r, d);
        if(l+d!=p+d)adj[x].push_back(pre[l+1+d]);
        if(p+1<=r)adj[x].push_back(pre[p+1+d]);
        return;
    }; solve(0, n-1, 0);

    function<void(int, int)> dfs= [&](int x, int y){
        for(auto& u:adj[x]){
            if(u==y)continue;
            dfs(u, x);
        }
        pos.push_back(x);
    };dfs(pre[0], 0);

    for(auto& u:pos)cout<<u<<' ';

    return 0;
}