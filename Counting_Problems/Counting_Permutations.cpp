// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

const long long mod=1e9+7; 

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n;
    cin>>n;
    
    vector<vector<vector<long long>>> dp(n+1, vector<vector<long long>> (n+1, vector<long long> (2, 0))); 
    dp[1][0][0]=1;

    for(int i=2; i<=n; i++){
        for(int j=0; j<i; j++){
            if(j)dp[i][j][1]=(dp[i-1][j-1][1]+dp[i-1][j-1][0]*2+dp[i-1][j][1])%mod;
            dp[i][j][0]=(dp[i-1][j][1]*(i-j-1)+dp[i-1][j][0]*(i-j-2)+dp[i-1][j+1][0]*(j+1)+dp[i-1][j+1][1]*j)%mod;
        }
    }

    cout<<(dp[n][0][0]+dp[n][0][1])%mod;

    return 0;
}