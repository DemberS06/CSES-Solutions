#include <bits/stdc++.h>

using namespace std;

const long long inf=1e15;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;

    vector<vector<pair<int, long long>>> adj(n+1), jda(n+1);
    for(int i=0, x,y,w; i<m; i++){
        cin>>x>>y>>w;
        adj[x].push_back({y, w});
        jda[y].push_back({x, w});
    }

    function<void(int, vector<long long>&)> djk = [&](int s, vector<long long>& dis){
        vector<int> vis(n+1, 0);
        set<pair<long long, int>> f;
        f.insert({0, s});

        while(!f.empty()){
            auto [p, x]=*f.begin();
            f.erase(f.begin());
            if(vis[x])continue;
            vis[x]=1, dis[x]=p;
            for(auto& [u,w]:adj[x]){
                if(vis[u])continue;
                f.insert({p+w, u});
            }
        }
    };

    vector<long long> a(n+1, inf), b(n+1, inf);
    djk(1, a); swap(adj, jda);
    djk(n, b); swap(adj, jda);

    vector<vector<int>> ady(n+1);
    vector<int> pre(n+1, 0), high=pre, vis=pre, p, ans;
    vector<pair<int, int>> v;
    
    function<void(int)> dfs = [&](int x){
        vis[x]=1;
        if(x==n)return;
        for(auto& u:ady[x]){
            if(vis[u])continue;
            if(!pre[n])pre[u]=pre[x]+1, p.push_back(u);
            dfs(u);
            if(pre[n])break;
            pre[u]=0;
            p.pop_back();
        }
    };
    
    function<void(int)> get_mx = [&](int x){
        vis[x]=1;
        if(pre[x])high[x]=min(pre[x]+1, pre[n]);
        for(auto& u:ady[x]){
            if(pre[u]){
                high[x]=max(high[x], pre[u]);
                continue;
            }
            if(!vis[u])get_mx(u);
            high[x]=max(high[x], high[u]);
        }
    };

    //cout<<b[1]<<' '<<a[n]<<"\n";
    
    for(int i=1; i<=n; i++){
        if(a[i]+b[i]!=a[n])continue;
        //cout<<i<<": ";
        for(auto& [u, w]:adj[i]){
            if(a[i]+b[u]+w!=a[n])continue;
            ady[i].push_back(u);
            //cout<<u<<' ';
        }//cout<<"\n";
    }
    
    pre[1]=1; p.push_back(1); dfs(1);
    sort(p.begin(), p.end(), [&](int& x, int& y){
        return pre[x]<pre[y];
    });
    fill(vis.begin(), vis.end(), 0);

    for(auto& i:p){
        get_mx(i);
        v.push_back({pre[i]+(i!=n), 1});
        v.push_back({high[i], -1});
        //cout<<i<<' '<<pre[i]<<' '<<high[i]<<"\n";
    }

    sort(v.begin(), v.end());
    int j=0, x=0;
    for(auto& i:p){
        while(j<v.size() && v[j].first<=pre[i])x+=v[j].second, j++;
        if(!x)ans.push_back(i);
    }

    sort(ans.begin(), ans.end());
    cout<<ans.size()<<"\n";
    for(auto& u:ans)cout<<u<<' ';

    return 0;
}