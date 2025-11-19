// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

const long long N=5e3, mod=1e9+7; 

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
    
    vector<vector<long long>> dp(N+1, vector<long long> (N+1, 0)); 
    dp[0][0]=1;

    for(int i=1; i<=N; i++){
        for(int j=0; j<N; j++){
            dp[i][j]=(dp[i][j]+(j+1)*dp[i-1][j])%mod;
            if(j)dp[i][j]=(dp[i][j]+(i-j)*dp[i-1][j-1])%mod;
        }
    }

    int t;
    cin>>t;

    while(t--){
        int n, a, b;
        cin>>n>>a>>b;
        if(a+b>n)cout<<0<<"\n";
        else {
            long long ans=0;
            for(int s=0;s<=a+b;s++){
                if((a+b-s)&1)ans=(ans-nenk(a+b, s)*dp[s][b])%mod;
                else ans=(ans+nenk(a+b, s)*dp[s][b])%mod;
            }
            if(ans<0)ans+=mod;
            cout<<ans*nenk(n, n-a-b)%mod*f[n]%mod<<"\n";
        }
    }

    return t+1;
}