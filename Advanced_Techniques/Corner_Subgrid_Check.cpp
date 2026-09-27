#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, k;
    cin>>n>>k;

    string s; vector<int> ans(k, 0);
    bitset<3000> b[n][k], c[k];

    for(int i=0; i<n; i++){
        cin>>s;
        for(int h=0; h<k; h++)c[h]=0;
        for(int j=0; j<n; j++){
            c[s[j]-'A'][j]=1;
        }
        for(int j=0, x; j<n; j++){
            x=s[j]-'A';
            if(ans[x])continue;
            c[x][j]=0;
            if((b[j][x]&c[x]).any())ans[x]=1;
            b[j][x]|=c[x];
            c[x][j]=1;
        }
    }

    for(int i=0; i<k; i++)
        if(ans[i])cout<<"YES\n";
        else cout<<"NO\n";
        
    return 0;
}