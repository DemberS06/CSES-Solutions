#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m, k; cin>>n>>m; k=(1<<n)-1;

    vector<int> col(n, 1), p(k+1, 0), dp(k+1, 1);
    vector<vector<int>> adj(n, vector<int> (n, 0));

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;x--; y--;
        adj[x][y]=adj[y][x]=1;
    }

    for(int i=1, j, b; i<=k; i++){
        b=i^(-i&i); dp[i]=dp[b];
        for(int h=0, t=-i&i; h<n; h++){
            if((t>>h)&1)j=h;
        }
        for(int h=0; h<n; h++){
            if((b>>h)&1 && adj[j][h])dp[i]=0;
        }
    }dp[0]=0;

    for(int i=1; i<=k; i++){
        if(dp[i])continue;
        for(int h=i; h; h=(h-1)&i){
            if(dp[h]!=1)continue;
            if(!dp[i] || dp[i]>dp[i^h]+1)p[i]=i^h, dp[i]=dp[i^h]+1;
        }
    }

    for(int i=k, c=1, j; i; i=p[i], c++){
        j=i^p[i];
        for(int h=0; h<n; h++){
            if((j>>h)&1)col[h]=c;
        }
    }
    
    cout<<dp[k]<<"\n";
    for(auto& u:col)cout<<u<<' ';cout<<"\n";
    
    return 0;
}