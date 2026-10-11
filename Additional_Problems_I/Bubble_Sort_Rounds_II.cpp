#include<bits/stdc++.h>

using namespace std;

struct Fenwick{
    int n;
    vector<int> fwk;
    Fenwick(int _n):n(_n), fwk(n+1, 0){}
    void update(int p, int x){
        for(; p<=n; p+=-p&p)fwk[p]+=x;
    }
    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p)res+=fwk[p];
        return res;
    }
    int query(int l, int r){
        return query(r)-query(l-1);
    }
};  

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k, cnt=0; cin>>n>>k;
    vector<int> a(n), p(n), q(n), ans(n);
    map<int, int> mp;
    set<int> f;
    Fenwick F(n);
    
    for(auto& u:a){
        cin>>u;
        f.insert(u);
    }
    for(auto& u:f)mp[u]=++cnt;
    f.clear();

    for(int i=0; i<n; i++){
        p[i]=i-min(k, F.query(mp[a[i]]+1, n));
        F.update(mp[a[i]], 1);
        q[i]=i; f.insert(i);
    }

    sort(q.begin(), q.end(), [&](int &x, int& y){
        return a[x]<a[y];
    });

    for(auto& i:q){
        auto x=*f.lower_bound(p[i]);
        f.erase(x);
        ans[x]=a[i];
    }

    for(auto& u:ans)cout<<u<<' ';

    return 0;   
}