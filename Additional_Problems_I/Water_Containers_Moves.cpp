#include <bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int a, b, x;
    cin>>a>>b>>x;
    if(x>a || x%__gcd(a, b)){
        cout<<"-1\n";
        return 0;;
    }
    long long ans=0, bns=0;
    vector<string> m, o;

    auto solveaa = [&](){
        int p=0, q=0;
        if(a==x)ans+=x, m.push_back("FILL A\n"), p=x;
        
        while(p%b!=x%b){
            m.push_back("FILL A\n"); ans+=a-p; p=a;
            while(p>=b && p%b!=x%b){
                m.push_back("MOVE A B\n"); p-=b-q; ans+=b-q, q=b; 
                if(p%b!=x%b)m.push_back("EMPTY B\n"), ans+=q, q=0;
            }
            if(p%b!=x%b){
                m.push_back("MOVE A B\n"); ans+=p;
                q=p;p=0;
            }
        }
        while(p>x){
            if(q)m.push_back("EMPTY B\n"), ans+=q, q=0;
            m.push_back("MOVE A B\n"); p-=b; ans+=b; q+=b;
        }
        while(p<x){
            m.push_back("FILL B\n"); ans+=b-q; q=b;
            m.push_back("MOVE B A\n"); ans+=q; p+=q; q=0;
        }
    };

    auto solveab = [&](){
        int p=0, q=0;
        
        while(p!=x){
            if(!q)o.push_back("FILL B\n"), bns+=b, q=b;
            
            if(p==a)o.push_back("EMPTY A\n"), bns+=p, p=0;
            o.push_back("MOVE B A\n");
            if(q<a-p)p+=q, bns+=q, q=0;
            else bns+=a-p, q-=a-p, p=a; 
        }
    };

    auto solvebb = [&](){
        int p=0, q=0;
        if(a==x)ans+=x, m.push_back("FILL A\n"), p=x;
        
        while(p!=x){
            if(!q)m.push_back("FILL B\n"), ans+=b, q=b;
            
            if(p==a)m.push_back("EMPTY A\n"), ans+=p, p=0;
            m.push_back("MOVE B A\n");
            if(q<a-p)p+=q, ans+=q, q=0;
            else ans+=a-p, q-=a-p, p=a; 
        }
    };

    auto solveba = [&](){
        int p=0, q=0;
        
        while(p!=x){
            if(!p)o.push_back("FILL A\n"), bns+=a, p=a;
            
            if(q==b)o.push_back("EMPTY B\n"), bns+=q, q=0;
            o.push_back("MOVE A B\n");
            if(p<b-q)q+=p, bns+=p, p=0;
            else bns+=b-q, p-=b-q, q=b; 
        }
    };

    if(a>=b)solveaa(), solveab();
    else solveba(), solvebb();

    if(ans>bns)swap(ans, bns), swap(m, o);

    cout<<m.size()<<' '<<ans<<"\n";
    for(auto& u:m)cout<<u;
    
    return 0;
}