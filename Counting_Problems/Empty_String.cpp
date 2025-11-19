// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

const long long mod=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();
    function<long long(long long, long long)> expbin = [&](long long x, long long y){
        long long ans=1;

        while(y){
            if(y&1)ans=ans*x%mod;
            x=x*x%mod;
            y/=2;
        }

        return ans;
    };
    
    int n;
    string s;
    cin>>s;
    n=s.size();

    vector<long long> f(n+2, 1), r(n+2, 1);
    for(int i=2; i<=n+1; i++)f[i]=f[i-1]*i%mod, r[i]=expbin(f[i], mod-2);
    function<long long(long long, long long)> nenk = [&](long long x, long long y){

        return f[x]*r[y]%mod*r[x-y]%mod;
    };

    vector<vector<long long>> dp(n+5, vector<long long> (n+5, 1));

    for(int t=1; t<=n; t++){
        for(int i=0, j=t-1; j<n; i++, j++){
            dp[i][j]=0;
            if(t&1)continue;
            for(int k=i+1; k<=j; k++){
                if(s[i]==s[k]){
                    dp[i][j]=(dp[i][j]+dp[i+1][k-1]*dp[k+1][j]%mod*nenk(t/2, (j-k)/2))%mod;
                }
            }
        }
    }

    cout<<dp[0][n-1];

    return 0;
}