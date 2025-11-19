// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, k;
    cin>>n>>k;

    vector<long long> res(k, 0), t(n+1, 0), L(n, 0), R(n, 0), U(n, 0), D(n, 0);
    vector<long long> e[n];
    string s[n];

    function<void(int, int)> solve = [&](int l, int r){
        for(auto& u:t)u=0;
        while(l>=0 && r>=0){
            if(l>0 && s[l-1][r]==s[l][r])U[r]++, D[r]--;
            else{
                U[r]=0; int x;
                for(x=0; l+x<n && s[l+x][r]==s[l][r]; x++); 
                D[r]=x;
            }
            if(r+1<n && s[l][r+1]==s[l][r])R[l]++, L[l]--;
            else{
                R[l]=0; int x;
                for(x=0; r-x>=0 && s[l][r-x]==s[l][r]; x++); 
                L[l]=x;
            }

            long long L1=min(L[l],U[r]+1), L2=min(D[r],R[l]+1), sum=0; 
            e[l-L1+1].push_back(l+1);

            for(int i=l+L2; i; i-=(i&-i))sum+=t[i];
            res[s[l][r]-'A']+=L2-sum;
            for(auto& idx:e[l]) for(int i=idx;i<=n;i+=i&-i)t[i]++; 
            e[l].clear();
    
            l--,r--;
        }
    };

	for(int i=0; i<n; i++)cin>>s[i];
	for(int i=0; i<n-1; i++)solve(i,n-1);
	for(int i=n-1; i>=0; i--)solve(n-1,i);
	for(auto& u:res)cout<<u<<'\n';
    return 0;
}