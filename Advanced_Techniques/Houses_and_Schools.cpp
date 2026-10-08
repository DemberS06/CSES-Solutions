#include <bits/stdc++.h>

using namespace std;

const long long inf=1e18;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k;
    cin>>n>>k;
    vector<long long> dp(n+1, inf), gp(n+1, inf); dp[0]=gp[0]=0;
    vector<long long> a(n+1, 0), b(n+1, 0);
    vector<vector<long long>> dis(n+1, vector<long long> (n+1));
    
    for(int i=1; i<=n; i++){
        cin>>a[i];
        b[i]=a[i]*i;
        a[i]+=a[i-1];
        b[i]+=b[i-1];
    }

    for(int l=1; l<=n; l++){
        for(int r=l, p=l; r<=n; r++){
            while(a[r]-a[l-1]>2*(a[p]-a[l-1]))p++;
            dis[l][r]=(b[r]-b[p])-(a[r]-a[p])*p;
            dis[l][r]+=(a[p-1]-a[l-1])*p-(b[p-1]-b[l-1]);
        }
    }

    function<void(int, int, int, int)> solve = [&](int l, int r, int p, int q){
        if(l>r)return;
        int mid=(l+r)/2, best=p, top=min(mid, q);
        long long x; dp[mid]=inf;
        for(int i=p; i<=top; i++){
            x=gp[i-1]+dis[i][mid];
            if(x>dp[mid])continue;
            best=i;
            dp[mid]=x;
        }
        solve(l, mid-1, p, best);
        solve(mid+1, r, best, q);
        return;
    };

    for(int i=0; i<k; i++){
        swap(gp, dp);
        solve(1,n,1,n);
    }
    cout<<dp.back();
    return 0;
}