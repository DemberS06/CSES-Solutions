// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

const long long N=5e3+3, mod=1e9+7; 

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

    string s;
    cin>>s;
    int n=s.size();

    vector<int> v(26, 0);
    for(auto& u:s)v[u-'a']++;

    sort(v.rbegin(), v.rend());
    while(!v.back())v.pop_back();

    vector<long long> dp={1};

    for(auto& u:v){
        vector<long long> ndp(dp.size()+u, 0);
        for(int i=0; i<dp.size(); i++){
            if(!dp[i])continue;
            for(int j=1; j<=u; j++){
                ndp[i+j]=(ndp[i+j]+dp[i]*nenk(i+j, i)%mod*nenk(u-1, j-1))%mod;
            }
        }
        swap(dp, ndp);
    }

    long long ans=0;
    for(int i=0; i<dp.size(); i++){
        if((n-i)&1)ans=(ans-dp[i])%mod;
        else ans=(ans+dp[i])%mod;
    }
    if(ans<0)ans+=mod;
    cout<<ans;
    

    return 0;
}