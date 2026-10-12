#include <bits/stdc++.h>

using namespace std;

const long long mod=1e9+7, N=500*500+1;
long long dp[N][2];

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, a, cnt=0; cin>>n>>a;     
    vector<int> p, q;

    for(int i=0, x; i<n; i++){
        cin>>x;
        x-=a;
        if(x==0)cnt++;
        if(x<0)p.push_back(-x);
        if(x>0)q.push_back(x);
    }

    long long z=1, ans=0; while(cnt--)z=2*z%mod;
    dp[0][0]=dp[0][1]=1;

    for(auto& u:p){
        for(int i=N-1; i>=u; i--)dp[i][0]=(dp[i][0]+dp[i-u][0])%mod;
    }
    for(auto& u:q){
        for(int i=N-1; i>=u; i--)dp[i][1]=(dp[i][1]+dp[i-u][1])%mod;
    }

    for(int i=1; i<N; i++){
        ans=(ans+(dp[i][0]*dp[i][1]%mod)*z)%mod;
    }

    cout<<(ans+z-1)%mod;

    return 0;
}