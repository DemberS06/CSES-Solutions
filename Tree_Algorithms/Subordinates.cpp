// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<vector<int>> adj(n);
    vector<int> dp(n, 0);

    for(int i=1, x; i<n; i++){
        cin>>x;
        adj[--x].push_back(i);
    }

    function<void(int)> dfs = [&](int x){
        for(auto& u:adj[x]){
            dfs(u);
            dp[x]+=dp[u]+1;
        }
    };

    dfs(0);
    
    for(auto& u:dp)cout<<u<<' ';

    return 0;
}