#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;

    vector<long long> v(n), l(n, 0), r(n, n-1);
    vector<int> st;

    for(auto& u:v)cin>>u;

    for(int i=0; i<n; i++){
        while(!st.empty() && v[st.back()]>v[i])r[st.back()]=i-1, st.pop_back();
        if(!st.empty())l[i]=st.back()+1;
        st.push_back(i);
    }

    long long ans=0;

    for(int i=0; i<n; i++){
        ans=max(ans, v[i]*(r[i]-l[i]+1));
    }

    cout<<ans;

    return 0;
}