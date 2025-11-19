// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int n, m, k=0;
    cin>>n>>m;
    while((1<<k)<2*n)k++;

    vector<vector<int>> boss(n+1, vector<int> (k, -1));

    for(int i=2; i<=n; i++)cin>>boss[i][0];
    
    for(int h=1; h<k; h++){
        for(int i=1; i<=n; i++){
            if(boss[i][h-1]==-1)continue;
            boss[i][h]=boss[boss[i][h-1]][h-1];
        }
    }

    while(m--){
        int ans, x;
        cin>>ans>>x;
        for(int h=k-1; h>=0 && ans>0; h--){
            if((x>>h)&1)ans=boss[ans][h];
        }
        cout<<ans<<"\n";
    }

    return m+1;
}