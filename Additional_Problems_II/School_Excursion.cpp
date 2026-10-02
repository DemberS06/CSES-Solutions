#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);;
    vector<int> a(n+1, 0), vis(n+1, 0), v;v.reserve(n);
    bitset<N> dp; dp[0].flip();

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<int(int)> dfs = [&](int x){
        int res=1;
        vis[x]=1;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            res+=dfs(u);
        }
        return res;
    };

    for(int i=1; i<=n; i++)if(!vis[i])a[dfs(i)]++;

    for(int i=1; i<=n; i++){
        if(!a[i])continue;
        while(!(a[i]&1))v.push_back(i), a[i]--;
        v.push_back(i);
        a[2*i]+=a[i]/2;
    }

    for(auto &u:v)dp|=(dp<<u);
    for(int i=1; i<=n; i++)cout<<dp[i];


    return 0;
}