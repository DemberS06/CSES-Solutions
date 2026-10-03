#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, ans=0;
    cin>>n;

    map<int, vector<long long>> mp;

    for(int i=1, x; i<=n; i++){
        cin>>x;
        mp[x].push_back(i);
    }

    for(auto& [_, v]:mp){
        long long x=0;
        for(auto& u:v){
            ans+=(u-x)*(n-u+1);
            x=u;
        }
    }

    cout<<ans;

    return 0;
}