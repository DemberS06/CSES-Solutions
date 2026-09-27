#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n;
    cin>>n;
    
    vector<int> v(n-2), a(n+1, 0);
    set<int> f;

    for(int i=1; i<=n; i++)f.insert(i);
    for(auto& u:v){
        cin>>u;
        a[u]++;
        f.erase(u);
    }

    for(auto& u:v){
        auto x=*f.begin();
        f.erase(f.begin());
        cout<<u<<' '<<x<<"\n";
        a[u]--;
        if(!a[u])f.insert(u);
    }

    for(auto& u:f)cout<<u<<' ';

    return 0;
}