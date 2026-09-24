#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; long long x, ans=0;
    cin>>n>>x;

    vector<long long> v(n), a, b; 
    for(auto& u:v)cin>>u;

    n/=2; a.reserve((1<<n));
    for(int i=0; i<(1<<n); i++){
        a.push_back(0);
        for(int h=0; h<n; h++){
            if((i>>h)&1)a.back()+=v[h];
        }
    }
    reverse(v.begin(), v.end());
    n=v.size()-n; b.reserve(1<<n);
    for(int i=0; i<(1<<n); i++){
        b.push_back(0);
        for(int h=0; h<n; h++){
            if((i>>h)&1)b.back()+=v[h];
        }
    }

    sort(a.begin(), a.end()); sort(b.rbegin(), b.rend());

    for(int i=0, l=0, r=0; i<b.size(); i++){
        while(r<a.size() && b[i]+a[r]<=x)r++;
        while(l<r && b[i]+a[l]<x)l++;
        ans+=r-l;
    }

    cout<<ans;

    return 0;
}