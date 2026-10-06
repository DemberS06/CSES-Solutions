#include <bits/stdc++.h>

using namespace std;

struct SuffixArray{
    int n, k;
    string s;
    vector<int> a;
    vector<vector<int>> b;
    SuffixArray(string _s):s(_s){
        s+='#'; n=s.size(), k=1;
        while((1<<k)<=n)k++;k++;
        a.resize(n);
        b.resize(n, vector<int> (k, 0));
        for(int i=0; i<n; i++)a[i]=i;
        sort(a.begin(), a.end(), [&](int& x, int& y){
            return s[x]<s[y];
        });
        for(int i=1; i<n; i++){
            b[a[i]][0]=b[a[i-1]][0];
            if(s[a[i]]!=s[a[i-1]])b[a[i]][0]++;
        }
        for(int h=0; h<k-1; h++){
            vector<int> c = csort(h);
            swap(a, c);
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
        vector<int> cnt(n+1, 0), st, res(n);

        for(int i=max(0, n-(1<<h)); i<n; i++){
            st.push_back(i); cnt[1+b[i][h]]++;
        }
        for(auto& u:a){
            if(u<(1<<h))continue;
            cnt[1+b[u-(1<<h)][h]]++;
            st.push_back(u-(1<<h));
        }
        for(int i=1; i<n; i++)cnt[i]+=cnt[i-1];
        for(auto& u:st){
            res[cnt[b[u][h]]]=u;
            cnt[b[u][h]]++;
        }
        return res;
    }

    long long lcp(int x, int y){
        if(x>y)swap(x, y);
        long long d=0;
        for(int h=k-1; h>=0; h--){
            if(y+(1<<h)>=n || b[x][h]!=b[y][h])continue;
            d+=(1<<h);
            x+=(1<<h);
            y+=(1<<h);
        }
        return d;
    }

    long long ans(){
        long long res=n;
        res=res*(n-1)/2;
        for(int i=1; i<n; i++){
            res-=lcp(a[i], a[i-1]);
        }
        return res;
    }

};

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    string s;
    cin>>s;

    SuffixArray S(s);
    //cout<<"HOLAAAA";return 0;
    cout<<S.ans();

    return 0;
}