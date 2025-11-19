// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();

    int n, k;

    cin>>n>>k;

    vector<vector<int>> dp(n, vector<int>(n, 1));
    vector<vector<char>> a(n, vector<char>(n));

    for(auto& v:a)for(auto& u:v)cin>>u;
    vector<long long> ans(k, 0);

    for(int i=1, x; i<n; i++){
        for(int j=1; j<n; j++){
            dp[i][j]=1e8; x=3;
            if(a[i-1][j]==a[i][j])dp[i][j]=min(dp[i][j], dp[i-1][j]+1), x--;
            if(a[i][j-1]==a[i][j])dp[i][j]=min(dp[i][j], dp[i][j-1]+1), x--;
            if(a[i-1][j-1]==a[i][j])dp[i][j]=min(dp[i][j], dp[i-1][j-1]+1), x--;
            if(x)dp[i][j]=1;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ans[a[i][j]-'A']+=dp[i][j];
        }
    }

    for(auto& u:ans)cout<<u<<"\n";

    return 0;
}