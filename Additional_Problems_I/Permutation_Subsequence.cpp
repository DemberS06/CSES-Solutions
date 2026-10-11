#include<bits/stdc++.h>

using namespace std;

struct SGT{
    int n;
    vector<int> a, x, b;
    SGT(int _n):n(_n), a(n+1, 0), x(4*n, 0), b(n+1){}

    int query(int i, int l, int r, int p, int q){
        if(l>r || q<l || p>r)return 0;
        if(l>=p && r<=q)return x[i];
        int u=query(2*i+1, l, (l+r)/2, p, q);
        int v=query(2*i, (l+r)/2+1, r, p, q);
        if(a[v]>a[u])return v;
        return u;
    }
    
    void update(int i, int l, int r, int p){
        if(l>r || p>r || p<l)return;
        if(l==r){
            x[i]=p;
            return;
        }
        update(2*i+1, l, (l+r)/2, p);
        update(2*i, (l+r)/2+1, r, p);
        if(a[x[2*i]]>a[x[2*i+1]])x[i]=x[2*i];
        else x[i]=x[2*i+1];
    }

    void update(int p){
        b[p+1]=query(1,1,n,1,p);
        a[p+1]=a[b[p+1]]+1;
        update(1,1,n, p+1);
    }

    vector<int> ans(){
        vector<int> res;
        for(int p=x[1]; p>0; p=b[p])res.push_back(p-1);
        reverse(res.begin(), res.end());
        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;cin>>n>>m;
    vector<int> a(n), b(m);
    for(auto& u:a)cin>>u;
    for(auto& u:b)cin>>u;
    if(n>m)swap(n, m), swap(a, b);
    vector<int> p(m+1);
    for(int i=0; i<m; i++)p[b[i]]=i;

    SGT S(m+1);

    for(auto& u:a)S.update(p[u]);
    auto ans=S.ans();
    cout<<ans.size()<<"\n";
    for(auto& u:ans)cout<<b[u]<<' ';

    return 0;
}