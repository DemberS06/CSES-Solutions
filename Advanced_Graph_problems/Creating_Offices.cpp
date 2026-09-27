#include <bits/stdc++.h>

using namespace std;

const long long N=2e5+5;

vector<vector<int>> adj;

int depth[N], ans[N];

void dfs(int x, int y){
    for(auto& u:adj[x]){
        if(u==y)continue;
        depth[u]=depth[x]+1;
        dfs(u, x);
    }
}

struct CentroidTree{
    int n, root;
    vector<int> cpar, lvl;
    vector<vector<int>> dist;
    CentroidTree(vector<vector<int>> &adj): n(adj.size()), root(-1), cpar(n, -1), lvl(n, 0){
        vector<int> sz(n, 0), dead(n, 0);
        int niveles=1;
        while((1<<niveles)<=n)niveles++;
        dist.assign(niveles+1, vector<int> (n, 0));
        function<int(int, int)> getsz = [&](int x, int p){
            sz[x]=1;
            for(auto &u:adj[x]){
                if(u==p || dead[u])continue;
                sz[x]+=getsz(u, x);
            }
            return sz[x];
        };
        function<int(int, int, int)> cen = [&](int x, int p, int tot){
            for(auto &u:adj[x]){
                if(u==p || dead[u])continue;
                if(sz[u]>tot/2)return cen(u, x, tot);
            }
            return x;
        };
        function<void(int, int, int, int)> fill_dist = [&](int x, int p, int l, int d){
            dist[l][x]=d;
            for(auto &u:adj[x]){
                if(u==p || dead[u])continue;
                fill_dist(u, x, l, d+1);
            }
        };
        function<void(int, int, int)> solve = [&](int r, int pc, int l){
            int c=cen(r, r, getsz(r, r));
            cpar[c]=pc;
            lvl[c]=l;
            if(pc==-1)root=c;
            fill_dist(c, c, l, 0);
            dead[c]=1;
            for(auto &u:adj[c]){
                if(!dead[u])solve(u, c, l+1);
            }
        };
        solve(1, -1, 0);
    }

    void update(int x){
        for(int u=x; u!=-1; u=cpar[u]){
            ans[u]=min(ans[u], dist[lvl[u]][x]);
        }
    }
    long long query(int x){
        int res=1e9;

        for(int u=x; u!=-1; u=cpar[u])res=min(res, ans[u]+dist[lvl[u]][x]);
        return res;
    }
};


int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, d;
    cin>>n>>d;

    vector<int> p(n+1, 0), res; res.reserve(n); 
    adj.resize(n+1);
    
    for(int i=1, x, y; i<n; i++){
        cin>>x>>y; ans[i]=1e9;
        p[i]=i;
        adj[x].push_back(y);
        adj[y].push_back(x);
    } p[n]=n; ans[n]=1e9;
    
    dfs(1, 1);
    CentroidTree C(adj);

    sort(p.begin(), p.end(), [&](int& x, int& y){
        if(depth[x]==depth[y])return x>y;
        return depth[x]>depth[y];
    });
    p.pop_back();

    for(auto& u:p){
        int x=C.query(u);
        if(x<d)continue;
        res.push_back(u);
        C.update(u);
    }

    cout<<res.size()<<"\n";
    for(auto& u:res)cout<<u<<' ';
    
    return 0;
}