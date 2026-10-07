#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

    int n, x=0, val=1e9;
    cin>>n;

    function<int(int, int)> get = [&](int x, int y){
        if(__gcd(x, y)!=1)return val;
        int res=0;
        if(x<y)swap(x, y);
        while(y){
            res+=x/y;
            x%=y;
            swap(x, y);
        }
        
        return res-1;
    };

    for(int i=1, y; i<=n+1; i++){
        y=get(i, n+2-i);
        if(y<val)val=y, x=i;
    }

    function<string(int x, int y)> ans = [&](int x, int y){
        string res;
        while(x!=1 || y!=1){
            if(x>y)x-=y, res+='0';
            else y-=x, res+='1';
        }

        return res;
    };

    cout<<ans(x, n+2-x);

    return 0;
}