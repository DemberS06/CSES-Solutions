#include <bits/stdc++.h>

using namespace std;

struct Fenwick{
    int n;
    vector<long long> fwk;
    Fenwick(int _n):n(_n+1), fwk(n, 0){}
    void update(int p, long long delta){
        for(; p<=n; p+=-p&p)fwk[p]+=delta;
    }
    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p)res+=fwk[p];
        return res;
    }
    long long query(int l, int r){
        return query(r)-query(l-1);
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, cnt=0; cin>>n;

    map<int, int> cmp;
    vector<int> v(n);
    set<int> f;
    Fenwick F(n);

    for(auto& u:v){
        cin>>u;
        f.insert(u);
    }

    for(auto& u:f)cmp[u]=++cnt;
    for(auto& u:v)u=cmp[u];

    long long ans=0;
    for(auto& u:v){
        ans=max(ans, F.query(u+1, n));
        F.update(u, 1);
    }

    cout<<ans;

    return 0;
}