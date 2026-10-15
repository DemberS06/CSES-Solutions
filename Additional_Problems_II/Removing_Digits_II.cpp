#include <bits/stdc++.h>

using namespace std;

map<tuple<int, int, long long>, tuple<long long, long long, int>> memo;
long long pot[20];

tuple<long long, long long, int> go(int m, int k, long long x){
    if(memo.count({m, k, x}))return memo[{m, k, x}];
    long long res=0, z=x;
    if(k==1){
        while(x>=m){
            if(x==0)return {res, 0, 0};
            res++; x=0;
        }

        memo[{m, k, z}]={res+1, x-m+10, 1};
        return memo[{m, k, z}];
    }
    int d=x/pot[k-1], g=1;
    while(d>=0){
        auto [s, y, f]=go(max(m, d), k-1, x%pot[k-1]);
        x=y; res+=s;
        if(!f){
            g=0;
            x+=pot[k-1]*d;
            break;
        }
        d--;
    }
    if(d<0)x+=pot[k-1]*9;
    memo[{m, k, z}]={res, x, g};
    return memo[{m, k, z}];
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long x, k=0; cin>>x; pot[0]=1;
    for(long long y=x; y; k++)y/=10;
    for(int i=1; i<20; i++)pot[i]=pot[i-1]*10;
    
    auto [ans, _, __]=go(0, k, x);
    cout<<ans;
    
    return 0;
}