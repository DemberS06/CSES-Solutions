#include<bits/stdc++.h>

using namespace std;

struct DSU{
    int n;
    vector<int> id;
    vector<vector<int>> cmp;
    vector<vector<pair<int, int>>> r;
    vector<pair<int, int>> ans, edge;

    DSU(int _n):n(_n), id(n+1), cmp(n+1), r(n+1){
        for(int i=1; i<=n; i++)id[i]=i, cmp[i].push_back(i);
    }

    void merge(int x, int y, int i){
        if(r[x].size()>r[y].size())swap(x, y);
        for(auto& [j, u]:r[x]){
            if(id[u]==x)continue;
            if(id[u]==y)ans.push_back({i, j});
            else r[y].push_back({j, u});
        }r[x].clear();

        if(cmp[x].size()>cmp[y].size())swap(x, y), swap(r[x], r[y]);
        for(auto& u:cmp[x]){
            id[u]=y;
            cmp[y].push_back(u);
        }cmp[x].clear();
    }

    void get_ans(int& m, int& q){
        edge.resize(m); ans.reserve(q);
        for(auto& [x, y]:edge)cin>>x>>y;

        for(int i=0, x, y; i<q; i++){
            cin>>x>>y;
            if(x==y){
                ans.push_back({0, i});
                continue;
            }
            r[x].push_back({i, y});
            r[y].push_back({i, x});
        }

        for(int i=0; i<m; i++){
            auto &[x, y]=edge[i];
            if(id[x]==id[y])continue;
            merge(id[x], id[y], i+1);
        }
    }

};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    cin>>n>>m>>q;

    DSU G(n);
    vector<int> ans(q, -1);
    G.get_ans(m, q);
    for(auto& [i, u]:G.ans)ans[u]=i;

    for(auto& u:ans)cout<<u<<"\n";

    return 0;
}

