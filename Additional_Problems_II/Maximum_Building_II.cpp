#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m; cin>>n>>m;
    vector<vector<long long>> a(n+1, vector<long long> (m+1, 0));
    vector<int> v(m, 0);

    function<void()> Advertsiment = [&]{
        vector<int> st, l(m, 0), r(m, m-1), p(m);
        for(int i=0; i<m; i++){
            while(!st.empty() && v[st.back()]>v[i])r[st.back()]=i-1, st.pop_back();
            if(!st.empty()){
                if(v[st.back()]==v[i])l[i]=l[st.back()];
                else l[i]=st.back()+1;
            }
            st.push_back(i);
            p[i]=i;
        }
        sort(p.begin(), p.end(), [&](int& x, int& y){
            return v[y]<v[x];
        });
        
        set<pair<int, int>> f; f.insert({m, m});
        
        int q=-1;
        for(auto& i:p){
            if(q!=-1 && l[i]==l[q] && r[i]==r[q]){
                q=i;
                continue;
            }q=i;
            while(true){
                auto [x, y]=*f.lower_bound({l[i], 0});
                if(x>r[i])break;
                a[v[i]][y-x+1]--;
                f.erase({x, y});
            }
            f.insert({l[i], r[i]});
            a[v[i]][r[i]-l[i]+1]++;
        }
    };

    string s;
    for(int i=0; i<n; i++){
        cin>>s;
        for(int j=0; j<m; j++){
            if(s[j]=='*')v[j]=0;
            else v[j]++;
        }
        Advertsiment();
    }

    vector<vector<long long>> ans(n, vector<long long> (m, 0));
    vector<long long> dp(m+1, 0);

    long long sum, f;
    for(int i=n; i>0; i--){
        sum=f=0;
        for(long long j=m; j>0; j--){
            f+=a[i][j];
            sum+=j*a[i][j];
            dp[j]+=sum-f*j+f;
            ans[i-1][j-1]=dp[j];
        }
    }
    
    for(auto& u:ans){
        for(auto& w:u)cout<<w<<' ';
        cout<<"\n";
    }

    return 0;
}