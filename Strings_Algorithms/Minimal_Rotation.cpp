#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    string s;
    cin>>s; s+=s;
    int n=s.size(), p=0;
    vector<int> kmp(n, 0);

    for(int i=1, j=0, k; i<n; i++){
        if(s[i]<s[p]){
            p=i, j=0;
            continue;
        }
        while(j>0 && s[i]!=s[p+j]){
            if(s[i]<s[p+j])p=i-j;
            j=kmp[j-1];
        }
        if(j!=0){
            k=kmp[j-1];
            while(k>0 && s[i]!=s[p+k])k=kmp[k-1];
            if(k>=0 && s[i]==s[p+k])k++;
            kmp[j]=k;
        }
        if(s[i]==s[p+j])j++;
    }

    p%=n/2;

    for(int i=0; i<n/2; i++)cout<<s[p+i];

    return 0;
}