#include<bits/stdc++.h>

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
    long long query(int l, int r){
        return query(r)-query(l-1);
    }
};

struct SuffixArray{
    int n, k=0;
    vector<vector<int>> b;
    vector<int> a;
    string s;
    SuffixArray(string _s):s(_s){
        s+=' '; n=s.size();
        while((1<<k)<=n)k++; k++;
        b.resize(n, vector<int> (k+1, 0));
        a.resize(n);
        for(int i=0; i<n; i++)a[i]=i;
        sort(a.begin(), a.end(), [&](int& x, int& y){
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
            st.push_back(i);
            cnt[b[i][h]+1]++;
        }
        for(auto& u:a){
            if(u<(1<<h))continue;
            st.push_back(u-(1<<h));
            cnt[b[u-(1<<h)][h]+1]++;
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

    string ans(long long t){
        string res;
        
        vector<pair<int, int>> st;
        Fenwick S(n+1), F(n+1);
        vector<long long> p(n, 0);
        for(int i=1; i<n; i++)p[i]=p[i-1]+n-a[i]-1;
        st.push_back({n, 0});
        
        function<long long(int, int)> val = [&](int i, int h){
            long long L=p[i-1];
            long long R=F.query(h+1, n); R*=h; R+=S.query(h);
            return L+R+h;
        };
        
        function<void(int, int)> push = [&](int i, int h){
            while(!st.empty() && st.back().second>h){
                auto [j, q]=st.back(); st.pop_back();
                long long d=st.back().first-j;
                F.update(q, -d);
                S.update(q, -d*q);
            }
            long long d=st.back().first-i;
            if(h)F.update(h, d);
            if(h)S.update(h, d*h);
            st.push_back({i, h});
        };

        int j, ok;
        
        for(int i=n-1; i>0; i--){
            int l=1, r=n-a[i]-1, mt;
            long long dm;
            
            while(l<=r){
                mt=(l+r)/2;
                dm=val(i, mt);
                if(dm>=t)r=mt-1, ok=mt, j=a[i];
                else l=mt+1;
            }
            push(i, lcp(a[i], a[i-1]));
        }

        for(int i=0; i<ok; i++)res+=s[i+j];

        return res;
    }
};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s; long long k;
    cin>>s>>k;
    SuffixArray S(s);
    cout<<S.ans(k);
    return 0;
}