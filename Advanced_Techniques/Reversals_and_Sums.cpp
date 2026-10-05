#include <bits/stdc++.h>

using namespace std;

struct Treap{
    int n, cnt=0, root=0;
    vector<int> l,r,t,p,lzy;
    vector<long long> sum, val;
    Treap(int _n):n(_n), l(n+1, 0), sum(n+1, 0){
        r=t=p=lzy=l; val=sum;
        random_device rd;
        mt19937 gen(rd());
        for(int i=1, x; i<=n; i++)p[i]=gen(), push();
    }

    void update(int x){
        t[x]=1+t[l[x]]+t[r[x]];
        sum[x]=val[x]+sum[l[x]]+sum[r[x]];
    }

    void rev(int x){
        if(!lzy[x])return;
        lzy[x]=0;
        swap(l[x], r[x]);
        lzy[l[x]]^=1;
        lzy[r[x]]^=1;
    }

    int merge(int x, int y){
        if(!x || !y)return x?x:y;
        rev(x); rev(y);
        if(p[x]>p[y]){
            r[x]=merge(r[x], y);
            update(x);
            return x;
        }
        l[y]=merge(x, l[y]);
        update(y);
        return y;
    }

    void push(){
        cnt++;
        cin>>val[cnt]; 
        sum[cnt]=val[cnt]; t[cnt]=1; 
        root=merge(root, cnt);
    }

    pair<int, int> split(int x, int k){
        if(!x)return {0, 0};
        rev(x);
        if(t[l[x]]>=k){
            auto [ll,lr]=split(l[x], k);
            l[x]=lr;
            update(x);
            return {ll, x};
        }
        auto [rl,rr]=split(r[x], k-t[l[x]]-1);
        r[x]=rl;
        update(x);
        return {x, rr};
    }

    void cut(int a, int b){
        auto [p, q]=split(root, b);
        auto [f, g]=split(p, a-1);
        lzy[g]^=1;
        root=merge(f, g);
        root=merge(root, q);
    }

    long long ans(int a, int b){
        auto [p, q]=split(root, b);
        auto [f, g]=split(p, a-1);
        long long res=sum[g];
        root=merge(f, g);
        root=merge(root, q);
        return res;
    }

};

int main(){
    cin.tie(0); cout.tie(0);ios_base::sync_with_stdio(0);
    int n, q;
    cin>>n>>q;
    Treap T(n);

    for(int t, x, y; q--;){
        cin>>t>>x>>y;
        if(t==1)T.cut(x, y);
        else cout<<T.ans(x, y)<<"\n";
    }
    return 0;
}