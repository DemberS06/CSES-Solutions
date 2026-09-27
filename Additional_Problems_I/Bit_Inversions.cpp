#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    
    string s;
    cin>>s; int n=s.size(), tam=1, m;
    
    set<int> L, R; multiset<long long> f;

    L.insert(-1); R.insert(n); f.insert(0); L.insert(0); R.insert(n+1);
    for(int i=1; i<n; i++){
        if(s[i]!=s[i-1])R.insert(i), L.insert(-i-1), f.insert(tam), tam=1;
        else tam++;
    }f.insert(tam);

    cin>>m; 

    for(int e; m--;){
        cin>>e;
        auto l=-*L.lower_bound(-e);
        auto r=*R.lower_bound(e);
        L.erase(-e);
        R.erase(e);
        
        
        if(l==r){
            auto p=-*L.lower_bound(1-e); p=max(1, p);
            auto q=*R.lower_bound(e+1); q=min(n, q);
            f.erase(f.find(1));
            f.insert(q-p+1);
            if(e!=1)R.erase(e-1), f.erase(f.find(e-p));
            else L.insert(-1);
            if(e!=n)L.erase(-1-e), f.erase(f.find(q-e));
            else R.insert(n);
        }
        else if(l==e){
            auto p=-*L.lower_bound(1-e); p=max(1, p);
            auto q=*R.lower_bound(e+1); q=min(n, q);
            f.erase(f.find(q-e+1));
            f.insert(e-p+1);
            f.insert(q-e);
            if(e!=1)R.erase(e-1), f.erase(f.find(e-p));
            else L.insert(-1);
            R.insert(e);
            L.insert(-1-e);
        }
        else if(r==e){
            auto p=-*L.lower_bound(1-e); p=max(1, p);
            auto q=*R.lower_bound(e+1); q=min(n, q);

            //cout<<l<<' '<<r<<' '<<p<<' '<<q<<"<-\n";
            f.erase(f.find(e-p+1));
            
            f.insert(e-p);
            f.insert(q-e+1);
            if(e!=n)L.erase(-1-e), f.erase(f.find(q-e));
            else R.insert(n);
            R.insert(e-1);
            L.insert(-e);
        }
        else{
            f.erase(f.find(r-l+1));
            f.insert(e-l);
            f.insert(r-e);
            f.insert(1);
            L.insert(-e-1);
            L.insert(-e);
            R.insert(e);
            R.insert(e-1);
        }

        //for(auto& u:L)cout<<u<<' ';cout<<"\n";
        //for(auto& u:R)cout<<u<<' ';cout<<"\n";
        //for(auto& u:f)cout<<u<<' ';cout<<"\n";
        
        cout<<*f.rbegin()<<" ";
    }

    return 0;
}