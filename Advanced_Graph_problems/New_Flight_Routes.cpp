#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0;
    cin>>n>>m;

    vector<int> st;
    vector<pair<int, int>> ans;

    function<void(int, int, vector<int>&, vector<vector<int>>&)> kosaraju = [&](int x, int f, vector<int>& vis, vector<vector<int>>& adj){
        k+=f;
        vis[x]=k;
        for(auto& u:adj[x]){
            if(vis[u])continue;
            kosaraju(u, f, vis, adj);
        }
        if(f)st.push_back(x);
    };
    
    vector<vector<int>> adj(n+1), jda(n+1), ady(n+1), yda(n+1);
    vector<int> col(n+1, 0), in(n+1, 0), out=in, id=in, ty=in;

    for(int i=0, x, y; i<m; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        jda[y].push_back(x);
    }
    
    for(int i=1; i<=n; i++){
        if(!col[i])kosaraju(i, 1, col, adj);
    }
 
    k=0; fill(col.begin(), col.end(), 0);
    
    while(!st.empty()){
        auto x=st.back();
        st.pop_back();
        if(!col[x])k++, kosaraju(x, 0, col, jda), id[k]=x;
    }
    
    if(k==1){
        cout<<"0";
        return 0;
    }
    
    for(int i=1; i<=n; i++){
        for(auto& u:adj[i]){
            if(col[u]==col[i])continue;
            in[col[u]]++;
            out[col[i]]++;
            ady[col[i]].push_back(col[u]);
        }
    }

    vector<int> p, q;
    int f, g;
    
    function<bool(int)> dfs = [&](int x){
        ty[x]=1;
        if(!out[x]){
            g=id[x]; q.push_back(id[x]);
            out[x]++;
            return 1;
        }
        for(auto& u:ady[x]){
            if(ty[u])continue;
            if(dfs(u))return 1;
        }
        return 0;
    };

    for(int i=1; i<=k; i++){
        if(!in[i]){
            if(!dfs(i))continue;
            f=id[i];
            in[i]++;
            p.push_back(id[i]);
        }
    }

    int t=p.size();
    for(int i=0; i<t; i++)ans.push_back({q[(i+1)%t], p[i]});

    p.clear(); q.clear();
    for(int i=1; i<=k; i++){
        if(!in[i])p.push_back(id[i]);
        if(!out[i])q.push_back(id[i]);
    }

    t=min(p.size(), q.size());
    for(int i=0; i<t; i++)ans.push_back({q[i], p[i]});
    for(int i=t; i<p.size(); i++)ans.push_back({g, p[i]});
    for(int i=t; i<q.size(); i++)ans.push_back({q[i], f});

    cout<<ans.size()<<"\n";
    for(auto& [x,y]:ans)cout<<x<<' '<<y<<"\n";

    return 0;
}