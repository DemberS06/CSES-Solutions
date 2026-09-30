#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, x, ans=0;
    cin>>n>>x;

    vector<int> dp(x+1, 0), p(n), w(n), a(n);
    vector<pair<int, int>> v; v.reserve(20*n);

    for(auto& u:p)cin>>u;
    for(auto& u:w)cin>>u;
    for(auto& u:a)cin>>u;

    for(int i=0; i<n; i++){
        while(a[i]){
            while(!(a[i]&1))v.push_back({p[i], w[i]}), a[i]--;
            v.push_back({p[i], w[i]});
            a[i]/=2; p[i]*=2, w[i]*=2;
        }
    }

    for(auto& [P, W]:v){
        for(int i=x; i>=P; i--)dp[i]=max(dp[i], dp[i-P]+W);
    }
    
    for(int i=0; i<=x; i++)ans=max(ans, dp[i]);
    cout<<ans;

    return 0;
}
