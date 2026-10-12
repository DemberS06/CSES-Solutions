#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    string s;
    cin>>n>>s; n=2*n-2;
    function<bool()> check = [&](){
        string r;
        for(auto& u:s){
            if(u=='.')continue;
            r+=u;
        }
        string t=r;
        sort(t.begin(), t.end());
        return r==t;
    };

    auto search = [&](string t, int p, int x, int l, int r){
        for(int i=p; i<=r && i>=l; i+=x){
            if(s[i]==t[0] && s[i+1]==t[1])return i;
        }
        return -1;
    };

    vector<string> ans;

    function<void(int, int)> swp = [&](int p, int q){
        swap(s[p], s[q]);
        swap(s[p+1], s[q+1]);
        ans.push_back(s);
    };

    while(ans.size()<1000 && !check()){
        int p=search("..", 0, +1, 0, n), q;
        q=search("AA", n, -1, p, n); if(q!=-1){swp(q, p); continue;}
        q=search("BB", 0, +1, 0, p); if(q!=-1){swp(q, p); continue;}
        q=search("AB", p, +1, p, n); if(q!=-1){swp(q, p); continue;}
        q=search("BA", p, -1, 0, p); if(q!=-1){swp(q, p); continue;}
        q=search("BA", p, +1, p, n); if(q!=-1){swp(q, p); continue;}
        q=search("AB", p, -1, 0, p); if(q!=-1){swp(q, p); continue;}
        break;
    }

    if(!check()){
        cout<<"-1\n";
        return 0;
    }

    cout<<ans.size()<<"\n";
    for(auto& u:ans)cout<<u<<'\n';

    return 0;
}