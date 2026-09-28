#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s, t, ans;
    cin>>s; t=s; int n=s.size();

    vector<vector<pair<char, int>>> adj(150);
    map<char, int> b;
    sort(t.begin(), t.end());

    for(int i=s.size()-1; i>=0; i--){
        adj[s[i]].push_back({t[i], b[t[i]]});
        b[t[i]]++;
    }

    char c='#'; int p=0;
    do{
        auto [d, q]=adj[c][p];
        ans+=d;
        c=d, p=q;
    }
    while(c!='#');
    ans.pop_back();
    cout<<ans;

    return 0;
}