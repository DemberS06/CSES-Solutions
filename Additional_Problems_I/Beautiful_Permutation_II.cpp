#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<int> ans, a, b;
    for(int i=n; i>0; i--){
        if(i&1)a.push_back(i);
        else b.push_back(i);
    }

    while(ans.size()+10<n){
        if(a.empty() || (!ans.empty() && abs(ans.back()-a.back())<=1)){
            ans.push_back(b.back());
            b.pop_back();
            continue;
        }
        if(b.empty() || (!ans.empty() && abs(ans.back()-b.back())<=1)){
            ans.push_back(a.back());
            a.pop_back();
            continue;
        }
        if(a.back()<b.back()){
            ans.push_back(a.back());
            a.pop_back();
            continue;
        }
        ans.push_back(b.back());
            b.pop_back();
    }

    for(auto& u:b)a.push_back(u);
    sort(a.begin(), a.end());
    int m=a.size();
    vector<int> vis(m, 0);

    function<int(int)> BT = [&](int x){
        ans.push_back(a[x]);
        if(ans.size()==n)return 1;
        vis[x]=1;
        for(int i=0; i<m; i++){
            if(vis[i])continue;
            if(abs(a[i]-a[x])<=1)continue;
            if(BT(i))return 1;
        }
        vis[x]=0;
        ans.pop_back();
        return 0;
    };
    
    for(int i=0; i<m; i++){
        if(!ans.empty() && abs(ans.back()-a[i])<=1)continue;
        if(!BT(i))continue;
        for(auto& u:ans)cout<<u<<' ';
        return 0;
    }

    cout<<"NO SOLUTION";

    return 0;
}