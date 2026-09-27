#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    long long x, n, ans=0;
    cin>>x>>n;

    multiset<long long> f;
    while(n--){
        cin>>x;
        f.insert(x);
    }

    while(f.size()>1){
        auto a=*f.begin();f.erase(f.begin());
        auto b=*f.begin();f.erase(f.begin());
        ans+=a+b;
        f.insert(a+b);
    }

    cout<<ans;

    return 0;
}