#include <bits/stdc++.h>

using namespace std;

int main(){
    string s, x;
    cin>>x>>s;
    s+=" "+x; 
    
    int n=s.size(), m=n-x.size()-1, ans=0;
    vector<int> kmp(n+5, 0);

    for(int i=1, j; i<n; i++){
        j=kmp[i-1];
        while(j>0 && s[i]!=s[j])j=kmp[j-1];
        if(s[i]==s[j])j++;
        kmp[i]=j;
        if(kmp[i]==m)ans++;
    }

    cout<<ans;
    return 0;
}