#include <bits/stdc++.h>

using namespace std;

const long long N=1e5+5, H=19;

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

        for(int h=0; h<H-1; h++){
            for(int i=1, p=0; i<=n; i++){
                if(i!=n && b[a[i]][h]==b[a[i-1]][h])continue;
                sort(a+p, a+i, [&](int& x, int& y){
                    if(x+(1<<h)>=n || (y+(1<<h))>=n)return y<x;
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


};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s, t; int k, n;
    cin>>s>>k; s+=' '; n=s.size();

    SuffArr S(s);

    for(int i=0, x, y, l, r, p, md, m; i<k; i++){
        cin>>t;
        
        x=-1, l=1, r=n;
        while(l<=r){
            md=(l+r)/2; p=a[md-1]; m=min(n-p, (int)t.size());
            for(int h=0; h<m; h++){
                if(s[p+h]==t[h])continue;
                if(s[p+h]<t[h])l=md+1;
                else r=md-1;
                break;
            }
            if(l<=md && r>=md){
                if(m>=t.size())x=md-1;
                l=md+1;
            }
        }
        if(x==-1){
            cout<<"0\n";
            continue;
        }
        y=-1, l=1, r=n;
        while(l<=r){
            md=(l+r)/2; p=a[md-1]; m=min(n-p, (int)t.size());
            for(int h=0; h<m; h++){
                if(s[p+h]==t[h])continue;
                if(s[p+h]<t[h])l=md+1;
                else r=md-1;
                break;
            }
            if(l<=md && r>=md){
                if(m>=t.size())y=md-1, r=md-1;
                else l=md+1;
            }
        }
        if(y==-1){
            cout<<"0\n";
            continue;
        }
        cout<<abs(y-x)+1<<"\n";
    }

    return 0;
}