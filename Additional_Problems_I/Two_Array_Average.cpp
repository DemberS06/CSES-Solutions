#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, p=1, q=1, k=120, x, y; cin>>n;
    vector<long long> a(n+1, 0), b(n+1, 0);
    for(int i=1; i<=n; a[i]+=a[i-1], i++)cin>>a[i]; 
    for(int i=1; i<=n; b[i]+=b[i-1], i++)cin>>b[i]; 
    for(long double l=0, r=1e10, mt; k--;){
        mt=(l+r)/2; x=1,y=1;
        for(long long i=1; i<=n; i++){
            if(-mt*i+a[i]>=-mt*x+a[x])x=i;
            if(-mt*i+b[i]>=-mt*y+b[y])y=i;
        }
        if(-mt*x+a[x]-mt*y+b[y]<0){
            r=mt;
            continue;
        }
        p=x, q=y;
        l=mt;
    }    

    cout<<p<<' '<<q;
    return 0;
}