#include<bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

struct Fenwick{
    int n;
    vector<long long> fwk;
    Fenwick(int _n):n(_n), fwk(n+1, 0){}
    void update(int p, long long x){
        for(int i=p+1; i<=n; i+=-i&i){
            fwk[i]+=x;
            if(fwk[i]>=md)fwk[i]-=md;
        }
    }
    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p){
            res+=fwk[p];
            if(res>=md)res-=md;
        }
        return res;
    }
    long long query(int l, int r){
        return (md+query(r+1)-query(l))%md;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    Fenwick f(n+1);
    vector<int> a(n);
    for(auto& u:a)cin>>u;
    map<int, int> mp;

    f.update(0, 1);
    for(int i=0, j=0; i<n; i++){
        mp[a[i]]++;
        while(mp[a[i]]>1)mp[a[j]]--, j++;
        f.update(i+1, f.query(j, i));
    }

    cout<<f.query(n, n);

    return 0;
}