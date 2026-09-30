#include<bits/stdc++.h>
 
using namespace std;
 
const int N=5e5+1;
 
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();
 
    int n; 
    cin>>n;
    vector<bitset<2*N>> dp(n+1); dp[0][N].flip();
    vector<int> v(n);
    multiset<pair<int, int>> a, b;
 
    for(int i=0; i<n; i++){
        cin>>v[i];
        dp[i+1]=(dp[i]>>v[i])|(dp[i]<<v[i]);
    }
 
    if(!dp[n][N]){
        cout<<"-1";
        return 0;
    }
 
    for(int i=n, p=N; i>0; i--){
        if(dp[i-1][p-v[i-1]])a.insert({i, v[i-1]}), p-=v[i-1];
        else b.insert({i, v[i-1]}), p+=v[i-1];
    }
 
    while(!a.empty()){
        auto [i, x]=*a.rbegin();
        auto [j, y]=*b.rbegin();
        a.erase(a.find({i, x}));
        b.erase(b.find({j, y}));
        cout<<x<<' '<<y<<"\n";
        int z=min(x, y);
        x-=z; y-=z;
        if(x)a.insert({i, x});
        else b.insert({j, y});
    }    
 
    return 0;
}