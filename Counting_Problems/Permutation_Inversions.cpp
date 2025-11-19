// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

const long long mod=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();

    int n, k;

    cin>>n>>k;

    vector<vector<long long>> dp(n+1, vector<long long>(k+1, 0));
    dp[0][0]=1;

    for(int i=1; i<=n; i++){
        for(int j=0; j<=k && j<=i*(i-1)/2; j++){
            dp[i][j]=dp[i-1][j];
            if(j)dp[i][j]=(dp[i][j]+dp[i][j-1])%mod;
            if(j>=i)dp[i][j]=(dp[i][j]-dp[i-1][j-i]+mod)%mod;
        }
    }

    cout<<dp[n][k];

    return 0;
}