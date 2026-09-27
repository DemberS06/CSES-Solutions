#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
using namespace std;

const int N = 3000;
const int W = (N + 63) / 64;

static uint64_t b[N][W];

int main(){
    long long n, ans=0;
    scanf("%lld", &n);

    static char buf[N + 5];

    for(int i=0; i<n; i++){
        scanf("%s", buf);
        for(int j=0; j<n; j++){
            if(buf[j]=='1') b[i][j>>6] |= (1ULL<<(j&63));
        }
    }

    int w=(n+63)/64;

    for(int i=0, x; i<n; i++){
        for(int j=i+1; j<n; j++){
            x=0;
            for(int k=0; k<w; k++){
                x += __builtin_popcountll(b[i][k]&b[j][k]);
            }
            ans += (long long)x*(x-1)/2;
        }
    }

    printf("%lld\n", ans);
    return 0;
}