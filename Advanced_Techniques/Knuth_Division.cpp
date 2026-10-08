#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<vector<long long>> dp(n+1, vector<long long> (n+1)), op=dp;
    vector<long long> p(n+1, 0);

    for(int i=1; i<=n; i++){
        cin>>p[i];
        p[i]+=p[i-1];
        dp[i][i]=0;
        op[i][i]=i;
    }

    for(int l=n; l>0; l--){
        for(int r=l+1; r<=n; r++){
            dp[l][r]=inf;
            for(int i=op[l][r-1]; i<=op[l+1][r] && i<r; i++){
                if(dp[l][r]<dp[l][i]+dp[i+1][r])continue;
                op[l][r]=i;
                dp[l][r]=dp[l][i]+dp[i+1][r];
            }
            dp[l][r]+=p[r]-p[l-1];
        }
    }

    cout<<dp[1][n];

    return 0;
}