#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);
    vector<int> a(n+1, 0), ans; ans.reserve(n);
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[y].push_back(x);
        a[x]++;
    }

    set<int> f;

    for(int i=1; i<=n; i++){
        if(!a[i])f.insert(i);
    }

    while(!f.empty()){
        auto x=*f.rbegin(); f.erase(x);
        ans.push_back(x);
        for(auto& u:adj[x]){
            a[u]--;
            if(!a[u])f.insert(u);
        }
    }

    reverse(ans.begin(), ans.end());

    for(auto& u:ans)cout<<u<<' ';

    return 0;
}