#include<bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s;
    cin>>s; int n=s.size();
    vector<long long> dp(n+1, 0), last(30, -1); dp[0]=1;

    for(int i=1,c; i<=n; i++){
        c=s[i-1]-'a';
        dp[i]=2*dp[i-1];
        if(last[c]!=-1)dp[i]-=dp[last[c]-1];
        dp[i]=(dp[i]+md)%md;
        last[c]=i;
    }

    cout<<(dp[n]+md-1)%md;

    return 0;
}