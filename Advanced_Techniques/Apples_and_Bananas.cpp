#include <bits/stdc++.h>

using namespace std;

const long long p1=998244353, p2=985661441;

long long expbin(long long x, long long y, long long mod){
    long long res=1;
    while(y){
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y/=2;
    }
    return res;
}

template<long long mod>
void ntt(vector<long long>& a, bool inv){
    int n=a.size();
    long long g=3, w, wk, x, y;

    for(int i=1, bit, j=0; i<n; i++){
        bit=(n>>1);
        for(; j&bit; bit>>=1)j^=bit; j^=bit;
        if(i<j)swap(a[i], a[j]);
    }

    for(int l=2; l<=n; l*=2){
        w=expbin(g, (mod-1)/l, mod);
        if(inv)w=expbin(w, mod-2, mod);
        for(int i=0; i<n; i+=l){
            wk=1;
            for(int k=0; 2*k<l; k++, wk=wk*w%mod){
                x=a[k+i], y=a[k+i+l/2]*wk%mod;
                a[k+i]=x+y;
                a[k+i+l/2]=x-y;
                if(a[k+i]>=mod)a[k+i]-=mod;
                if(a[k+i+l/2]<0)a[k+i+l/2]+=mod;
            }
        }
    }
    if(inv){
        w=expbin(n, mod-2, mod);
        for(auto&u:a)u=u*w%mod;
    }
}


int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int k, n, m, t=0;
    cin>>k>>n>>m;
    while((1<<t)<=2*k)t++; t=(1<<t);

    vector<long long> a(t, 0), b(t, 0);
    for(int x; n--;){
        cin>>x;
        a[x]++;
    }
    for(int x; m--;){
        cin>>x;
        b[x]++;
    }

    auto c=a, d=b;

    ntt<p1>(a, 0);
    ntt<p1>(b, 0);
    ntt<p2>(c, 0);
    ntt<p2>(d, 0);
    for(int i=0; i<t; i++){
        a[i]=a[i]*b[i]%p1;
        c[i]=c[i]*d[i]%p2;
    }
    ntt<p1>(a, 1);
    ntt<p2>(c, 1);

    long long rev=expbin(p1, p2-2, p2);
    for(int i=2; i<=2*k; i++){
        long long x=(p2+(c[i]-a[i])%p2)*rev%p2;
        x=a[i]+x*p1;
        cout<<x<<' ';
    }
    
    return 0;
}