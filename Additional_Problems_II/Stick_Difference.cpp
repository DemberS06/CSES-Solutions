#include <bits/stdc++.h>

using namespace std;

struct SGT{
    int n;
    vector<long long> sgt;
    SGT(int _n):n(_n), sgt(4*n, 0){}

    void update(int i, int l, int r, int p, long long x){
        if(l>r || p<l || p>r)return;
        if(l==r){
            sgt[i]=x;
            return;
        }
        update(2*i+1, l, (l+r)/2, p, x);
        update(2*i, (l+r)/2+1, r, p, x);
        sgt[i]=max(sgt[2*i], sgt[2*i+1]);
    }

    void update(int p, long long x){
        update(1,1,n,p+1,x);
    }

    long long top(){
        return sgt[1];
    }
};

struct SP{
    vector<vector<long long>> sp;
    SP(vector<long long>& v){
        int k=v.size(), lg=1;
        while((1<<lg)<=k)lg++;
        sp.assign(lg, vector<long long>(k));
        sp[0]=v;
        for(int j=1; j<lg; j++)
            for(int i=0; i+(1<<j)<=k; i++)
                sp[j][i]=min(sp[j-1][i], sp[j-1][i+(1<<(j-1))]);
    }
 
    long long query(int l, int r){
        int j=__lg(r-l+1);
        return min(sp[j][l], sp[j][r-(1<<j)+1]);
    }
};
 
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<long long> a(n);
    long long tot=0, mn=1e18, ans;
    for(auto& u:a){
        cin>>u;
        tot+=u; mn=min(mn, u);
    }
    long long L=min(max(1ll, tot/(2*(n+m))), mn);
 
    vector<pair<long long, int>> slw;
    for(int i=0; i<n; i++){
        long long c=a[i]/mn, x;
        for(x=a[i]/(c+1); x>=L; x=a[i]/(c+1)){
            slw.push_back({x, i});
            c=a[i]/x;
            x=a[i]/(c+1);
        }
    }
    sort(slw.rbegin(), slw.rend());
 
    SGT seg(n);
    vector<long long> c(n);
    long long cnt=0;
    for(int i=0; i<n; i++){
        c[i]=a[i]/mn; cnt+=c[i];
        seg.update(i, (a[i]+c[i]-1)/c[i]);
    }
 
    vector<long long> A, f, g;
    A.push_back(mn); f.push_back(seg.top()); g.push_back(cnt);
    for(int j=0, i; j<slw.size();){
        long long x=slw[j].first;
        while(j<slw.size() && slw[j].first==x){
            i=slw[j].second;
            cnt-=c[i]; c[i]=a[i]/x; cnt+=c[i];
            seg.update(i, (a[i]+c[i]-1)/c[i]);
            j++;
        }
        A.push_back(x); f.push_back(seg.top()); g.push_back(cnt);
    }
 
    int k=A.size();
    vector<long long> dif(k);
    for(int i=0; i<k; i++)dif[i]=f[i]-A[i];
    SP sp(dif);
 
    set<pair<long long, int>> pq;
    vector<long long> parts(n, 1);
    for(int i=0; i<n; i++)pq.insert({a[i], i});
 
    for(long long T=n+1; T<=n+m; T++){
        auto [v, i]=*pq.rbegin();
        if(v>1){
            pq.erase(*pq.rbegin()); parts[i]++;
            pq.insert({(a[i]+parts[i]-1)/parts[i], i});
        }
        long long Q=(*pq.rbegin()).first;
 
        int P=lower_bound(g.begin(), g.end(), T)-g.begin();
        int R=lower_bound(f.begin(), f.end(), Q, greater<long long>())-f.begin();
        long long x=A[P], y=A[R];
 
        ans=Q-min(y, x);
        if(y<=x && R>P)ans=min(ans, sp.query(P, R-1));
        cout<<ans<<' ';
    }
 
    return 0;
}