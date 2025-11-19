//hola soy Dember :D
#include <bits/stdc++.h>
 
using namespace std;

const long long mod = 1e9+7;
 
int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0); 
	function<long long(long long, long long)> expbin = [&](long long x, long long y){
        long long res=1;
        
        while(y){
            if(y&1)res=res*x%mod;
            x=x*x%mod;
            y>>=1;
        }

        return res;
    };

	int n;
	cin>>n;
	vector<long long> fac(2*n+1, 1), rev(2*n+1, 1), ans(n, 0), dp(n+1, 0);
	
    function<long long(int, int)> nenk = [&](int n, int k) {
		return fac[n]*rev[n-k]%mod*rev[k]%mod;
	};
	
    fac[0]=rev[0]=dp[0]=1;

	for(int i=2; i<=2*n; i++)fac[i]=fac[i-1]*i%mod, rev[i]=expbin(fac[i], mod-2);
	
    for(int i=0; i<n; i++){
		for(int j=i; j>=0; j--){
			dp[j+1]=(dp[j+1]+dp[j])%mod;
			dp[j]=dp[j]*i%mod;
		}
        
		for(int j=0; j<=i; j++)ans[j]=(ans[j] + nenk(n-1, i)*expbin(n, n-i-1)%mod*dp[j+1]%mod)%mod;
	}
	for(auto& u:ans)cout<<u<<'\n';
 
    return 0;
}