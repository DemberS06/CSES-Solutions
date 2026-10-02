#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s, t="^#";
    cin>>s;
    for(auto c:s)t+=c, t+="#"; t+="$";

    int n=s.size(), m=t.size();
    
    vector<int> p(m+1, 0);
    
    for(int i=1, c=0, r=0; i<m-1; i++){
        if(i<r)p[i]=min(r-i, p[2*c-i]);
        
        while(t[i+p[i]+1]==t[i-p[i]-1])p[i]++;
        if(i+p[i]>r)r=i+p[i], c=i;
    }
    
    int x=2;
    for(int i=3; i<m; i++)if(p[x]<p[i])x=i;
    for(int i=-p[x]+1; i<p[x]; i+=2)cout<<t[x+i];
    
    return 0;
}