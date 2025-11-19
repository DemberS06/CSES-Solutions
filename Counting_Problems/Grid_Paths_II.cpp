// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

const long long N=2e6+6, mod=1e9+7; 

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    function<long long(long long, long long)> expbin = [&](long long x, long long y){
        long long res=1;
        while(y){
            if(y&1)res=res*x%mod;
            x=x*x%mod;
            y/=2;
        }
        return res;
    };
    
    vector<long long> f(N+1, 1), r=f;
    for(int i=1; i<=N; i++)f[i]=f[i-1]*i%mod, r[i]=expbin(f[i], mod-2);
    
    function<long long(long long, long long)> nenk = [&](long long x, long long y){
        return f[x]*r[y]%mod*r[x-y]%mod;
    };

    int n, m;
    cin>>n>>m;

    vector<pair<int, int>> v(m);
    for(auto& [x, y]:v)cin>>x>>y;
    v.push_back({n, n});

    sort(v.begin(), v.end());

    vector<long long> dp(m+1);

    for(int i=0; i<=m; i++){
        auto& [x, y]=v[i];
        dp[i]=nenk(x+y-2, x-1);
        for(int j=0; j<i; j++){
            auto& [p, q]=v[j];
            if(p>x || q>y)continue;
            dp[i]=(dp[i]-dp[j]*nenk(x+y-p-q, x-p))%mod;
        }
    }
    
    cout<<(dp[m]+mod)%mod;

    return 0;
}