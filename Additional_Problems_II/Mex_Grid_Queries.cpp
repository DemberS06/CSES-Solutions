#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    function<int(int, int)> solve = [&](int x, int y){
        if(x==y)return 0;
        int k=1;
        while(k<x || k<y)k*=2;
        k/=2;
        int p=x, q=y;
        if(p>k)p-=k;
        if(q>k)q-=k;
        if(p!=x && q!=y)return solve(p, q);
        return k+solve(p, q);
    };
    
    int x, y;
    cin>>x>>y;
    //cout<<(x-1)^(y-1);
    cout<<solve(x, y);

    return 0;
}