#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k; long long sum=0;
    cin>>n>>k;
    vector<long long> v(n);
    for(auto& u:v){
        cin>>u;
        if(u<0)sum+=u, u=-u;
    }
    sort(v.begin(), v.end());

    vector<long long> p, val(n, 1e18);
    multiset<pair<long long, int>> f;
    f.insert({sum, -1});

    while(p.size()!=k){
        auto [x, i]=*f.begin();
        f.erase(f.begin()); 
        
        p.push_back(x);
        if(i!=n-1)f.insert({x+v[i+1], i+1});
        if(i!=-1 && i!=n-1)f.insert({x+v[i+1]-v[i], i+1});
    }

    for(auto& u:p)cout<<u<<' ';

    return 0;
}