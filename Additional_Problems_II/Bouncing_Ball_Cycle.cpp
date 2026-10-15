#include <bits/stdc++.h>

using namespace std;

void solve(){
    long long a, b, g;
    cin>>a>>b; a--, b--; g=__gcd(a, b);
    long long R1=(a/g+1)/2;
    long long R0=R1+(a/g%2==0);
    long long R3=a/g/2;
    long long Rg=R3+(a/g%2==1);
    long long C1=(b/g+1)/2;
    long long C0=C1+(b/g%2==0);
    long long C3=b/g/2;
    long long Cg=C3+(b/g%2==1);

    cout<<2*a*b/g<<' '<<R0*C0+Rg*Cg+(g-1)*(R1+R3)*(C1+C3)<<"\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t; cin>>t;
    while(t--)solve();
    return t+1;
}