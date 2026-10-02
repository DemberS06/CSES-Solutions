#include <bits/stdc++.h>

using namespace std;

const long long N=1e5+1, H=21; 
int a[N], b[N][H];

struct SuffArr{
    int n;
    string s;

    SuffArr(string _s){
        s=_s;
        n=s.size();
        for(int i=0; i<n; i++)a[i]=i;

        sort(a, a+n, [&](int& x, int& y){
            return s[x]<s[y];
        });

        for(int i=1; i<n; i++){
            b[a[i]][0]=b[a[i-1]][0];
            if(s[a[i]]!=s[a[i-1]])b[a[i]][0]++;
        }

        for(int h=0; h<20; h++){
            for(int i=1, p=0; i<=n; i++){
                if(i!=n && b[a[i]][h]==b[a[p]][h])continue;
                sort(a+p, a+i, [&](int& x, int& y){
                    if(x+(1<<h)>=n || y+(1<<h)>=n)return y<x;
                    return b[x+(1<<h)][h]<b[y+(1<<h)][h];
                });
                p=i;
            }

            for(int i=1; i<n; i++){
                b[a[i]][h+1]=b[a[i-1]][h+1];
                if(b[a[i]][h]!=b[a[i-1]][h] || a[i]+(1<<h)>=n || a[i-1]+(1<<h)>=n || b[a[i]+(1<<h)][h]!=b[a[i-1]+(1<<h)][h])b[a[i]][h+1]++;            
            }
        }
    }

    int query(int x, int y){
        int d=0;
        if(x>y)swap(x, y);
        for(int h=H-1; h>=0; h--){
            if(y+(1<<h)>=n || b[x][h]!=b[y][h])continue;
            d+=(1<<h);
            x+=(1<<h);
            y+=(1<<h);
        }
        return d;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s, t;
    int k, n;
    cin>>s>>k; s+=' ';
    n=s.size();
    
    SuffArr S(s);
    
    for(int i=0, l, r, ans; i<k; i++){
        cin>>t;
        ans=0;
        
        l=1, r=n;
        while(!ans && l<=r){
            int md=(l+r)/2, p=a[md-1], m=min(n-p, (int)t.size());
            if(m>=t.size())ans=1;
            //cout<<md<<' '<<p<<"\n";
            for(int i=0; i<m; i++){
                if(s[p+i]==t[i])continue;
                ans=0;
                if(s[p+i]<t[i])l=md+1;
                else r=md-1;
                break;
            }
            if(l<=md && r>=md)l=md+1;
        }
        if(ans)cout<<"YES\n";
        else cout<<"NO\n";
    }

    return 0;
}