#include <bits/stdc++.h>

using namespace std;

struct Hungarian{
    int n, m;
    vector<long long> u, v;
    vector<int> p, way, asig; 
    vector<vector<long long>> a;
    Hungarian(int _n, int _m):n(_n), m(_m), u(n+1), v(m+1), p(m+1){
        a.resize(n+1, vector<long long> (m+1, 0));
        way.resize(m+1, 0);
        asig.resize(n+1, 0);
    }

    long long solve(){
        const long long INF=1e18;
        fill(u.begin(), u.end(), 0);
        fill(v.begin(), v.end(), 0);
        fill(p.begin(), p.end(), 0);
        for(int i=1; i<=n; i++){
            p[0]=i;
            int j0=0;
            vector<long long> minv(m+1, INF);
            vector<int> used(m+1, 0);
            do{
                used[j0]=1;
                int i0=p[j0], j1=0;
                long long delta=INF;
                for(int j=1; j<=m; j++){
                    if(used[j])continue;
                    long long cur=a[i0][j]-u[i0]-v[j];
                    if(cur<minv[j])minv[j]=cur, way[j]=j0;
                    if(minv[j]<delta)delta=minv[j], j1=j;
                }
                for(int j=0; j<=m; j++){
                    if(used[j])u[p[j]]+=delta, v[j]-=delta;
                    else minv[j]-=delta;
                }
                j0=j1;
            }while(p[j0]);
            do{
                int j1=way[j0];
                p[j0]=p[j1];
                j0=j1;
            }while(j0);
        }
        for(int j=1; j<=m; j++){
            if(p[j])asig[p[j]]=j;
        }
        return -v[0];
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;

    Hungarian H(n, n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>H.a[i][j];
        }
    }

    cout<<H.solve()<<"\n";

    for(int i=1; i<=n; i++)cout<<i<<' '<<H.asig[i]<<"\n";


    return 0;
}