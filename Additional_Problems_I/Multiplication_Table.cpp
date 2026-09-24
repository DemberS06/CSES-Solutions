#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    long long n;
    cin>>n;
    
    long long ans=0, l=1, r=n*n;

    function<bool(long long)> simulation = [&](long long x){
        long long sum=0;
        for(long long i=1; i<=n; i++)sum+=min(n,(x-1)/i);
       
        return sum<(n*n+1)/2;
    };

    while(l<=r){
        long long md=(l+r)/2;
        if(simulation(md))ans=md, l=md+1;
        else r=md-1;
    }

    cout<<ans;


    return 0;
}