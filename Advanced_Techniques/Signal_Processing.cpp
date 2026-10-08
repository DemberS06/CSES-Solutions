#include <bits/stdc++.h>

using namespace std;

const long long mod=2281701377;

long long expbin(long long x, long long y){
    long long res=1;
    while(y){
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

void ntt(vector<long long>& a, bool inv){
    int n=a.size();
    for(int i=1, j=0, bit; i<n; i++){
        bit=(n>>1);
        for(; j&bit; bit>>=1)j^=bit; j^=bit;
        if(i<j)swap(a[i], a[j]);
    }
    
    long long g=3, w, wk, x, y;
    for(int l=2; l<=n; l<<=1){
        w=expbin(g, (mod-1)/l);
        if(inv)w=expbin(w, mod-2);
        for(int i=0; i<n; i+=l){
            wk=1;
            for(int k=0; 2*k<l; k++, wk=wk*w%mod){
                x=a[i+k], y=a[i+k+l/2]*wk%mod;
                a[i+k]=x+y;
                a[i+k+l/2]=x-y;
                if(a[i+k]>=mod)a[i+k]-=mod;
                if(a[i+k+l/2]<0)a[i+k+l/2]+=mod;
            }
        }
    }

    if(inv){
        w=expbin(n, mod-2);
        for(auto& u:a)u=u*w%mod;
    }
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, t=0;
    cin>>n>>m;
    while((1<<t)<n+2*m)t++; t=(1<<t);
    vector<long long> a(t, 0), b(t, 0);
    for(int i=1; i<=n; i++)cin>>a[i+m];
    for(int i=1; i<=m; i++)cin>>b[t-i];
    
    ntt(a, 0);
    ntt(b, 0);
    for(int i=0; i<t; i++)a[i]=a[i]*b[i]%mod;
    ntt(a, 1);

    for(int i=1; i<n+m; i++)cout<<a[i]<<' ';

    return 0;
}