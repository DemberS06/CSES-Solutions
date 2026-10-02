#include <bits/stdc++.h>

using namespace std;

vector<int> kmp(string& s){
    int n=s.size();
    vector<int> pi(n, 0);
    for(int i=1, j=0; i<n; i++){
        while(j>0 && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])j++;
        pi[i]=j;
    }

    return pi;
}

vector<int> fz(string& s){
    int n=s.size();
    vector<int> z(n, 0);

    for(int i=1, l=0, r=0; i<n; i++){
        if(i<r)z[i]=min(r-i, z[i-l]);
        while(i+z[i]<n && s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i, r=i+z[i];
    }
    return z;
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s;
    cin>>s;

    for(auto& u:fz(s))cout<<u<<' ';cout<<"\n";
    for(auto& u:kmp(s))cout<<u<<' ';cout<<"\n";

    return 0;
}