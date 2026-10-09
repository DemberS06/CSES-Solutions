#include <bits/stdc++.h>

using namespace std;

struct MCMF{
    struct Edge{
        int to;
        long long cap, cost;
        Edge(int _to, long long _cap, long long _cost){
            to=_to; cap=_cap; cost=_cost;
        };
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    MCMF(int _n):n(_n), g(n+1){}
    void add_edge(int u, int v, long long cap, long long cost){
        g[u].push_back(e.size());
        e.push_back(Edge(v, cap, cost));
        g[v].push_back(e.size());
        e.push_back(Edge(u, 0, -cost));
    }
    pair<long long, long long> flow(int s, int t, long long maxf=LLONG_MAX){
        const long long INF=1e18;
        long long fl=0, cost=0;
        while(fl<maxf){
            vector<long long> d(n+1, INF);
            vector<int> pe(n+1, -1), inq(n+1, 0);
            deque<int> q;
            d[s]=0;
            q.push_back(s);
            while(!q.empty()){
                int u=q.front();
                q.pop_front();
                inq[u]=0;
                for(auto &id:g[u]){
                    if(e[id].cap<=0 || d[u]+e[id].cost>=d[e[id].to])continue;
                    d[e[id].to]=d[u]+e[id].cost;
                    pe[e[id].to]=id;
                    if(!inq[e[id].to])inq[e[id].to]=1, q.push_back(e[id].to);
                }
            }
            if(d[t]==INF)break;
            long long f=maxf-fl;
            for(int v=t; v!=s; v=e[pe[v]^1].to)f=min(f, e[pe[v]].cap);
            for(int v=t; v!=s; v=e[pe[v]^1].to){
                e[pe[v]].cap-=f;
                e[pe[v]^1].cap+=f;
            }
            fl+=f;
            cost+=f*d[t];
        }
        return {fl, cost};
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, sumA=0, sumB=0; cin>>n;
    vector<int> a(n), b(n);
    MCMF G(2*n+2);
    for(int i=0; i<n; i++){
        cin>>a[i];
        sumA+=a[i];
        G.add_edge(2*n, i, a[i], 0);
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
        sumB+=b[i];
        G.add_edge(i+n, 2*n+1, b[i], 0);
    }
    for(int i=0, x; i<n; i++){
        for(int j=n; j<2*n; j++){
            cin>>x;
            G.add_edge(i, j, 1, -x);
        }
    }

    auto [f, c]=G.flow(2*n, 2*n+1);
    
    if(f!=sumA || sumA!=sumB){
        cout<<"-1\n";
        return 0;
    }

    vector<string> s(n, string(n, '.'));

    cout<<-c<<"\n";
    for(int i=0; i<n; i++){
        for(int j=1; j<=n; j++){
            auto& e=G.e[G.g[i][j]];
            if(!e.cap)s[i][j-1]='X';
        }
    }

    for(auto& u:s)cout<<u<<'\n';
    

    return 0;
}