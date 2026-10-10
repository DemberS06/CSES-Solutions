#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<int> a(n+1), p(n+1), vis(n+1, 0);
    map<int, vector<pair<int, int>>> mp;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        p[a[i]]=i;
    }

    for(int h=1; h<=n; h++){
        if(vis[h])continue;
        vector<int> v;
        for(int x=a[h]; !vis[x]; x=p[x]){
            vis[x]=1;
            v.push_back(x);
        }
        if(v.size()==1)continue;
        for(int i=(v.size()-1)/2, j=i+1; i>=0 && j<v.size(); i--, j++){
            mp[0].push_back({p[v[i]], p[v[j]]});
            swap(a[p[v[i]]], a[p[v[j]]]);
            swap(p[v[i]], p[v[j]]);
        }
        for(auto& u:v){
            if(u==p[u])continue;
            mp[1].push_back({p[p[u]], p[u]});
            swap(a[p[u]], a[p[p[u]]]);
            swap(p[u], p[p[u]]);
        }
    }

    cout<<mp.size()<<"\n";
    for(auto& [_, v]:mp){
        cout<<v.size()<<"\n";
        for(auto& [x, y]:v)cout<<x<<' '<<y<<"\n";
    }

    return 0;
}