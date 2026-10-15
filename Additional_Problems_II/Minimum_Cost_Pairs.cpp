#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n; cin>>n;
    vector<long long> v(n), a(n+1, 1e15), L(n+1), R(n+1), ok(n+1, 1);
    for(auto& u:v)cin>>u;
    sort(v.begin(), v.end());

    set<pair<long long, int>> f;
    for(int i=1; i<n; i++){
        a[i]=v[i]-v[i-1];
        L[i]=i-1; R[i]=i+1;
        f.insert({a[i], i});
    }

    function<void(int)> push = [&](int x){
        int l=L[x], r=R[x];
        L[x]=L[l]; R[x]=R[r];
        L[R[x]]=R[L[x]]=x;
        a[x]=a[l]+a[r]-a[x];
        f.insert({a[x], x});
        ok[l]=ok[r]=0;
        if(r==n || l==0)ok[x]=0; 
    };

    long long ans=0;
    for(int i=1; 2*i<=n; i++){
        while(!f.empty()){
            auto [x, j]=*f.begin();
            f.erase(f.begin());
            if(!ok[j] || a[j]!=x)continue;
            ans+=x;
            push(j);
            break;
        }
        cout<<ans<<' ';
    }

    return 0;
}