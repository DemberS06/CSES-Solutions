#include <bits/stdc++.h>

using namespace std;

template<long long mod> 
long long expbin(long long x, long long y){
    long long res=1;
    while(y){
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

template<long long mod>
void ntt(vector<long long>& a, bool inv){
    int n=a.size();
    for(int i=1, j=0, b; i<n; i++){
        b=(n>>1);
        for(; b&j; b>>=1)j^=b; j^=b;
        if(i<j)swap(a[i], a[j]);
    }
    long long x, y, w, wk, g=3;
    for(int l=2; l<=n; l<<=1){
        w=expbin<mod>(g, (mod-1)/l);
        if(inv)w=expbin<mod>(w, mod-2);
        for(int i=0; i<n; i+=l){
            wk=1;
            for(int k=0; 2*k<l; k++,wk=wk*w%mod){
                x=a[i+k], y=a[i+k+l/2]*wk%mod;
                a[i+k]=x+y;
                a[i+k+l/2]=x-y;
                if(a[i+k]>=mod)a[i+k]-=mod;
                if(a[i+k+l/2]<0)a[i+k+l/2]+=mod;
            }
        }
    }

    if(inv){
        w=expbin<mod>(n, mod-2);
        for(auto& u:a)u=u*w%mod;
    }
}

const long long p1=998244353, p2=985661441;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s; cin>>s; 
    int n=s.size(), t=0;
    while((1<<t)<=2*n)t++; t=(1<<t);
    vector<long long> a(t, 0), b=a, c, d; a[0]++;
    long long z=0, sum=0;

    for(int i=0, x=0; i<n; i++){
        if(s[i]=='1')x++, z+=sum*(sum+1)/2, sum=0;
        else sum++;
        a[x]++;
    }z+=sum*(sum+1)/2;
    b=a; reverse(b.begin(), b.end());
    c=a, d=b;
    ntt<p1>(a, 0);
    ntt<p2>(c, 0);
    ntt<p1>(b, 0);
    ntt<p2>(d, 0);
    for(int i=0; i<t; i++)a[i]=a[i]*b[i]%p1;
    for(int i=0; i<t; i++)c[i]=c[i]*d[i]%p2;
    ntt<p1>(a, 1);
    ntt<p2>(c, 1);

    long long x, p=expbin<p2>(p1, p2-2);
    cout<<z<<' ';
    for(int i=0; i<n; i++){
        x=(p2+(c[i]-a[i])%p2)*p%p2;
        cout<<a[i]+x*p1<<' ';
    }

    return 0;
}