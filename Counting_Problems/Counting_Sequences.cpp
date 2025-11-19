// hola soy Dember :D

#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();

    function<long long(long long, long long)> expbin = [&](long long x, long long y){
        long long res=1;

        while(y){
            if(y&1)res=res*x%mod;
            x=x*x%mod;
            y/=2;
        }

        return res;
    };

    long long n, k, ans=0;
    cin>>n>>k;

    vector<long long> f(2*n+1, 1), r=f;
    for(int i=1; i<=2*n; i++)f[i]=i*f[i-1]%mod, r[i]=expbin(f[i], mod-2);

    function<long long(long long, long long)> nenk = [&](long long x, long long y){
        return f[x]*r[y]%mod*r[x-y]%mod;
    };

    for(int i=0; i<k; i++){
        if(i&1) ans-=expbin(k-i, n)*nenk(k, i)%mod;
        else    ans+=expbin(k-i, n)*nenk(k, i)%mod;
        ans%=mod;
        if(ans<0)ans+=mod;
    }

    cout<<ans;

    return 0;
}