#include<bits/stdc++.h>

using namespace std;

const long long N=669, mod=1e9+7;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;

    vector<int> vis(5001, 0), p;
    vector<bitset<N>> a(n), S(N);
    for(int i=2; i<=5000; i++){
        if(vis[i])continue;
        p.push_back(i);
        for(int j=i; j<=5000; j+=i)vis[j]=i;
    }
    long long ans=1;

    for(int i=0, x; i<n; i++){
        cin>>x;
        for(int h=0; h<N; h++){
            while(x%p[h]==0)a[i][h].flip(), x/=p[h];
        }

        for(int h=N-1; h>=0; h--){
            if(S[h].count()==0 && a[i][h]){
                S[h]=a[i];
                break;
            }
            if(h==0)ans=ans*2%mod;
            if(!a[i][h])continue;
            a[i]^=S[h];
        }
    }

    cout<<ans;

    return 0;
}