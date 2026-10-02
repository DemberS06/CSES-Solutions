#include <bits/stdc++.h>

using namespace std;


int main(){
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;

    vector<vector<int>> adj(n+1);
    vector<int> pre(n+1, 0), high=pre, vis=pre;

    function<void(int)> dfs = [&](int x){
        vis[x]=1;
        if(x==n)return;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            if(!pre[n])pre[u]=pre[x]+1;
            dfs(u);
            if(!pre[n])pre[u]=0;
            else break;
        }
    };

    function<void(int x)> get_mx = [&](int x){
        vis[x]=1;
        if(pre[x])high[x]=min(pre[x]+1, pre[n]);
        for(auto& u:adj[x]){
            if(pre[u]){
                high[x]=max(high[x], pre[u]);
                continue;
            }
            if(vis[u]){
                high[x]=max(high[x], high[u]);
                continue;
            }
            get_mx(u);
            high[x]=max(high[x], high[u]);
        }
    };

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
    }

    pre[1]=1;
    dfs(1);

    vector<pair<int, int>> v;
    vector<int> p;

    for(int i=1; i<=n; i++){
        if(!pre[i])continue;
        p.push_back(i);
    }

    sort(p.begin(), p.end(), [&](int& x, int& y){
        return pre[x]<pre[y];
    });

    fill(vis.begin(), vis.end(), 0);
    for(auto& u:p){
        get_mx(u);
        v.push_back({pre[u]+(u!=n), 1});
        v.push_back({high[u], -1});
        //cout<<u<<' '<<pre[u]<<' '<<high[u]<<"\n";
    } //cout<<vis[2]<<' '<<high[2]<<"\n";

    sort(v.begin(), v.end());

    vector<int> ans; ans.reserve(n);
    int j=0, x=0; 
    for(auto& i:p){
        if(!pre[i])continue;
        while(j<v.size() && v[j].first<=pre[i])x+=v[j].second, j++;
        if(!x)ans.push_back(i);
    }

    sort(ans.begin(), ans.end());

    cout<<ans.size()<<"\n";
    for(auto& u:ans)cout<<u<<' ';
    
    return 0;
}