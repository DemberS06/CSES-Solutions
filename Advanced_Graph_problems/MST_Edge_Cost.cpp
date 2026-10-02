#include<bits/stdc++.h>

using namespace std;

struct DSU{
    int n;
    vector<vector<int>> cmp;
    vector<int> id;

    DSU(int _n):n(_n), cmp(n+1), id(n+1){
        for(int i=1; i<=n; i++)id[i]=i, cmp[i].push_back(i);
    }

    void merge(int x, int y){
        if(cmp[x].size()>cmp[y].size())swap(x, y);
        for(auto& u:cmp[x]){
            cmp[y].push_back(u);
            id[u]=y;
        }cmp[x].clear();
    }

    int add(int x, int y){
        x=id[x], y=id[y];
        if(x==y)return 0;
        merge(x, y);
        return 1;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0; long long sum=0;
    cin>>n>>m;
    
    vector<vector<pair<int, long long>>> adj(n+1);
    vector<long long> w(m);
    vector<int> x(m), y(m), p(m);
    DSU G(n);

    for(int i=0; i<m; i++){
        cin>>x[i]>>y[i]>>w[i];
        p[i]=i;
    }

    sort(p.begin(), p.end(), [&](int& x, int& y){
        return w[x]<w[y];
    });

    for(auto& i:p){
        if(!G.add(x[i], y[i]))continue;
        sum+=w[i];
        adj[x[i]].push_back({y[i], w[i]});
        adj[y[i]].push_back({x[i], w[i]});
    }

    vector<vector<long long>> par(n+1, vector<long long> (20)), dp=par;
    vector<int> pre(n+1, 0), pos(n+1, 0);

    function<void(int, int, int)> dfs = [&](int x, int y, int w){
        par[x][0]=y; dp[x][0]=w; pre[x]=++k;
        for(int h=1; h<20; h++){
            par[x][h]=par[par[x][h-1]][h-1];
            dp[x][h]=max(dp[x][h-1], dp[par[x][h-1]][h-1]);
        }

        for(auto& [u, p]:adj[x]){
            if(u==y)continue;
            dfs(u, x, p);
        }
        pos[x]=k;
    };

    function<bool(int, int)> is_parent = [&](int x, int y){
        return pre[x]<=pre[y] && pos[y]<=pos[x];
    };

    function<long long(int, int)> query = [&](int x, int y){
        long long res=0;
        for(int h=19; h>=0; h--){
            if(is_parent(par[x][h], y))continue;
            res=max(res, dp[x][h]);
            x=par[x][h];
        }
        for(int h=19; h>=0; h--){
            if(is_parent(par[y][h], x))continue;
            res=max(res, dp[y][h]);
            y=par[y][h];
        }
        if(!is_parent(x, y))res=max(res, dp[x][0]);
        if(!is_parent(y, x))res=max(res, dp[y][0]);
        return res;
    };

    dfs(1, 1, 0);

    for(int i=0; i<m; i++){
        cout<<sum-query(x[i], y[i])+w[i]<<"\n";
    }

    return 0;
}