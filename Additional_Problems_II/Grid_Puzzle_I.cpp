#include <bits/stdc++.h>

using namespace std;

struct Dinic{
    struct Edge{
        int to, rev;
        long long cap;
        Edge(int _to, int _rev, long long _cap){
            to=_to, rev=_rev, cap=_cap;
        }
    };
    int n, s, t;
    vector<vector<Edge>> adj;
    vector<int> dis, it;
    Dinic(int _n):n(_n), adj(n+1), dis(n+1), it(n+1){}
    void add_edge(int u, int v, long long c){
        adj[u].push_back(Edge{v, adj[v].size(), c});
        adj[v].push_back(Edge{u, adj[u].size()-1, 0});
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
                if(dis[e.to]||!e.cap)continue;
                dis[e.to]=dis[x]+1;
                q.push(e.to);
            }
        }
        return dis[t]>0;
    }
    long long dfs(int x, long long f){
        if(x==t)return f;
        for(int &i=it[x]; i<adj[x].size(); i++){
            auto &e=adj[x][i];
            if(dis[x]!=dis[e.to]-1||!e.cap)continue;
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
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, sumA=0, sumB=0; cin>>n;
    vector<int> a(n), b(n);
    Dinic G(2*n+2);
    for(int i=0; i<n; i++){
        cin>>a[i];
        sumA+=a[i];
        G.add_edge(2*n, i, a[i]);
        for(int j=n; j<2*n; j++)G.add_edge(i, j, 1);
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
        sumB+=b[i];
        G.add_edge(n+i, 2*n+1, b[i]);
    }
    long long f=G.max_flow(2*n, 2*n+1);
    if(f!=sumA || sumA!=sumB){
        cout<<"-1\n";
        return 0;
    }
    vector<string> s(n, string(n, '.'));
    for(int i=0; i<n; i++){
        for(int j=1; j<=n; j++){
            auto& e=G.adj[i][j];
            if(e.cap==0)s[i][j-1]='X';
        }
    }
    for(auto& u:s)cout<<u<<"\n";
    return 0;
}