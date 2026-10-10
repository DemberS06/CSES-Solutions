#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n; cin>>n;
    vector<int> a(n*(n-1)/2), ans;
    
    for(auto& u:a)cin>>u;
    sort(a.begin(), a.end());

    function<int(int)> sim = [&](int val){
        multiset<int> f;
        ans.clear(); ans.push_back(val);
        for(auto& u:a)f.insert(u);

        while(!f.empty()){
            auto x=*f.begin()-val;
            if(x<=0)return 0;
            for(auto &u:ans){
                if(!f.count(x+u))return 0;
                f.erase(f.find(x+u));
            }
            ans.push_back(x);
        }

        return 1;
    };
    
    for(int i=2; i<a.size(); i++){
        if(!sim((a[1]+a[0]-a[i])/2))continue;
        for(auto& u:ans)cout<<u<<' ';
        break;
    }

    return 0;
}