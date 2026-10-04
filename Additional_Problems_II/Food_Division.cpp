#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, x, y=0; cin>>n;

    vector<long long> v(n);
    for(auto& u:v)cin>>u;
    for(auto& u:v){
        cin>>x;
        u-=x;
        u+=y;
        y=u;
    }

    sort(v.begin(),v.end());
    x=v[n/2]; y=0;
    for(auto& u:v)y+=abs(u-x);
    cout<<y;

    return 0;
}