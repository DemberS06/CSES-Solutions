// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std; 

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, root=0;
    cin>>n;

    vector<vector<int>> adj(n);
    vector<int> a(n, 1);

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int p){
        for(auto& u:adj[x]){
            if(u==p)continue;
            dfs(u, x);
            a[x]+=a[u];
        }
    };dfs(root, 0);

    function<int(int)> centroid = [&](int x){
        int p=adj[x].back();

        for(auto& u:adj[x]){
            if(a[u]>a[p])p=u;
        }

        if(a[p]<=n/2)return x;
        a[x]-=a[p];
        a[p]+=a[x];
        return centroid(p);
    };

    if(!adj[root].empty())root=centroid(root);
    cout<<root+1;

    return 0;
}