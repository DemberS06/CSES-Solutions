#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<long long> f(n+1, 0), dp(n+1, 0), pot(n+1, 1);

    for(int i=1, x; i<=n; i++){
        cin>>x; f[x]++;
        pot[i]=2*pot[i-1]%md;
    }

    for(int i=n; i>0; i--){
        long long sum=f[i];
        for(int j=2*i; j<=n; j+=i){
            dp[i]=(md+dp[i]-dp[j])%md;
            sum+=f[j];
        }
        dp[i]=(md+dp[i]+pot[sum]-1)%md;
    }

    for(int i=1; i<=n; i++)cout<<dp[i]<<' ';

    return 0;
}