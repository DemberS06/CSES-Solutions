#include <bits/stdc++.h>

using namespace std;

struct Dinic{
    struct Edge{
        int to, rev;
        long long cap;
        Edge(int _to, int _rev, long long _cap): to(_to), rev(_rev), cap(_cap) {}
    };
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> dis, it;
    Dinic(int _n): n(_n), adj(_n+1), dis(_n+1), it(_n+1) {}
    void add_edge(int u, int v, long long c){
        adj[u].push_back(Edge(v, adj[v].size(), c));
        adj[v].push_back(Edge(u, adj[u].size()-1, 0));
    }
    bool bfs(){
        fill(dis.begin(), dis.end(), 0);
        queue<int> q;
        q.push(s);
        dis[s]=1;
        while(!q.empty()){
            auto x=q.front();
            q.pop();
            for(auto& e:adj[x]){
                if(dis[e.to] || !e.cap)continue;
                dis[e.to]=dis[x]+1;
                q.push(e.to);
            }
        }
        return dis[t]>0;
    }
    long long dfs(int x, long long f){
        if(x==t)return f;
        for(int &i=it[x]; i<(int)adj[x].size(); i++){
            auto &e=adj[x][i];
            if(dis[x]!=dis[e.to]-1 || !e.cap)continue;
            long long tr=dfs(e.to, min(f, e.cap));
            if(!tr)continue;
            e.cap-=tr;
            adj[e.to][e.rev].cap+=tr;
            return tr;
        }
        return 0;
    }
    long long max_flow(int _s, int _t){
        s=_s, t=_t;
        long long flow=0;
        while(bfs()){
            fill(it.begin(), it.end(), 0);
            while(true){
                long long pushed=dfs(s, 1e18);
                if(!pushed)break;
                flow+=pushed;
            }
        }
        return flow;
    }
    vector<int> reach(){
        vector<int> vis(n+1, 0);
        queue<int> q;
        q.push(s);
        vis[s]=1;
        while(!q.empty()){
            auto x=q.front();
            q.pop();
            for(auto& e:adj[x]){
                if(vis[e.to] || !e.cap)continue;
                vis[e.to]=1;
                q.push(e.to);
            }
        }
        return vis;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    Dinic G(2*n+1);
    string s;

    for(int i=1; i<=n; i++){
        cin>>s;
        G.add_edge(0, i, 1);
        G.add_edge(i+n, 2*n+1, 1);
        for(int j=0; j<n; j++){
            if(s[j]=='.')continue;
            G.add_edge(i, n+j+1, 1);
        }
    }

    G.max_flow(0, 2*n+1);
    vector<int> vis=G.reach();
    vector<pair<int, int>> ans;

    for(int i=1; i<=n; i++){
        if(!vis[i])ans.push_back({1, i});
    }
    for(int j=n+1; j<=2*n; j++){
        if(vis[j])ans.push_back({2, j-n});
    }

    cout<<ans.size()<<"\n";
    for(auto& [x, y]:ans)cout<<x<<' '<<y<<"\n";

    return 0;
}