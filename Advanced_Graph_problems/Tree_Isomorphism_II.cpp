#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

pair<int, int> centroid(vector<vector<int>>& adj, vector<int> sz){
    int root=1, x=1;
    
    while(true){
        x=adj[root].back();
        for(auto& u:adj[root]){
            if(sz[u]>sz[x])x=u;
        }
        if(2*sz[x]<=sz[root])break;
        swap(sz[root], sz[x]);
        swap(root, x);
        sz[x]=sz[root]-sz[x];
    }

    if(sz[root]!=2*sz[x])x=root;
    return {root, x};
}

vector<int> sz(vector<vector<int>>& adj){
    int n=adj.size();;
    vector<int> dp(n+1, 0);

    function<void(int, int)> dfs = [&](int x, int y){
        dp[x]++;
        for(auto& u:adj[x]){
            if(u==y)continue;
            dfs(u, x);
            dp[x]+=dp[u];
        }
    }; dfs(1, 1);

    return dp;
}

long long hsh(int x, int y, vector<vector<int>>& adj, long long p){
    long long ans=1;
    for(auto& u:adj[x]){
        if(u==y)continue;
        ans=ans*(p+hsh(u,x,adj, p*(adj[u].size()+1)%md))%md;
    }
    return ans;
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

    auto [c1, c2] = centroid(a, sz(a));
    auto [c3, c4] = centroid(b, sz(b));

    long long v1=hsh(c1, c1, a, 1), v2=hsh(c2, c2, a, 1);
    long long v3=hsh(c3, c3, b, 1), v4=hsh(c4, c4, b, 1);

    if(v1==v3 || v1==v4 || v2==v3 || v2==v4)cout<<"YES\n";
    else cout<<"NO\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int t;
    cin>>t;
    while(t--)solve();

    return 0;
}