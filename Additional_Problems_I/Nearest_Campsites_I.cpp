#include<bits/stdc++.h>

using namespace std;

const long long N=1e6+1;

struct SGT{
    int n;
    vector<int> sgt;
    SGT(int _n):n(_n), sgt(4*n, 2e9){}
    void update(int i, int l, int r, int p, int x){
        if(l>r || l>p || r<p)return;
        if(l==r){
            sgt[i]=min(sgt[i], x);
            return;
        }
        update(2*i+1, l, (l+r)/2, p, x);
        update(2*i, (l+r)/2+1, r, p, x);
        sgt[i]=min(sgt[2*i], sgt[2*i+1]);
    }
    void update(int x, int p){
        update(1,1,n, p, x);
    }
    int query(int i, int l, int r, int p, int q){
        if(l>r || l>q || r<p)return 2e9;
        if(l>=p && r<=q)return sgt[i];
        return min(query(2*i+1, l, (l+r)/2, p, q),
                   query(2*i, (l+r)/2+1, r, p, q));
    }
    int query(int l, int r){
        return query(1,1,n, l, r);
    }
};

vector<pair<int, int>> s[N];

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m; cin>>n>>m;
    
    for(int i=0, p, q; i<n; i++){
        cin>>p>>q;
        s[p].push_back({0, q});
    }
    for(int i=0, p, q; i<m; i++){
        cin>>p>>q;
        s[p].push_back({i+1, q});
    }

    vector<int> dis(m+1, 2e9);
{
    SGT L(N), R(N);
    for(int h=1; h<N; h++){
        for(auto& [i, x]:s[h]){
            if(!i){
                L.update(-h-x, x);
                R.update(x-h, x);
                continue;
            }
            dis[i]=min(dis[i], h+x+L.query(1, x));
            dis[i]=min(dis[i], h+R.query(x, N)-x);
        }
    }
}
{
    SGT L(N), R(N);
    for(int h=N-1; h>0; h--){
        for(auto& [i, x]:s[h]){
            if(!i){
                L.update(h-x, x);
                R.update(x+h, x);
                continue;
            }
            dis[i]=min(dis[i], -h+x+L.query(1, x));
            dis[i]=min(dis[i], -h+R.query(x, N)-x);
        }
    }
}
    
    int ans=0;
    for(int i=1; i<=m; i++)ans=max(ans, dis[i]);
    cout<<ans;

    return 0;
}