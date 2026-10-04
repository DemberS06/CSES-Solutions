#include <bits/stdc++.h>

using namespace std;

struct SGT{
    int n;
    vector<long long> sgt;
    SGT(int _n):n(_n), sgt(4*n, 0){}
    void update(int i, int l, int r, int p, long long x){
        if(l>r || p<l || p>r)return;
        if(l==r){
            sgt[i]=x;
            return;
        }
        update(2*i+1,l,(l+r)/2,p,x);
        update(2*i,(l+r)/2+1,r,p,x);
        sgt[i]=max(sgt[2*i], sgt[2*i+1]);
    }
    long long query(int i, int l, int r, int p, int q){
        if(l>r || p>r || q<l)return 0;
        if(l>=p && r<=q)return sgt[i];
        return max(query(2*i+1,l,(l+r)/2,p,q),
                   query(2*i,(l+r)/2+1,r,p,q));
    }

    void update(int p, long long x){
        update(1,1,n,p,x);
    }
    long long query(int l, int r){
        return query(1,1,n,l,r);
    }
};

struct Fenwick{
    int n;
    vector<long long> fwk;
    Fenwick(int _n):n(_n), fwk(n+1, 0){}
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
    int n; cin>>n;
    vector<int> v(n);
    for(auto& u:v)cin>>u;

    function<long long()> s1 = [&](){
        long long res=0;
        Fenwick F(n+1);
        for(auto& u:v){
            res+=F.query(u, n);
            F.update(u, 1);
        }
        return res;
    };

    function<int()> s2 = [&](){
        int res=n;
        vector<int> vis(n, 0);
        for(int i=0; i<n; i++){
            if(vis[i])continue;
            res--;
            for(int x=v[i]; !vis[x-1]; x=v[x-1])vis[x-1]=1;
        }
        return res;
    };

    function<long long()> s3 = [&](){
        SGT S(n+1);
        for(auto& u:v){
            S.update(u, 1+S.query(1, u));
        }
        return n-S.query(1, n);
    };

    function<int()> s4 = [&](){
        vector<int> p(n+1);
        for(int i=0; i<n; i++)p[v[i]]=i;
        for(int i=n; i>1; i--){
            if(p[i]<p[i-1])return i-1;
        }
        return 0;
    };

    cout<<s1()<<' '; 
    cout<<s2()<<' ';
    cout<<s3()<<' ';
    cout<<s4()<<' ';

    return 0;
}