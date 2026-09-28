#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

long long expbin(long long x, long long y){
    long long res=1;
    while(y){
        if(y&1)res=res*x%md;
        x=x*x%md;
        y>>=1;
    }
    return res;
}

struct Fenwick{
    int n;
    vector<long long> fwk;

    Fenwick(int _n){
        n=_n+1;
        fwk.resize(n+1, 0);
    }

    void update(int p, long long x){
        for(; p<=n; p+=-p&p)fwk[p]=(fwk[p]+x)%md;
    }

    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p)res=(res+fwk[p])%md;
        return res;
    }    

    long long query(int l, int r){
        return (md+query(r)-query(l-1))%md;
    }
};

struct Hash{
    int n;
    string s;
    long long x=537;
    Fenwick fwk;

    Hash(string _s):s(_s), n(_s.size()), fwk(_s.size()+5){
        long long d=x, v;
        for(int i=0; i<n; i++){
            v=d*(s[i]-'a'+1)%md;
            fwk.update(i+1, v);
            d=d*x%md;
        }
    }

    void update(int p, char c){
        long long v=(md+(long long)c-(long long)s[p])*expbin(x, p+1)%md;
        s[p]=c;
        fwk.update(p+1, v);
    }

    long long query(int l, int r){
        long long v=expbin(x, l); v=expbin(v, md-2);
        return fwk.query(l+1, r+1)*v%md;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, q;
    string s;
    cin>>n>>q>>s;

    Hash A(s);
    reverse(s.begin(), s.end());
    Hash B(s);

    for(int t, l, r; q--; ){
        cin>>t>>l;
        if(t==1){
            char c;
            cin>>c;
            A.update(l-1, c);
            B.update(n-l, c);
        }
        else{
            cin>>r;
            //for(int i=l-1; i<=r-1; i++)cout<<A.s[i];cout<<"\n";
            //for(int i=n-r; i<=n-l; i++)cout<<B.s[i];cout<<"\n";
            //cout<<A.query(l-1, r-1)<<' '<<B.query(n-r, n-l)<<" ";
            if(A.query(l-1, r-1)==B.query(n-r, n-l))cout<<"YES\n";
            else cout<<"NO\n";
        }
    }

    return 0;
}