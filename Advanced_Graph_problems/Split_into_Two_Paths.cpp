#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m; cin>>n>>m;
    vector<vector<int>> adj(n+1), jda(n+1);
    vector<int> in(n+1, 0), p(1, 0), dp(n+1, 0), val(n+1, 0), v(n+1, 0), r(n+1), pat(n+1, 0);
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        jda[y].push_back(x);
        in[y]++;
    }

    queue<int> q;
    for(int i=1; i<=n; i++){
        adj[0].push_back(i);
        if(!in[i])q.push(i);
    }
    while(!q.empty()){
        auto x=q.front(); q.pop();
        val[x]=p.size();
        p.push_back(x);
        for(auto& u:adj[x]){
            in[u]--;
            if(!in[u])q.push(u);
        }
        jda[x].push_back(0);
    }
    
    for(int i=n; i>0; i--){
        r[i]=i;
        for(auto& u:adj[p[i]]){
            if(val[u]==i+1)r[i]=r[i+1];
        }
    }
    v[0]=1; dp[0]=r[1];

    for(int i=2; i<=n; i++){
        for(auto& u:jda[p[i]]){
            if(!v[val[u]] || dp[val[u]]<i-1 || val[u]==i-1)continue;
            v[i-1]=1;
            dp[i-1]=r[i];
            pat[i-1]=val[u];
        }
    }

    int x=-1;
    for(int i=0; i<=n; i++){
        if(dp[i]>=n)x=i;
    }
    if(x==-1){
        cout<<"NO\n";
        return 0;
    }
    
    vector<int> a, b;
    function<void(int, int)> solve = [&](int x, int y){
        if(!y)return;
        for(int i=y; i>x; i--)a.push_back(p[i]);
        swap(a, b);
        solve(pat[x], x);
    };

    solve(x, n); if(a.size()>b.size())swap(a,b);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    cout<<"YES\n";
    cout<<a.size()<<' '; for(auto& u:a)cout<<u<<' ';cout<<"\n";
    cout<<b.size()<<' '; for(auto& u:b)cout<<u<<' ';cout<<"\n";

    return 0;
}