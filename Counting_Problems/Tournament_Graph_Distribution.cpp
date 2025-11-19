// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9+7;

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
    
    long long n;
    cin>>n; 

    vector<long long> fac(n+1, 1), rev(n+1, 1), T(n+1, 1), B(n+1, 0), ans(n, 0);
    for(long long i=1; i<=n; i++){
        fac[i]=fac[i-1]*i%mod; 
        rev[i]=expbin(fac[i], mod-2); 
        T[i]=expbin(2, i*(i-1)/2)*rev[i]%mod;
        B[i]=T[i];
        for(int k=1; k<i; k++)B[i]=(B[i] + T[k]*(mod-B[i-k]))%mod;
    }
    
    vector<vector<long long>> dp(n+1, vector<long long> (n+1, 0));
    dp[0][0]=1; 

    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            if(B[i]==0)continue;
            for(int m=i; m<=n; m++)dp[k][m]=(dp[k][m] + dp[k-1][m-i]*B[i])%mod;
        }
        ans[k-1]=dp[k][n]*fac[n]%mod;
    }

    for(auto& u:ans)cout<<u<<'\n';

    return 0;
}
