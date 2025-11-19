// hola soy Dember :D
#include <bits/stdc++.h>
 
using namespace std;
 
const int N=2e5+1;
 
int c[N], fr[N], l, r, deep;
long long n, ans, fwk[N], a[N];
vector<int> adj[N];
 
void update(int i){
    for(++i; i<=r+1; i+=-i&i)fwk[i]++;
}
 
void update(int i, long long delta){
    for(++i; i<=r+1; i+=-i&i)fwk[i]+=delta;
}
 
long long query(int i){
    long long res=0;
    for(++i; i>0; i-=-i&i)res+=fwk[i];
    return res;
}
 
int getsize(int x, int p){
    a[x]=1;
    for(auto& u:adj[x]){
        if(u==p || c[u])continue;
        a[x]+=getsize(u, x);
    }
    return a[x];
}
 
int centroid(int x, int p, int sz){
    for(auto& u:adj[x]){
        if(u==p || c[u])continue;
        if(a[u]>sz/2){
            a[x]-=a[u];
            a[u]=sz;
            return centroid(u, x, sz);
        }
    }
 
    return x;
};
 
void dfs_query(int x, int p, int d){
    deep=max(deep, d);
    ans+=query(r-d);
    if(l>d)ans-=query(l-d-1); 
    for(auto& u:adj[x]){
        if(u==p || c[u])continue;
        if(d<r)dfs_query(u, x, d+1);
    }  
}
 
void dfs_update(int x, int p, int d){
    update(d);
    fr[d]++;
    for(auto& u:adj[x]){
        if(u==p || c[u])continue;
        if(d<r)dfs_update(u, x, d+1);
    }  
}
 
void solve(int x){
    x=centroid(x, x, getsize(x, x));
    c[x]=1; deep=0;

    if(l==1 && a[x]<=r){
        ans+=a[x]*(a[x]-1)/2;
        return;
    }
    
    for(auto& u:adj[x]){
        if(c[u])continue;
        dfs_query(u, x, 1);
        dfs_update(u, x, 1);
    }
 
    for(int i=1; i<=deep; i++){
        update(i, -fr[i]);
        fr[i]=0;
    }
 
    if(deep<=l/2)return;
 
    for(auto& u:adj[x]){
        if(c[u])continue;
        solve(u);
    }
}
 
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    cin>>n>>l>>r;
 
    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--y].push_back(--x);
        adj[x].push_back(y);
    }
 
    update(0, 1);
 
    solve(n-1);
 
    cout<<ans;
 
    return 0;
}