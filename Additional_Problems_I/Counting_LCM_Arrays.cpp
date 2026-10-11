#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9+7;
void mult(auto& x, auto& y){
    int n=x.size();
    auto res=y;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            res[i][j]=0;
            if(i==0 || j==0 || (i==1 && j==1)){
                for(int k=0; k<n; k++){
                    res[i][j]=(res[i][j]+x[i][k]*y[k][j])%mod;
                }
            }
            else{
                if(j>1)res[i][j]=res[i][j-1];
                else res[i][j]=res[i-1][j];
            }
        }
    }
    swap(x, res);
}

void expbin(auto& res, int y){
    auto x=res;
    while(y){
        if(y&1)mult(res, x);
        mult(x, x);
        y>>=1;
    }
}
    

void solve(){
    int n, k; cin>>n>>k;
    long long ans=1;
    map<int, int>mp;
    for(int i=2, x=k; i*i<=x; i++){
        while(k%i==0)mp[i]++, k/=i;
    }if(k!=1)mp[k]++;
    
    
    function<void(int)> solve = [&](int x){
        vector<vector<long long>> a(x+1, vector<long long> (x+1, 0));
        for(int i=0; i<=x; i++)a[i][0]=a[0][i]=1;
        expbin(a, n-2);
        long long sum=0;
        for(auto& v:a){
            for(auto& u:v)sum+=u;
        }
        sum%=mod;
        ans=ans*sum%mod;
    };
    for(auto& [_, u]:mp)solve(u);
    cout<<ans<<"\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t; cin>>t;
    while(t--)solve();
    return t+1;
}