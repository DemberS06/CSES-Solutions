// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0, ord=0;
    cin>>n>>m;
    while((1<<k)<2*n)k++;

    vector<vector<int>> adj(n+1), boss(n+1, vector<int> (k, 0));
    vector<int> pre(n+1), pos(n+1);

    for(int i=2; i<=n; i++){
        cin>>boss[i][0];
        adj[boss[i][0]].push_back(i);
    }

    function<void(int)> dfs = [&](int x){
        pre[x]=++ord;

        for(auto& u:adj[x])dfs(u);

        pos[x]=ord;
    }; dfs(1);
    
    for(int h=1; h<k; h++){
        for(int i=1; i<=n; i++){
            boss[i][h]=boss[boss[i][h-1]][h-1];
        }
    }

    while(m--){
        int x, y;
        cin>>x>>y;
        
        for(int h=k-1; h>=0; h--){
            int p=boss[x][h];
            if(!p)continue;
            if(pre[p]>pre[y] || pos[p]<pos[y])x=p;
        }if(pre[x]>pre[y] || pos[x]<pos[y])x=boss[x][0];
        
        cout<<x<<"\n";
    }

    return m+1;
}