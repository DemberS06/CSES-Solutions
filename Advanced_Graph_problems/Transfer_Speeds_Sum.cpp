#include <bits/stdc++.h>

using namespace std;

struct DSU{
    int n;
    vector<int> id;
    vector<vector<int>> cmp;

    DSU(int _n){
        n=_n;
        id.resize(n+1);
        cmp.resize(n+1);
        for(int i=1; i<=n; i++)cmp[i].push_back(i), id[i]=i;
    }

    void merge(int x, int y){
        if(cmp[x].size()>cmp[y].size())swap(x, y);

        for(auto& u:cmp[x]){
            id[u]=y;
            cmp[y].push_back(u);
        }cmp[x].clear();
    }

    long long add(int x, int y){
        x=id[x], y=id[y];
        long long res=(long long)cmp[x].size()*(long long)cmp[y].size();
        merge(x, y);
        return res;
    }

};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; long long ans=0;
    cin>>n;

    vector<tuple<long long, int, int>> v(n-1);
    DSU G(n);

    for(auto& [w,x,y]:v)cin>>x>>y>>w;
    sort(v.rbegin(), v.rend());

    for(auto& [w,x,y]:v)ans+=w*G.add(x, y);

    cout<<ans;

    return 0;
}