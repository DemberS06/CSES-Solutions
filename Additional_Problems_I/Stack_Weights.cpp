#include <bits/stdc++.h>

using namespace std;

struct SGT{
    int n;
    vector<int> mn, mx, lzy;
    SGT(int _n):n(_n), mn(4*n,0), mx(4*n,0), lzy(4*n, 0){}

    void update(int i, int l,int r, int p, int q, int x){
        if(l>r || q<l || p>r)return;
        if(l>=p && r<=q){
            lzy[i]+=x;
            return;
        }
        lzy[2*i]+=lzy[i]; lzy[2*i+1]+=lzy[i]; lzy[i]=0;
        update(2*i+1, l, (l+r)/2, p, q, x);
        update(2*i, (l+r)/2+1, r, p, q, x);
        mn[i]=min(mn[2*i]+lzy[2*i], mn[2*i+1]+lzy[2*i+1]);
        mx[i]=max(mx[2*i]+lzy[2*i], mx[2*i+1]+lzy[2*i+1]);
    }
    void update(int p, int x){
        update(1,1,n,1,p,x);
    }
    int query(){
        long long x=mn[1]+lzy[1];
        long long y=mx[1]+lzy[1];
        if(x*y<0)return 2;
        return x>=0;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
    SGT sgt(n);

    for(int i=0, x, p; i<n; i++){
        cin>>x>>p;
        sgt.update(x, 2*p-3);
        int y=sgt.query();
        if(y==0)cout<<">\n";
        if(y==1)cout<<"<\n";
        if(y==2)cout<<"?\n";
    }

    return 0;
}