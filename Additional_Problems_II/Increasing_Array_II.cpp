#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, ans=0;
    cin>>n;

    multiset<int> f;

    for(int i=0, x; i<n; i++){
        cin>>x;
        ans-=x;
        f.insert(-x); f.insert(-x);
        ans-=*f.begin();
        f.erase(f.begin());
    }

    cout<<ans;

    return 0;
}