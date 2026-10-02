#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m, k; 
    string s, r, t;
    cin>>n>>s; m=s.size();

    function<int()> KMP = [&](){
        t=s+"  "+r; k=t.size();
        vector<int> kmp(k, 0);
        for(int i=1, j=0; i<k; i++){
            while(j>0 && t[i]!=t[j])j=kmp[j-1];
            if(t[i]==t[j])j++;
            kmp[i]=j;
        }
        return kmp.back();
    };

    vector<vector<int>> adj(m, vector<int> (26, 0));
    for(int i=0; i<m; i++){
        for(char c='A'; c<='Z'; c++){
            r+=c;
            adj[i][c-'A']=KMP();
            r.pop_back();
        }
        r+=s[i];
    }

    vector<vector<long long>> dp(n+1, vector<long long> (m+1, 0)); dp[0][0]=1;

    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            for(int h=0; h<26; h++){
                dp[i][adj[j][h]]=(dp[i][adj[j][h]]+dp[i-1][j])%md;
            }
        }
        dp[i][m]=(dp[i][m]+dp[i-1][m]*26)%md;
    }

    cout<<dp[n][m];

    return 0;
}