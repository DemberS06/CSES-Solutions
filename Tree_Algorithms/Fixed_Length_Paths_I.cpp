// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k, deep;
    long long ans=0;
    cin>>n>>k;

    vector<vector<int>> adj(n);
    vector<int> a(n), c(n, 0), fr(k+1, 0), st;
    st.reserve(n);

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--y].push_back(--x);
        adj[x].push_back(y);
    }

    function<void(int, int)> getsize = [&](int x, int p){
        a[x]=1;
        for(auto& u:adj[x]){
            if(u==p || c[u])continue;
            getsize(u, x);
            a[x]+=a[u];
        }
    };

    function<void(int, int, int, int)> dfs = [&](int x, int p, int t, int d){
        if(d>k)return;
        if(t)     fr[d]++;
        else ans+=fr[k-d];      
        for(auto& u:adj[x]){
            if(u==p || c[u])continue;
            dfs(u, x, t, d+1);
        }  
    };

    function<int(int, int, int)> centroid = [&](int x, int p, int sz){
        for(auto& u:adj[x]){
            if(u==p || c[u])continue;
            if(a[u]>sz/2)return centroid(u, x, sz);
        }

        return x;
    };

    st.push_back(0);
    fr[0]=1;

    while(!st.empty()){
        auto x=st.back();
        st.pop_back();

        getsize(x, x);
        x=centroid(x, x, a[x]);
        c[x]=1;
        
        for(auto& u:adj[x]){
            if(c[u])continue;
            dfs(u, x, 0, 1);
            dfs(u, x, 1, 1);
        }
    
        for(deep=1; deep<=k; deep++){
            if(!fr[deep])break;
            fr[deep]=0;
        }
        if(deep<=k/2)continue;

        for(auto& u:adj[x]){
            if(c[u])continue;
            st.push_back(u);
        }
    }

    cout<<ans;

    return 0;
}