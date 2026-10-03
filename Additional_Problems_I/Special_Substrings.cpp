#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s;
    cin>>s; int n=s.size(), mn=0;

    set<char> f;
    map<char, int> cmp;

    for(auto& u:s)f.insert(u);
    for(auto& u:f)cmp[u]=mn++;
    for(auto& u:s)u=cmp[u];

    long long ans=0;
    vector<int> v(mn, 0);
    map<vector<int>, long long> dp; dp[v]++;

    for(auto& u:s){
        v[u]++; mn=n;
        for(auto& x:v)mn=min(mn, x);
        for(auto& x:v)x-=mn;
        ans+=dp[v];
        dp[v]++;
    }

    cout<<ans;

    return 0;
}