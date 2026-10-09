#include <bits/stdc++.h>

using namespace std;
struct MCMF{
    struct Edge{
        int to;
        long long cap, cost;
        Edge(int _to, long long _cap, long long _cost){
            to=_to;
            cap=_cap;
            cost=_cost;
        }
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    MCMF(int _n): n(_n), g(_n+1){}
    void add_edge(int u, int v, long long cap, long long cost){
        g[u].push_back(e.size());
        e.push_back(Edge(v, cap, cost));
        g[v].push_back(e.size());
        e.push_back(Edge(u, 0, -cost));
    }  

    pair<long long, long long> flow(int s, int t, long long maxf=LLONG_MAX){
        const long long INF=1e18;
        long long f1=0, cost=0;
        while(f1<maxf){
            vector<long long> d(n+1, INF);
            vector<int> pe(n+1, -1), inq(n+1, 0);
            deque<int> q;
            d[s]=0;
            q.push_back(s);
            while(!q.empty()){
                int u=q.front();
                q.pop_front();
                inq[u]=0;
                for(auto& id:g[u]){
                    if(e[id].cap<=0 || d[u]+e[id].cost>=d[e[id].to])continue;
                    d[e[id].to]=d[u]+e[id].cost;
                    pe[e[id].to]=id;
                    if(!inq[e[id].to])inq[e[id].to]=1, q.push_back(e[id].to);
                }
            }
            if(d[t]==INF)break;
            long long f=maxf-f1;
            for(int v=t; v!=s; v=e[pe[v]^1].to)f=min(f, e[pe[v]].cap);
            for(int v=t; v!=s; v=e[pe[v]^1].to){
                e[pe[v]].cap-=f;
                e[pe[v]^1].cap+=f;
            }
            f1+=f;
            cost+=f*d[t];
        }
        return {f1, cost};
    }

    vector<vector<int>> route(int s, int t, int k){
        vector<vector<int>> res(k);
        
        for(int i=0, x; i<k; i++){
            x=s;
            res[i].push_back(x);
            while(x!=t){
                for(auto& id:g[x]){
                    if(id&1)continue;
                    if(e[id].cap)continue;
                    e[id].cap=1;
                    x=e[id].to;
                    res[i].push_back(x);
                    break;
                }
            }
        }

        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k;
    cin>>n>>m>>k;
    MCMF G(n);

    G.add_edge(0, 1, k, 0);

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        G.add_edge(x, y, 1, 1);
    }

    auto [f, c]=G.flow(0, n);
    if(f!=k){
        cout<<"-1\n";
        return 0;
    }

    cout<<c<<"\n";

    auto ans=G.route(1, n, k);

    for(auto& v:ans){
        cout<<v.size()<<"\n";;
        for(auto& u:v)cout<<u<<' ';cout<<"\n";
    }

    return 0;
}