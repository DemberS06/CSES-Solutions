// hola soy Dember :D
#include<bits/stdc++.h>

using namespace std;

int main(){
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	int n, k;
	cin>>n>>k;
    
    if(k==1){
        cout<<(long long)n*(n+1)*(2*n+1)/6;
        return 0;
    }
    
    vector<vector<int>> g(n+1, vector<int>(n+1, 0));
    vector<vector<bool>> ok(n+1, vector<bool>(n+1, 0));
    long long ans=0;
	int mx=(1<<k)-1;
    string s;

    for(int i=1; i<=n; i++){
		cin>>s;
		for(int j=1; j<=n; j++)g[i][j]=(1<<(s[j-1]-'A'));
	}

	for(int j=0; (1<<j)<=n; j++){
		for(int x=1; x<=n-(1<<j);x++) for(int y=1; y<=n-(1<<j); y++) if(!ok[x][y]){
			int m=min((1<<j), n-max(x, y)-(1<<j)+1);
			if((g[x][y]|g[x+m][y]|g[x][y+m]|g[x+m][y+m])==mx){
				ok[x][y]=true;
				int a=0, k=n-max(x, y)+1;
				for(int i=j-1; i+1; i--){
					a|=(1<<i);
					if(k<=(1<<j)+a || (g[x][y]|g[x+a][y]|g[x][y+a]|g[x+a][y+a])==mx)a-=(1<<i);
				}
				ans+=k-(1<<j)-a;
			}
			if(m<(1<<j))ok[x][y]=true;
		}
		for(int x=1; x<=n-(1<<(j+1))+1; x++) for(int y=1;y<=n-(1<<(j+1))+1; y++)g[x][y]|=g[x+(1<<j)][y]|g[x][y+(1<<j)]|g[x+(1<<j)][y+(1<<j)];
	}
	
    cout<<ans;

    return 0;
}