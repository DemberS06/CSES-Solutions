#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s, t="-#";
    cin>>s;
    for(auto& u:s)t+=u, t+="#"; t+="_";
    int m=t.size();

    function<int(int)> pos = [&](int x){
        while(t[x]<'a')x--;
        return x/2-1;
    };

    vector<int> p(m+1, 0), ans(s.size(), 1);
    for(int i=1, c=0, r=0, x, d; i<m-1; i++){
        if(r>i)p[i]=min(r-i, p[2*c-i]);
        while(t[i-p[i]-1]==t[i+p[i]+1])p[i]++, ans[pos(i+p[i])]=max(ans[pos(i+p[i])], p[i]);

        if(r<i+p[i])c=i, r=i+p[i];
    }

    for(auto& u:ans)cout<<u<<' ';

    return 0;
}