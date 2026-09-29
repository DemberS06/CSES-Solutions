#include <bits/stdc++.h>

using namespace std;

struct DSU{
    int n, m;
    vector<int> id;
    vector<vector<int>> cmp;

    DSU(int _n){
        n=m=_n;
        id.resize(n+1);
        cmp.resize(n+1);
        for(int i=1; i<=n; i++)id[i]=i, cmp[i].push_back(i);
    }

    void merge(int x, int y){
        if(cmp[x].size()>cmp[y].size())swap(x, y);
        for(auto& u:cmp[x]){
            cmp[y].push_back(u);
            id[u]=y;
        }cmp[x].clear();
    }

    void add(int x, int y){
        if(id[x]==id[y])return;
        m--;
        merge(id[x], id[y]);
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m, k;
    cin>>n>>m>>k;

    vector<pair<int, int>> f, g, h; g.reserve(k);
    vector<int> ans; ans.reserve(k);
    DSU G(n);
    
    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        if(x>y)swap(x, y);
        f.push_back({x, y});
    }

    for(int i=0, x, y; i<k; i++){
        cin>>x>>y;
        if(x>y)swap(x, y);
        g.push_back({x, y});
    }reverse(g.begin(), g.end());
    
    h=g;
    sort(f.begin(), f.end());
    sort(h.begin(), h.end());

    for(int i=0, j=0; i<m; i++){
        while(j<k && h[j]<f[i])j++;
        if(j<k && h[j]==f[i])continue;
        G.add(f[i].first, f[i].second);
    }
    for(auto& [x, y]:g)ans.push_back(G.m), G.add(x, y);
    
    reverse(ans.begin(), ans.end());
    for(auto& u:ans)cout<<u<<' ';

    return 0;
}