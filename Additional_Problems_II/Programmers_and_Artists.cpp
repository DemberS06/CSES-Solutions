#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, a, b;
    cin>>a>>b>>n;
    vector<pair<int, int>> v(n);

    for(auto& [x, y]:v)cin>>x>>y;
    sort(v.begin(), v.end(), [&](auto& x, auto& y){
        return x.first-x.second>y.first-y.second;
    });

    multiset<long long> f;
    vector<long long> p(n), q(n);
    long long sum=0;

    for(int i=0; i<n; i++){
        f.insert(v[i].first);
        sum+=v[i].first;
        if(f.size()>a){
            sum-=*f.begin();
            f.erase(f.begin());
        }
        p[i]=sum;
    }
    sum=0; f.clear();
    for(int i=n-1; i>=0; i--){
        f.insert(v[i].second);
        sum+=v[i].second;
        if(f.size()>b){
            sum-=*f.begin();
            f.erase(f.begin());
        }
        q[i]=sum;
    }
    
    sum=max(p.back(), q[0]);
    for(int i=1; i<n; i++)sum=max(sum, p[i-1]+q[i]);
    cout<<sum;

    return 0;
}