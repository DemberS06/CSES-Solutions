// hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, k;
    cin>>n>>k;

    vector<string> g(n);
    for(auto& s:g)cin>>s;

    vector<long long> ans(k, 0);
    vector<long long> h(n, 0), l(n), r(n), st(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i && g[i][j]==g[i-1][j])h[j]++;
            else h[j]=1;
        }

        int x, y, c=0;
        for(int j=0; j<n; j++){
            if(g[i][j]!=c)x=-1, y=j-1;
            while(x!=-1 && h[st[x]]>=h[j])x--;
            l[j]=(x==-1)?y:st[x];
            st[++x]=j;
            c=g[i][j];
        }
        
        c=0;
        for(int j=n-1; j>=0; j--){
            if(g[i][j]!=c)x=-1, y=j+1;
            while(x!=-1 && h[st[x]]>h[j])x--;
            r[j]=(x==-1)?y:st[x];
            st[++x]=j;
            c=g[i][j];
        }

        for(int j=0; j<n; j++){
            if(h[j]>0)ans[g[i][j]-'A']+=h[j]*(j-l[j])*(r[j]-j);
        }
    }

    for(auto& u:ans)cout<<u<<'\n';

    return 0;
}
