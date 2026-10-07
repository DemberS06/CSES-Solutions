#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;

int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, k;
    cin>>n>>k;

    vector<long long> c(n+1, 0), a(n+1, inf), dp(n+1, inf); dp[0]=a[0]=0;
    
    function<void(int, int, int, int)> Monge = [&](int l, int r, int p, int q){
        if(l>r)return;
        int mid=(l+r)/2, best=p, top=min(mid, q);
        long long val; dp[mid]=inf;
        for(int i=p; i<=top; i++){
            val=a[i-1]+(c[mid]-c[i-1])*(c[mid]-c[i-1]);
            if(val>dp[mid])continue;
            best=i;
            dp[mid]=val;
        }

        Monge(l, mid-1, p, best);
        Monge(mid+1, r, best, q);
    };

    for(int i=1; i<=n; i++){
        cin>>c[i];
        c[i]+=c[i-1];
    }

    for(int i=0; i<k; i++){
        swap(a, dp);
        Monge(1,n,1,n);
    }

    cout<<dp.back();

    return 0;
}