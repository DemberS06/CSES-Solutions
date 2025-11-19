// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

const long long mod=1e9+7;

int main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, k, ans=0;
    cin>>n>>k;

    if(k>n*n){
        cout<<0;
        return 0;
    }

    vector<int> v[2]; 
    for(int i=2; i<=2*n; i++){
        int x=min(i-1ll, 2*n+1-i);
        if(x<=0)continue;
        v[x&1].push_back(x);
    }

    auto computeWays = [&](vector<int>& v){
        sort(v.begin(), v.end());
        long long m=v.size();
        int cap=min(k, m);
        vector<long long> dp(cap+1, 0), ndp(cap+1, 0);
        dp[0]=1;
        for(int i=0; i<m; i++){
            fill(ndp.begin(), ndp.end(), 0);

            for(int j=0; j<=cap; j++){
                if(dp[j]==0)continue;
                ndp[j]=(ndp[j]+dp[j])%mod;
                if(j<cap && v[i]>j)ndp[j+1]=(ndp[j+1]+dp[j]*(v[i]-j))%mod;
            }
            dp.swap(ndp);
        }
        return dp;
    };

    vector<long long> B = computeWays(v[0]);
    vector<long long> W = computeWays(v[1]);

    for(int i=0, j=k; i<B.size(); i++, j--){
        if(j<0 || j>=W.size())continue;
        ans=(ans+B[i]*W[j])%mod;
    }

    cout<<ans;
    
    return 0;
}
