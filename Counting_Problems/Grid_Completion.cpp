// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

const long long N=505, mod=1e9+7; 

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    function<long long(long long, long long)> expbin = [&](long long x, long long y){
        long long res=1;
        while(y){
            if(y&1)res=res*x%mod;
            x=x*x%mod;
            y/=2;
        }
        return res;
    };
    
    vector<long long> f(N+1, 1), r=f;
    for(int i=1; i<=N; i++)f[i]=f[i-1]*i%mod, r[i]=expbin(f[i], mod-2);
    
    function<long long(long long, long long)> nenk = [&](long long x, long long y){
        return f[x]*r[y]%mod*r[x-y]%mod;
    };

    int n;
    cin>>n;

    vector<int> rA(n, -1), cA(n, 0), rB=rA, cB=cA;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            char c;
            cin>>c;
            if(c=='A')rA[i]=j, cA[j]=1;
            if(c=='B')rB[i]=j, cB[j]=1;
        }
    }

    int c0=0, c1=0, c2=0, c3=0, pn=0, qn=0;
    for(int i=0; i<n; i++){
        if(rA[i]==-1 && rB[i]==-1)c0++;
        if(rA[i]==-1 && rB[i]!=-1 && !cA[rB[i]])c1++;
        if(rA[i]!=-1 && rB[i]==-1 && !cB[rA[i]])c2++;
        if(rA[i]==-1)pn++;
        if(rB[i]==-1)qn++;
        if(!cA[i] && !cB[i])c3++;
    }

    long long ans = 0;
    if(c0>c3)swap(c0, c3);
    for(int i=0; i<=c0; i++){
        for(int j=0; j<=c1; j++){
            for(int k=0; k<=c2; k++){
                if(pn-i<j || pn-i<k) continue;
                long long ways=1;
                ways = ways*nenk(c0, i)%mod;
                ways = ways*nenk(c1, j)%mod;
                ways = ways*nenk(c2, k)%mod;
                ways = ways*nenk(c3, i)%mod;
                ways = ways*f[   i  ]%mod;
                ways = ways*f[pn-i-j]%mod;
                ways = ways*f[qn-i-k]%mod;
                
                if((i+j+k)&1)ans=(ans-ways)%mod;
                else ans=(ans+ways)%mod;
            }
        }
    }
    if(ans<0)ans+=mod;
    cout<<ans;

    return 0;
}