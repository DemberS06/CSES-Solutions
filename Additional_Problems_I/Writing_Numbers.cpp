#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    long long n, l=1, r=6e17, ans;
    cin>>n;

    function<long long(long long)> val = [&](long long x){
        long long res=0, factor=1, curr, nxt;

        while(factor<=x){
            curr=x/(10*factor);
            nxt=x%(10*factor);        
            res+=factor*curr;
            if(nxt>=factor)res+=min(factor, nxt-factor+1);
            factor*=10;
        }

        return res;
    };

    while(l<=r){
        long long mt=(l+r)/2;
        if(val(mt)<=n)ans=mt, l=mt+1;
        else r=mt-1;
    }

    cout<<ans;
    
    return 0;
}