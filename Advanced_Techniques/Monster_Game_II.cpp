#include<bits/stdc++.h>

using namespace std;

const long long inf = 5e18;

struct LiChao{
    int n;
    vector<long long> a, b;
    LiChao(int _n):n(_n), a(4*n, 0), b(4*n, inf){}

    long long val(int i, long long x){
        return a[i]*x+b[i];
    }

    long long query(int i, int l, int r, long long x){
        if(l>r || l>x || r<x)return inf;
        if(l==r)return a[i]*x+b[i];
        int mt=(l+r)/2;
        return min({a[i]*x+b[i],
                query(2*i, l, mt, x),
                query(2*i+1, mt+1, r, x)});
    }

    void update(int i, int l, int r, long long m, long long q){
        if(l>r)return;
        if(m==a[i]){
            b[i]=min(q,b[i]);
            return;
        }

        long long mt=(l+r)/2;
        if(val(i, mt)>m*mt+q){
            swap(m, a[i]);
            swap(q, b[i]);
        }

        if(l==r)return;
        if(m>a[i])update(2*i, l, mt, m, q);
        else update(2*i+1, mt+1, r, m, q);
    }

    void push(long long m, long long q){
        update(1,1,n, m,q);
    }

    long long query(long long x){
        return query(1,1,n, x);
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, m, b;
    cin>>n>>m;
    LiChao C(1e6);
    C.push(m, 0);

    vector<long long> s(n), f(n);
    
    for(auto& u:s)cin>>u;
    for(auto& u:f)cin>>u;

    for(int i=0; i<n; i++){
        b=C.query(s[i]);
        C.push(f[i], b);
    }

    cout<<b;

    return 0;
}