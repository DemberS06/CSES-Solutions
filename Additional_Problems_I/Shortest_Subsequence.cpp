#include <bits/stdc++.h>

using namespace std;


int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    string s, d="ACGT";
    cin>>s; int n=s.size();

    vector<int> a(n), p(n), c(n, 0), dp(4, 0), f(4, -1);

    reverse(s.begin(), s.end());
    for(int i=0; i<n; i++){
        for(int h=0; h<4; h++){
            if(s[i]==d[h])a[i]=h;
        }
    }

    for(int i=0, x=0; i<n; i++, x=dp[0]){
        for(int j=1; j<4; j++)if(dp[j]<x)x=dp[j], c[i]=j;
        p[i]=f[c[i]];
        
        dp[a[i]]=dp[c[i]]+1;
        f[a[i]]=i;
    }

    for(int i=n-1; i>=0; i=p[i])cout<<d[c[i]];
    sort(dp.begin(), dp.end());
    if(dp[0]==dp.back())cout<<"A";

    return 0;
}

