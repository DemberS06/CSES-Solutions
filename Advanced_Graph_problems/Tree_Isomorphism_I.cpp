#include <bits/stdc++.h>

using namespace std;

const long long md1=1e9+7, md2=998244353, P=99991, Q=100003;

pair<long long, long long> dfs(int x, int y, vector<vector<int>>& adj){
    long long sa=0, sb=1;
    for(auto& u:adj[x]){
        if(u==y)continue;
        auto [a,b]=dfs(u, x, adj);
        sa+=a; sb=sb*b%md2;
    }sa%=md1;
    if(!sa)sa++;
    if(!sb)sb++;
    return {sa*P%md2, (sb+Q)%md1};
}

void solve(){
    int n;
    cin>>n;

    vector<vector<int>> a(n+1), b(n+1);

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    
    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        b[x].push_back(y);
        b[y].push_back(x);
    }

    if(dfs(1, 1, a)==dfs(1, 1, b))cout<<"YES\n";
    else                          cout<<"NO\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int t;
    cin>>t;
    
    while(t--)solve();

    return 0;
}
