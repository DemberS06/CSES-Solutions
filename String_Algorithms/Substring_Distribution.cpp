#include <bits/stdc++.h>

using namespace std;

struct Fenwick{
    int n;
    vector<long long> fwk;
    Fenwick(int _n):n(_n), fwk(n+1, 0){}
    void update(int p, long long delta){
        for(; p<=n; p+=-p&p)fwk[p]+=delta;
    } 
    long long query(int p){
        long long res=0;
        for(; p>0; p-=-p&p)res+=fwk[p];
        return res;
    }
};
struct SuffixArray{
    int n, k=0;
    string s;
    vector<int> a;
    vector<vector<int>> b;
    Fenwick F;
    SuffixArray(string _s):s(_s), F(s.size()+5){
        s+=' '; n=s.size();
        while((1<<k)<=n)k++; 
        b.resize(n, vector<int> (k+1, 0));
        a.resize(n);
        for(int i=0; i<n; i++)a[i]=i;
        sort(a.begin(), a.end(), [&](int& x, int &y){
            return s[x]<s[y];
        });
        
        for(int i=1; i<n; i++){
            b[a[i]][0]=b[a[i-1]][0];
            if(s[a[i]]!=s[a[i-1]])b[a[i]][0]++;
        }

        for(int h=0; h<k; h++){
            a=csort(h);
            for(int i=1; i<n; i++){
                b[a[i]][h+1]=b[a[i-1]][h+1];
                if(check(a[i], a[i-1], h))b[a[i]][h+1]++;
            }
        }
    }

    bool check(int x, int y, int h){
        if(b[x][h]!=b[y][h])return 1;
        return b[x+(1<<h)][h]!=b[y+(1<<h)][h];
    }

    vector<int> csort(int h){
        vector<int> cnt(n+1, 0), res(n), st;
        for(int i=max(0, n-(1<<h)); i<n; i++){
            cnt[b[i][h]+1]++;
            st.push_back(i);
        }
        for(auto& u:a){
            if(u<(1<<h))continue;
            cnt[b[u-(1<<h)][h]+1]++;
            st.push_back(u-(1<<h));
        }
        for(int i=1; i<n; i++)cnt[i]+=cnt[i-1];
        for(auto& u:st){
            res[cnt[b[u][h]]]=u;
            cnt[b[u][h]]++;
        }   
        return res;
    }
    
    int lcp(int x, int y){
        if(x>y)swap(x, y);
        int d=0;
        for(int h=k; h>=0; h--){
            if(y>=n || b[x][h]!=b[y][h])continue;
            d+=(1<<h);
            x+=(1<<h);
            y+=(1<<h);
        }
        return d;
    }

    vector<int> ans(){
        for(int i=1, x; i<n; i++){
            x=lcp(a[i], a[i-1]);
            F.update(x+1, 1);
            F.update(n-a[i],-1);
        }
        
        vector<int> res;
        for(int i=1; i<n; i++)res.push_back(F.query(i));
        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s; cin>>s;
    SuffixArray S(s);
    for(auto& u:S.ans())cout<<u<<' ';
    return 0;
}