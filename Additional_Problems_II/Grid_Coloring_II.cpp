#include <bits/stdc++.h>

using namespace std;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k; cin>>n>>m; k=n*m;
    vector<vector<int>> adj(2*k), jda(2*k);
    vector<string> s(n);
    for(auto& u:s)cin>>u;

    function<int(int, int)> check = [&](int x, int y){
        if(x<0 || x>=n)return 0;
        if(y<0 || y>=m)return 0;
        return 1;
    };
    
    function<int(int)> T = [&](int x){
        if(x>0)return 2*x-1;
        else return -2*(x+1);
    };

    function<void(int, int)> push = [&](int x, int y){
        adj[T(x)].push_back(T(y));
        jda[T(y)].push_back(T(x));
        adj[T(-y)].push_back(T(-x));
        jda[T(-x)].push_back(T(-y));
    };

    for(int i=0; i<n; i++){
        for(int j=1; j<=m; j++){
            for(int h=0, x, y; h<4; h++){
                x=i+dx[h], y=j+dy[h];
                if(!check(x, y-1))continue;
                if(s[i][j-1]==s[x][y-1]){
                    if(h&1)push(i*m+j, -x*m-y);
                    else   push(-i*m-j, x*m+y);
                }
                if(s[i][j-1]=='A' && s[x][y-1]=='B')push(-i*m-j, -x*m-y);
                if(s[i][j-1]=='A' && s[x][y-1]=='C')push(i*m+j, x*m+y);
                if(s[i][j-1]=='B' && s[x][y-1]=='C')push(-i*m-j, -x*m-y);
            }
        }
    }
    
    vector<int> ans(2*k, 0), a(2*k, 0), st; int cnt=0;
    function<void(int, int, vector<int>&, vector<vector<int>>&)> kosaraju = [&](int x, int f, vector<int>& vis, vector<vector<int>>& adj){
        cnt+=f;
        vis[x]=cnt;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            kosaraju(u, f, vis, adj);
        }
        if(f)st.push_back(x);
    };
    for(int i=0; i<2*k; i++){
        if(!a[i])kosaraju(i, 1, a, adj);
    }cnt=0;
    while(!st.empty()){
        auto x=st.back();
        st.pop_back();
        if(!ans[x])cnt++, kosaraju(x, 0, ans, jda);
    }

    for(int i=0; i<n; i++){
        for(int j=1, x, y; j<=m; j++){
            x=2*(m*i+j)-1; y=x-1;
            if(ans[x]==ans[y]){
                cout<<"IMPOSSIBLE";
                return 0;
            }
            s[i][j-1]='A'+(s[i][j-1]-'A'+1+(ans[x]<ans[y]))%3;
        }
    }
    for(auto& u:s)cout<<u<<'\n';

    return 0;
}