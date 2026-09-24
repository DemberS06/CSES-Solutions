#include <bits/stdc++.h>

using namespace std;

const long long md=1e9+7;

struct Trie{
    int n;
    vector<unordered_map<char, int>> adj;
    vector<long long> a;

    Trie(int _n){
        n=_n+1;
        adj.reserve(n); a.reserve(n);
        adj.resize(1);
        a.resize(1, 0);
    }

    long long push(char& c, int x){
        if(!adj[x].count(c)){
            adj[x][c]=a.size(); 
            a.push_back(0);
            unordered_map<char, int> z;
            adj.push_back(z);
        }
        return adj[x][c];
    }

    void push(string& s){
        int x=0;
        for(auto& u:s)x=push(u, x);
        a[x]++;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    string s; int m, n;
    cin>>s>>m; n=s.size();

    Trie T(2e5);

    for(string x; m--;){
        cin>>x;
        reverse(x.begin(), x.end());
        T.push(x);
    }

    vector<long long> dp(n+1, 0); dp[0]=1;

    for(int i=1; i<=n; i++){
        for(int j=i, p=0; j>0; j--){
            if(!T.adj[p].count(s[j-1]))break;
            p=T.push(s[j-1], p);
            dp[i]=(dp[i]+dp[j-1]*T.a[p])%md;
        }
    }

    cout<<dp[n];
}