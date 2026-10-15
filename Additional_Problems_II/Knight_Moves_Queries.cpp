// a=max(x,y)-1, b=min(x,y)-1, m=max((a+1)/2, (a+b+2)/3)
// d(x,y) = (a,b)==(1,0) ? 3 : (a,b)==(1,1)||(a,b)==(2,2) ? 4 : m+((m+a+b)&1)
#include <bits/stdc++.h>

using namespace std;

const long long N=3000;
long long d[N][N];
int dx[]={1,1,-1,-1,2,2,-2,-2};
int dy[]={2,-2,2,-2,1,-1,1,-1};

void solve(){
    int x, y;
    cin>>x>>y;x--,y--;
    long long res=0;

    if(x<N && y<N){
        cout<<d[x][y]-1<<"\n";
        return;
    }

    if(x>y)swap(x, y);
    {
        int z=min(x-200, y-x);
        if(z>0)x-=z, y-=2*z, res+=z;
    }
    if(x<=200){
        int z=y/4-200;
        z*=4;
        if(z>0)y-=z, res+=z/2;
    }
    else{
        int z=x/3-200;
        if(z>0)y-=3*z, x-=3*z, res+=2*z;
    }
    cout<<res+d[x][y]-1<<"\n";
}

bool check(int x, int y){
    if(x<0 || x>=N)return 1;
    if(y<0 || y>=N)return 1;
    if(d[x][y])return 1;
    return 0;
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    queue<pair<int, int>> q; d[0][0]=1; q.push({0, 0});

    while(!q.empty()){
        auto [x, y]=q.front(); q.pop();
        for(int h=0; h<8; h++){
            if(check(x+dx[h], y+dy[h]))continue;
            q.push({x+dx[h], y+dy[h]});
            d[x+dx[h]][y+dy[h]]=d[x][y]+1;
        }
    }

    int t; cin>>t;
    while(t--)solve();

    return t+1;
}