// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    vector<long long> prev(1, 1); 

    for(int i=2; i<=n; i++){
        vector<long long> cur(i, 0);
        for(int m=0; m<=i-1; m++){
            if(m<i-1)cur[m]=prev[m]*(m+1)%mod;
            if(m>0)cur[m]=(cur[m] + prev[m-1]*(i-m))%mod;
        }
        prev.swap(cur);
    }

    for(auto& u:prev)cout<<u<<'\n';

    return 0;
}
