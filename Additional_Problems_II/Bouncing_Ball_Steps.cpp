#include <bits/stdc++.h>

using namespace std;

void solve(){
    long long n, m, k, x, y, ans=0;
    cin>>n>>m>>k; n--, m--;

    function<long long(long long)> get_p = [&](long long p){
        long long f=k/p, res;
        if(f&1)res=p-k%p;
        else res=k%p;
        ans+=f;

        return res+1;
    };

    x=get_p(n);
    y=get_p(m);
    ans-=k/(n*m/__gcd(n, m));

    cout<<x<<' '<<y<<' '<<ans<<"\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t; cin>>t;
    while(t--)solve();
    return t+1;
}