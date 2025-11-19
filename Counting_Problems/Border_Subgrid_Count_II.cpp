//hola soy Dember :D
#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;
using ll = long long;

int main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    int n, k;
    cin>>n>>k;

    vector<string> g(n);
    for(auto& s:g)cin>>s;;

    int W=(n+63)>>6;
    unsigned long long lastMask=(n%64)?((1ull<<(n%64))-1ull):~0ull;

    vector<long long> ans(k, 0);

    for(int C=0; C<'A'+k; C++){
        vector<vector<unsigned long long>> rowBits(n, vector<unsigned long long>(W, 0ull));
        for(int r=0; r<n; r++){
            unsigned long long cur=0;
            int bi=0, wi=0;
            for(int c=0; c<n; c++){
                if(g[r][c]==C)cur|=(1ull<<bi);
                bi++;
                if(bi==64)rowBits[r][wi++]=cur, cur=0, bi=0;
            }
            if(bi)rowBits[r][wi]=cur;
        }

        vector<unsigned long long> side(W), good(W);
        for(int r1=0; r1<n; r1++){
            for(int w=0; w<W; w++)side[w]=rowBits[r1][w];

            for(int r2=r1; r2<n; r2++){
                if(r2>r1)for(int w=0; w<W; w++)side[w]&=rowBits[r2][w];
                
                for(int w=0; w<W; w++)good[w]=rowBits[r1][w]&rowBits[r2][w];
                long long runSide=0;
                bool prevEndsOne=false; 
                for(int w=0; w<W; w++){
                    unsigned long long gword=good[w], sword=side[w];
                    if(w==W-1)gword&=lastMask, sword&=lastMask;

                    if(gword==0ull){
                        if(runSide>0){
                            ans[C-'A']+=(runSide*(runSide+1))/2;
                            runSide=0;
                        }
                        prevEndsOne=false;
                        continue;
                    }

                    unsigned long long fullMask=(w==W-1)?lastMask:~0ull;
                    if(gword==fullMask){
                        bool isContinuation=prevEndsOne;
                        if(!isContinuation){
                            if(runSide>0){
                                ans[C-'A']+=(runSide*(runSide+1))/2;
                                runSide=0;
                            }
                        }
                        runSide+=__builtin_popcountll(sword);
                        prevEndsOne=true;
                        continue;
                    }

                    unsigned long long mask=gword;
                    while(mask){
                        int l=__builtin_ctzll(mask);
                        unsigned long long shifted=(mask>>l), notShifted=~shifted;
                        int runLen;
                        if(notShifted==0ull)runLen=64-l;
                        else runLen=__builtin_ctzll(notShifted);
                        bool isContinuation=(prevEndsOne && l==0);
                        if(!isContinuation){
                            if(runSide>0){
                                ans[C-'A']+=(runSide*(runSide+1))/2;
                                runSide=0;
                            }
                        }
                        unsigned long long subMask=(runLen==64)?~0ull:((1ull<<runLen)-1ull), sideBlock=(sword>>l)&subMask;
                        runSide+=__builtin_popcountll(sideBlock);
                        mask&=~(subMask<<l);
                    }
                    int lastBitIdx;
                    if(w==W-1)lastBitIdx=(n-1)&63;
                    else lastBitIdx=63;
                    prevEndsOne=((gword>>lastBitIdx)&1ull);
                }

                if(runSide>0){
                    ans[C-'A']+=(runSide*(runSide+1))/2;
                    runSide=0;
                }
            }
        }
    }

    for(auto& u:ans)cout<<u<<'\n';
    
    return 0;
}
