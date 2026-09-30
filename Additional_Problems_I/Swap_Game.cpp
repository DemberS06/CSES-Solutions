#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    vector<int> f(10); f[0]=1; 
    for(int i=1; i<10; i++)f[i]=i*f[i-1];
    vector<vector<int>> adj(f[9]+1);
    vector<int> l={0,1,3,4,6,7,0,1,2,3,4,5};
    vector<int> r={1,2,4,5,7,8,3,4,5,6,7,8};

    function<int(vector<int>&)> val = [&](vector<int>& p){
        vector<int> v(10, 1); v[0]=0;
        int res=1;
        for(int i=0, x; i<9; i++){
            x=0; 
            v[p[i]]=0;
            for(int j=1; j<p[i]; j++)x+=v[j];
            res+=x*f[8-i];
        }
        return res;
    };

    vector<int> b={1,2,3,4,5,6,7,8,9}, dis(f[9]+1, 0);
    for(int i=1, x; i<=f[9]; i++, next_permutation(b.begin(), b.end())){
        for(int h=0; h<12; h++){
            x=i;
            for(int j=l[h]+1; j<r[h]; j++){
                if(b[j]<b[r[h]])x+=f[8-l[h]];
                else x-=f[8-j];
                if(b[j]>b[l[h]])x+=f[8-j];
                else x-=f[8-l[h]];
            }
            if(b[l[h]]<b[r[h]])x+=f[8-l[h]];
            else x-=f[8-l[h]];
            for(int j=r[h]+1; j<9; j++){
                if(b[j]<b[r[h]])x+=f[8-l[h]]-f[8-r[h]];
                if(b[j]<b[l[h]])x+=f[8-r[h]]-f[8-l[h]];
            }
            adj[i].push_back(x);
        }
    }

    queue<int> q; q.push(1); dis[1]=1;

    while(!q.empty()){
        auto x=q.front(); q.pop();
        for(auto& u:adj[x]){
            if(dis[u])continue;
            dis[u]=dis[x]+1;
            q.push(u);
        }
    }

    vector<int> a(9);
    for(auto& u:a)cin>>u;

    cout<<dis[val(a)]-1;

    return 0;
}