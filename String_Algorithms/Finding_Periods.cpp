#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s;
    cin>>s; int n=s.size();
    vector<int> kmp(n, 0);

    for(int i=1, j=0; i<n; i++){
        while(j>0 && s[i]!=s[j])j=kmp[j-1];
        if(s[i]==s[j])j++;
        kmp[i]=j;
    }

    int x=n-kmp.back();
    set<int> f; f.insert(n);

    for(int i=x; i<n; i+=x)f.insert(i);
    for(int i=kmp[n-1]; i>0; i=kmp[i-1])f.insert(n-i);

    for(auto& u:f)cout<<u<<' ';

    return 0;
}