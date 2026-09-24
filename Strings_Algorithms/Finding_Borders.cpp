#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s;
    cin>>s; int n=s.size();
    vector<int> kmp(n, 0), ans;

    for(int i=1, j; i<n; i++){
        j=kmp[i-1];
        while(j>0 && s[i]!=s[j])j=kmp[j-1];
        if(s[i]==s[j])j++;
        kmp[i]=j;
    }

    for(n--; kmp[n]; n--){
        n=kmp[n];
        ans.push_back(n);
    }

    reverse(ans.begin(), ans.end());

    for(auto& u:ans)cout<<u<<' ';
    
    return 0;
}