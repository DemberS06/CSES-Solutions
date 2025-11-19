// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

struct SGT {
    int n;
    vector<int> st;
    SGT(int _n): n(_n), st(2*_n) {}

    void build(vector<long long>& A){
        for(int i=0;   i<n; i++)st[n+i]=A[i];
        for(int i=n-1; i>0; i--)st[i]=max(st[i<<1], st[i<<1|1]);
    }

    void update(int idx, long long v){
        idx+=n;
        st[idx]=v;
        while(idx>1)idx>>=1, st[idx]=max(st[idx<<1], st[idx<<1|1]);
    }

    int query(int l, int r){
        int res=0;
        for(l+=n, r+=n; l<=r; l>>=1, r>>=1) {
            if(l&1)res=max(res, st[l++]);
            if(!(r&1))res=max(res, st[r--]);
        }
        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m, curPos;
    cin>>n>>m;

    vector<vector<int>> adj(n);
    vector<int> a(n, 1), d(n, 0), parent(n), heavy_child(n, -1), head(n), pos(n), val(n);

    for(auto& u:val)cin>>u;

    for(int i=1, x, y; i<n; i++){
        cin>>x>>y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }

    function<int(int, int)> dfs = [&](int x, int p){
        parent[x]=p;
        int max_sz=0;
        for(int u:adj[x]){
            if(u==p)continue;
            d[u]=d[x]+1;
            int s=dfs(u, x);
            if(s>max_sz)max_sz=s, heavy_child[x]=u;
            a[x]+=s;
        }
        return a[x];
    };

    function<void(int, int)> hld = [&](int x, int p){
        if(heavy_child[p]==x)head[x]=head[p];
        else head[x]=x;
        pos[x]=curPos++;
        if(heavy_child[x]!=-1)hld(heavy_child[x], x);
        for(int u:adj[x]){
            if(u==p || u==heavy_child[x])continue;
            hld(u, x);
        }
    };

    dfs(0, 0);
    curPos=0;
    hld(0, 0);

    vector<long long> base(n);
    for(int i=0; i<n; i++)base[pos[i]]=val[i];

    SGT sgt(n);
    sgt.build(base);

    function<int(int, int)> query = [&](int x, int y){
        int ans=0;
        while(head[x]!=head[y]) {
            if(d[head[x]]>d[head[y]])swap(x, y);
            ans=max(ans, sgt.query(pos[head[y]], pos[y]));
            y=parent[head[y]];
        }
        if(d[x]>d[y])swap(x, y);
        ans=max(ans, sgt.query(pos[x], pos[y]));
        return ans;
    };

    while(m--){
        int t, x, y;
        cin>>t>>x>>y;
        if(t==1)sgt.update(pos[--x], y);
        else cout<<query(--x, --y)<<' ';
    }
    return m+1;
}
