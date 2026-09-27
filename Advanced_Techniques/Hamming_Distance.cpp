#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio();

    int n, k;
    cin>>n>>k;

    vector<int> a(n);
    string s;
    for(auto& u:a){
        cin>>s;
        for(auto &x:s)u=2*u+(x=='1');
    }

    sort(a.begin(), a.end());

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            k=min(k, __popcount(a[i]^a[j]));
        }
    }

    cout<<k;

    return 0;
}