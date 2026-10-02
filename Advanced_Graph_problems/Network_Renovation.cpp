#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    
    vector<vector<int>> adj(n+1);
    vector<int> v;


    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int y){
        if(adj[x].size()==1)v.push_back(x);
        for(auto& u:adj[x]){
            if(u==y)continue;
            dfs(u, x);
        }
    };

    for(int i=1; i<=n; i++){
        if(adj[i].size()==1)continue;
        dfs(i, i);
        break;
    }

    if(v.size()&1)v.push_back(v[0]);
    cout<<v.size()/2<<"\n";

    for(int i=0, t=v.size()/2; i<t; i++){
        cout<<v[i]<<' '<<v[i+t]<<"\n";
    }


    return 0;
}