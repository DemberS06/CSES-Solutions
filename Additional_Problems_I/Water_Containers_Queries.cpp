#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t, a, b, x; cin>>t;
    while(t--){
        cin>>a>>b>>x;
        if(x>a || x%__gcd(a, b)){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
    }
    return t+1;
}