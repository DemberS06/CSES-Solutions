// hola soy Dember :D
#include<bits/stdc++.h>
 
using namespace std;
 
int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
 
    int n, k, ans=0;
    cin>>n>>k;
 
    vector<vector<int>> v(n, vector<int> (2));
    multiset<int> f;
 
    for(auto &u:v)cin>>u[0]>>u[1];
    sort(v.begin(), v.end());
 
    for(int i=0; i<k; i++)f.insert(1);
    
    for(auto u:v){
        auto x=*f.begin(), y=*f.rbegin();
        if(x<=u[0]){
            f.erase(f.find(x));
            f.insert(u[1]);
            ans++;
        }
        else if(y>u[1]){
            f.erase(f.find(y));
            f.insert(u[1]);
        }
    }
 
    cout<<ans;
 
    return 0;
}