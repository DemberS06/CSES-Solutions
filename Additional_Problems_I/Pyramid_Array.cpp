#include <bits/stdc++.h>

using namespace std;

struct Fenwick{
    int n;
    vector<long long> fwk;
    Fenwick(int _n):n(_n), fwk(n, 0){}
 
    void update(int p, long long delta){
        for(; p<n; p+=-p&p)fwk[p]+=delta;
    }
 
    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p)res+=fwk[p];
        return res;
    }
};

int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    long long n, cnt=0;
    cin>>n;
    vector<vector<long long>> dp(n+1, vector<long long> (2, 0));
    vector<long long> v(n), p(n+1, 0);
    map<int, int> cmp;
    set<int> f;
    Fenwick a(n+1);

    for(auto& u:v){
        cin>>u;
        f.insert(u);
    }

    for(auto& u:f)cmp[u]=++cnt;
    for(int i=0; i<n; i++){
        v[i]=cmp[v[i]];
        p[v[i]]=i+1;
    }
    a.update(p[n], 1);

    for(int i=n-1, l, r; i>0; i--){
        l=a.query(p[i]), r=n-i-l;
        a.update(p[i], 1);
        dp[i][1]=dp[i][0]=min(dp[i+1][0], dp[i+1][1]);
        dp[i][1]+=r; dp[i][0]+=l;
    }

    cout<<min(dp[1][0], dp[1][1]);

    return 0;
}