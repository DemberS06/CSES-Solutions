// hola soy Dember :D
#include "bits/stdc++.h"

using namespace std;

int main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k;
    cin>>n>>k;

    vector<int> a(n+1, 0), b(n+1, 0), c(n+1, 0);
    vector<string> g(n);
    for(auto& s:g)cin>>s;
    
    int w=(1<<k)-1;
    long long ans=0;

    for(int j=0; j<n; j++) {
        vector<int> v(n);
        for(int j2=j; j2<n; j2++){
            for(int i=0; i<n; i++)v[i]|=1<<(g[i][j2]-'A');
            
            int l=0, r=0, res=0;
            for(int i=0; i<n; i++){
                c[++l]=v[i];
                a[l]=c[l]|a[l-1];
                while((a[l]|b[r])==w){
                    if (!r) {
                        for(int j=l, i=1; j>=1; j--, i++)b[i]=b[i-1]|c[j];
                        r=l;
                        l=0;
                    }
                    r--;
                    res++;
                }
                ans+=res;
            }
        }
    }

    cout<<ans<<'\n';

    return 0;
}