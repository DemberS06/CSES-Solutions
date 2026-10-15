#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k, m; cin>>n>>m>>k;
    vector<long long> a(n), ans;
    for(auto& u:a)cin>>u;
    sort(a.begin(), a.end());

    multiset<tuple<long long, int, int, int>> f;

    for(long long sum=0, i=0; i<m; i++){
        sum+=a[i];
        if(i==m-1)f.insert({sum, i, i, n});
    }

    while(ans.size()<k){
        auto [sum, i, p, r]=*f.begin();
        f.erase(f.begin());
        ans.push_back(sum);
        if(p+1<r)f.insert({sum+a[p+1]-a[p], i, p+1, r});
        if(i && p>i)f.insert({sum+a[i]-a[i-1], i-1, i, p});
    }

    for(auto& u:ans)cout<<u<<' ';
    return 0;
}