#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; long long k, ans=1e9;
    cin>>n>>k;

    vector<long long> v(n);
    for(auto& u:v)cin>>u;
    for(int i=0; i<n; i++)v.push_back(v[i]); v.push_back(k);

    vector<vector<int>> b(2*n+2, vector<int> (20, 2*n));

    for(long long i=0, j=0, x=0; i<2*n; i++){
        while(j<2*n&&x+v[j]<=k)x+=v[j], j++;
        b[i][0]=j-1;
        x-=v[i];
    }

    for(int h=1; h<20; h++){
        for(int i=0; i<2*n; i++){
            b[i][h]=b[b[i][h-1]+1][h-1];
        }
    }

    function<long long(int, int)> bl = [&](int x, int y){
        long long res=0;

        for(int h=19; h>=0; h--){
            if(b[x][h]>=y)continue;
            x=b[x][h]+1;
            res+=(1<<h);
        }

        if(x<y)res++;

        return res;
    };

    for(int i=0; i<n; i++)ans=min(ans, bl(i, n+i));
    cout<<ans;
    
    return 0;
}