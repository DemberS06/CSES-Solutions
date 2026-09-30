#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7, N=5e3+1;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, x;
    cin>>n>>x;
    vector<int> a(n);
    for(auto& u:a)cin>>u;
    sort(a.begin(), a.end());

    vector<vector<long long>> gp(n+1, vector<long long> (2*N+1, 0)); gp[0][N]=1;

    for(auto& w:a){
        vector<vector<long long>> dp(n+1, vector<long long> (2*N+1, 0));
        for(int i=0; i<=n; i++){
            for(int j=0; j<=2*N; j++){
                if(i>0 && j<=2*N-w)dp[i][j]+=gp[i-1][j+w];
                if(i<n && j>=w)dp[i][j]+=gp[i+1][j-w]*(i+1);
                dp[i][j]=(dp[i][j]+gp[i][j]*(i+1))%md;
            }
        }
        
        swap(dp, gp);
    }

    long long ans=0;

    for(int i=0; i<=x; i++)ans=(ans+gp[0][N+i])%md;
    cout<<ans;

    return 0;
}