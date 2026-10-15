#include<bits/stdc++.h>

using namespace std;

const long long N=(1<<20);

pair<long long, int> f [N], g[N];
long long a[20], b[20];
long long n, p, q, P, Q;

long long cnt(long long x){
    long long res=0;
    for(int i=0, j=P-1; i<Q; i++){
        while(j>=0 && f[j].first+g[i].first>x)j--;
        res+=j+1;
    }
    return res-1;
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    cin>>n; p=n/2, q=n-p; P=(1<<p), Q=(1<<q);

    for(int i=0;i<p;i++)cin>>a[i];
    for(int i=0;i<q;i++)cin>>b[i];
    
    for(int i=0; i<P; i++){
        f[i]={0, i};
        for(int h=0; h<p; h++){
            if((f[i].second>>h)&1)f[i].first+=a[h];
        }
    }
    for(int i=0; i<Q; i++){
        g[i]={0, i};
        for(int h=0; h<q; h++){
            if((g[i].second>>h)&1)g[i].first+=b[h];
        }
    }

    sort(f, f+P);
    sort(g, g+Q);

    long long L=0; long long R=cnt(1ll<<n);
    long long l=1, r=f[P-1].first+g[Q-1].first, mt, x;
    
    while(l<r){
        mt=(l+r-1)/2; x=cnt(mt);
        if(x-L<R-x)l=mt+1, L=x;
        else r=mt, R=x;
    }

    vector<pair<int, int>> num;

    for(int i=0, j=P-1; i<Q && num.size()<2; i++){
        while(j>=0 && f[j].first+g[i].first>l)j--;
        while(j>=0 && f[j].first+g[i].first==l && num.size()<2){
            num.push_back({f[j].second, g[i].second});
            j--;
        } j+=(j<P-1);
    }

    x=num[0].first&num[1].first;
    num[0].first^=x; num[1].first^=x;
    x=num[0].second&num[1].second;
    num[0].second^=x; num[1].second^=x;
    
    vector<long long> s, t;
    for(auto& [u, v]:num){
        for(int h=0; h<p; h++){
            if((u>>h)&1)s.push_back(a[h]);
        }
        for(int h=0; h<q; h++){
            if((v>>h)&1)s.push_back(b[h]);
        }
        swap(s, t);
    }
    cout<<s.size()<<"\n";
    for(auto& u:s)cout<<u<<' '; cout<<"\n";
    cout<<t.size()<<"\n";
    for(auto& u:t)cout<<u<<' ';

    return 0;
}