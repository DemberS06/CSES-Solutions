#include <bits/stdc++.h>

using namespace std; 

struct DSU{
    int n;
    vector<set<int>> f0, f1;
    vector<int> id, bit;
    vector<vector<int>> cmp;
    DSU(int _n):n(_n), f0(n+1), f1(n+1), id(n+1), bit(n+1, 0), cmp(n+1){
        for(int i=1; i<=n; i++){
            id[i]=i;
            cmp[i].push_back(i);
            f1[i].insert(1e9);
            f0[i]=f1[i];
            f0[i].insert(i);
        }
    }

    void merge1(int x, int y){
        if(cmp[x].size()<cmp[y].size())swap(x, y);
        if(f0[x].size()<f0[y].size())swap(f0[x], f0[y]);
        if(f1[x].size()<f1[y].size())swap(f1[x], f1[y]);
        for(auto& u:f0[y])f0[x].insert(u); f0[y].clear();
        for(auto& u:f1[y])f1[x].insert(u); f1[y].clear();
        for(auto& u:cmp[y]){
            id[u]=x;
            cmp[x].push_back(u);
        }cmp[y].clear();
    }
    void merge0(int x, int y){
        if(cmp[x].size()<cmp[y].size())swap(x, y);
        if(f0[x].size()<f1[y].size())swap(f0[x], f1[y]);
        if(f1[x].size()<f0[y].size())swap(f1[x], f0[y]);
        for(auto& u:f0[y])f1[x].insert(u); f0[y].clear();
        for(auto& u:f1[y])f0[x].insert(u); f1[y].clear();
        for(auto& u:cmp[y]){
            id[u]=x; bit[u]^=1;
            cmp[x].push_back(u);
        }cmp[y].clear();
    }

    void add(int x, int y){
        int d=bit[x]^bit[y];
        x=id[x]; y=id[y];
        if(x==y)return;
        if(d)merge1(x, y);
        else merge0(x, y);
    }

    bool push(int x, int y){
        y=id[y];
        auto a=*f0[y].begin(), b=*f1[y].begin();
        if(a<x && b<x)return 0;
        if(a<x)add(x, a);
        else add(x, b);
        return 1;
    }
    int low(int x){
        int y=id[x];
        return min(*f0[y].begin(), *f1[y].begin());
    }
    void pop(int x){
        int y=id[x];
        if(bit[x])f1[y].erase(x);
        else      f0[y].erase(x);
    }
    int bt(int x){
        return bit[x];
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, h=0; cin>>n;
    vector<int> vis(n+2, 0), a(n); DSU G(n);
    set<int> f;

    for(int i=0, z, h=1; i<n; i++){
        int& x=a[i]; cin>>x; vis[x]=1;
        while(!f.empty()){
            auto y=*f.begin();
            if(y>x)break;
            f.erase(y);
            if(!G.push(x, y)){
                cout<<"IMPOSSIBLE\n";
                return 0;
            }
        }
        f.insert(G.low(x));
        while(vis[h]){
            G.pop(h);
            f.erase(h);
            f.insert(G.low(h));
            h++;
        }
    }

    for(auto& i:a)cout<<G.bt(i)+1<<' ';

    return 0;
}