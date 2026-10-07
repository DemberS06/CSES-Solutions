#include <bits/stdc++.h>

using namespace std;

struct CHT{
    int p=0;
    vector<long long> a, b;
    bool bad(int x, int y, long long m, long long q){
        return (q-b[x])*(a[x]-a[y])<=(b[y]-b[x])*(a[x]-m);
    }
    long long val(int i, long long x){
        return a[i]*x+b[i];
    }
    void push(long long m, long long q){
        if(!a.empty() && a.back()==m){
            if(b.back()<=q)return;
            a.pop_back(); b.pop_back();
        }
        while(a.size()>1 && bad(a.size()-2, a.size()-1, m, q)){
            a.pop_back(); b.pop_back();
        }
        a.push_back(m), b.push_back(q);
        p=min(p, (int)a.size()-1);
    }
    long long query(long long x){
        while(p+1<a.size() && val(p, x)>=val(p+1, x))p++;
        return val(p, x);
    }

};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long m, b=0, x;
    int n;
    cin>>n>>m;
    CHT C;
    C.push(m, b);

    vector<long long> s(n), f(n);
    for(auto& u:s)cin>>u;
    for(auto& u:f)cin>>u;
    for(int i=0; i<n; i++){
        x=s[i], m=f[i];
        b=C.query(x);
        C.push(m, b);
    }

    cout<<b;

    return 0;
}