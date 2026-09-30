#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, m;
    cin>>n>>m;
    
    string s;
    vector<vector<long long>> a(n+1, vector<long long> (m, 0));

    long long ans=0;

    function<long long(vector<long long>&)> mxarea = [&](vector<long long>& v){
        long long res=0;
        vector<long long> L(m, 0), R(m, m-1), st; st.reserve(m);
        for(int i=0; i<m; i++){
            while(!st.empty() && v[i]<=v[st.back()])R[st.back()]=i-1, st.pop_back();
            if(!st.empty())L[i]=st.back()+1;
            st.push_back(i);
        }

        for(int i=0; i<m; i++)res=max(res, v[i]*(R[i]-L[i]+1));

        return res;
    };
    
    for(int i=1; i<=n; i++){
        cin>>s;
        for(int j=0; j<m; j++){
            if(s[j]=='.')a[i][j]=a[i-1][j]+1;
            else a[i][j]=0;
        }
        ans=max(ans, mxarea(a[i]));
    }

    cout<<ans;

    return 0;
}