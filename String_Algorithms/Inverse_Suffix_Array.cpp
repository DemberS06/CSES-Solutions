#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> p(n+2, 0), a(n+1);
    string s; char c='a'; s.resize(n, c);
    for(int i=1; i<=n; i++){
        cin>>a[i];
        p[a[i]]=i;
    }

    for(int i=2; i<=n; i++){
        if(p[a[i]+1]<p[a[i-1]+1])c++;
        s[a[i]-1]=c;
        if(c>'z'){
            cout<<"-1";
            return 0;
        }
    }

    cout<<s;

    return 0;
}