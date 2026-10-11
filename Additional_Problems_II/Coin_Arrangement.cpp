#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    long long n, x=0, y=0, ans=0;
    cin>>n;
    vector<int> a(n), b(n);
    for(auto& u:a)cin>>u;
    for(auto& u:b)cin>>u;

    for(int i=0; i<n; i++){
        x+=a[i]-1;
        y+=b[i]-1;
        if(x<0 && y>0){
            long long d=min(-x, y);
            ans+=d;
            x+=d;
            y-=d;
        }
        if(x>0 && y<0){
            long long d=min(-y, x);
            ans+=d;
            y+=d;
            x-=d;
        }
        
        ans+=abs(y)+abs(x);
    }

    cout<<ans;

    return 0;
}