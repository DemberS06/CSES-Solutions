#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<long long> a(n+1, 0), p(n+1, n);
    for(int i=1; i<=n; i++){
        cin>>a[i];
        a[i]+=a[i-1];
    }

    for(int i=1; i<=n; i++){
        p[i]=1;
        for(int j=i-1; j>0; j-=p[j]){
            if((a[j]-a[j-p[j]])*p[i]<(a[i]-a[i-p[i]])*p[j])break;
            p[i]+=p[j];
        }
    }

    for(int i=1; i<=n; i++)cout<<p[i]<<' ';
    
    return 0;
}