// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0, ord=0;
    cin>>n>>m;
    while((1<<k)<2*n)k++;

    vector<vector<int>> adj(n+1), boss(n+1, vector<int> (k, 0));
    vector<int> pre(n+1), pos(n+1), d(n+1, 0);

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    function<void(int, int)> dfs = [&](int x, int p){
        pre[x]=++ord;
        boss[x][0]=p;
        
        for(int h=1; h<k; h++)boss[x][h]=boss[boss[x][h-1]][h-1];
        
        for(auto& u:adj[x]){
            if(u==p)continue;
            d[u]=d[x]+1;
            dfs(u, x);
        }

        pos[x]=ord;
    }; dfs(1, 0);

    while(m--){
        int x, y, p;
        cin>>x>>y;p=x;

        for(int h=k-1; h>=0; h--){
            int q=boss[p][h];
            if(!q)continue;
            if(pre[q]>pre[y] || pos[q]<pos[y])p=q;
        }if(pre[p]>pre[y] || pos[p]<pos[y])p=boss[p][0]; 
        
        cout<<d[x]+d[y]-2*d[p]<<"\n";
    }

    return m+1;
}