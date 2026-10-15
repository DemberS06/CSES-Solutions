#include <bits/stdc++.h>

using namespace std;

int dy[]={-1, 1, 0, 0};
int dx[]={0, 0, -1, 1};

int color(int y, int x){
    return (y+x)&1;
}

bool F3(int h, int w, pair<int, int> s, pair<int, int> t){
    for(int q=0; q<8; q++){
        int H=h, W=w;
        if(q&4)swap(H, W);
        if(H!=3 || W%2)continue;
        auto mp=[&](pair<int, int> c){
            int y=c.first, x=c.second;
            if(q&1)x=w+1-x;
            if(q&2)y=h+1-y;
            if(q&4)swap(y, x);
            return make_pair(y, x);
        };
        auto a=mp(s), b=mp(t);
        for(int r=0; r<2; r++){
            if(color(a.first, a.second)!=color(1, 1) && (a.second<b.second-1 || (a.first==2 && a.second<b.second)))return true;
            swap(a, b);
        }
    }
    return false;
}

bool solvable(int h, int w, pair<int, int> s, pair<int, int> t){
    if(s==t)return h*w==1;
    if(h*w%2==0){
        if(color(s.first, s.second)==color(t.first, t.second))return false;
    }
    else if(color(s.first, s.second) || color(t.first, t.second))return false;
    if(h==1 || w==1){
        int a=(h==1?s.second:s.first), b=(h==1?t.second:t.first);
        return min(a, b)==1 && max(a, b)==max(h, w);
    }
    if(h==2 && s.second==t.second && s.second>1 && s.second<w)return false;
    if(w==2 && s.first==t.first && s.first>1 && s.first<h)return false;
    return !F3(h, w, s, t);
}

int bh, bw;
pair<int, int> bt;
vector<vector<int>> vis;
vector<pair<int, int>> path;

bool ok(int y, int x){
    return y>=1 && y<=bh && x>=1 && x<=bw && !vis[y][x];
}

bool conn(int y0, int x0, int left){
    vector<vector<int>> seen(bh+2, vector<int> (bw+2, 0));
    vector<pair<int, int>> st;
    int cnt=0;
    for(int d=0; d<4; d++){
        int y=y0+dy[d], x=x0+dx[d];
        if(!ok(y, x))continue;
        seen[y][x]=1, st.push_back({y, x}), cnt=1;
        break;
    }
    while(!st.empty()){
        auto [y, x]=st.back(); st.pop_back();
        for(int d=0; d<4; d++){
            int yy=y+dy[d], xx=x+dx[d];
            if(!ok(yy, xx) || seen[yy][xx])continue;
            seen[yy][xx]=1, cnt++, st.push_back({yy, xx});
        }
    }
    return cnt==left;
}

bool dfs(int y, int x){
    if(make_pair(y, x)==bt)return (int)path.size()==bh*bw;
    if(!conn(y, x, bh*bw-(int)path.size()))return false;
    for(int d=0; d<4; d++){
        int yy=y+dy[d], xx=x+dx[d];
        if(!ok(yy, xx))continue;
        if(make_pair(yy, xx)==bt && (int)path.size()+1!=bh*bw)continue;
        vis[yy][xx]=1, path.push_back({yy, xx});
        if(dfs(yy, xx))return true;
        vis[yy][xx]=0, path.pop_back();
    }
    return false;
}

vector<pair<int, int>> base(int h, int w, pair<int, int> s, pair<int, int> t){
    bh=h, bw=w, bt=t;
    vis.assign(h+2, vector<int> (w+2, 0));
    path={s};
    vis[s.first][s.second]=1;
    dfs(s.first, s.second);
    return path;
}

vector<vector<pair<int, int>>> ladder(int L, pair<int, int> s){
    vector<vector<pair<int, int>>> res;
    auto corner=[&](vector<pair<int, int>> cur, int p, int c, int q, int dir){
        for(int r=p; ; r+=dir){
            vector<pair<int, int>> u=cur;
            for(int i=r; i!=q+dir; i+=dir)u.push_back({i, c});
            for(int i=q; i!=r-dir; i-=dir)u.push_back({i, 3-c});
            res.push_back(u);
            if(r==q)break;
            cur.push_back({r, c}), cur.push_back({r, 3-c}), c=3-c;
        }
    };
    int p=s.first, c=s.second;
    if(p==1)corner({}, 1, c, L, 1);
    if(p==L)corner({}, L, c, 1, -1);
    if(p>1 && p<L){
        for(int dir=-1; dir<=1; dir+=2){
            vector<pair<int, int>> pre;
            int e=(dir<0?1:L);
            for(int i=p; i!=e+dir; i+=dir)pre.push_back({i, c});
            for(int i=e; i!=p-dir; i-=dir)pre.push_back({i, 3-c});
            corner(pre, p-dir, 3-c, (dir<0?L:1), -dir);
        }
    }
    return res;
}

vector<pair<int, int>> build(int H, int W, pair<int, int> s, pair<int, int> t){
    if(H<=5 && W<=5)return base(H, W, s, t);
    for(int q=0; q<4; q++){
        int h=H, w=W;
        auto fw=[&](pair<int, int> c){
            int y=c.first, x=c.second;
            if(q==0)return make_pair(y, x);
            if(q==1)return make_pair(y, W+1-x);
            if(q==2)return make_pair(x, y);
            return make_pair(x, H+1-y);
        };
        auto bk=[&](pair<int, int> c){
            int y=c.first, x=c.second;
            if(q==0)return make_pair(y, x);
            if(q==1)return make_pair(y, W+1-x);
            if(q==2)return make_pair(x, y);
            return make_pair(H+1-x, y);
        };
        auto sh=[&](pair<int, int> c){
            return make_pair(c.first, c.second-2);
        };
        if(q>=2)swap(h, w);
        if(w<6)continue;
        auto a=fw(s), b=fw(t);
        bool ia=a.second<=2, ib=b.second<=2;
        if(ia && ib)continue;

        if(!ia && !ib){
            if(h<2 || (h==2 && a.second==3 && b.second==3))continue;
            if(!solvable(h, w-2, sh(a), sh(b)))continue;
            auto r=build(h, w-2, sh(a), sh(b));
            for(auto& u:r)u.second+=2;
            for(int i=0; i+1<(int)r.size(); i++){
                auto u=r[i], v=r[i+1];
                if(u.second!=3 || v.second!=3)continue;
                vector<pair<int, int>> res(r.begin(), r.begin()+i+1);
                if(v.first==u.first+1){
                    for(int y=u.first; y>=1; y--)res.push_back({y, 2});
                    for(int y=1; y<=h; y++)res.push_back({y, 1});
                    for(int y=h; y>=v.first; y--)res.push_back({y, 2});
                }
                else{
                    for(int y=u.first; y<=h; y++)res.push_back({y, 2});
                    for(int y=h; y>=1; y--)res.push_back({y, 1});
                    for(int y=1; y<=v.first; y++)res.push_back({y, 2});
                }
                res.insert(res.end(), r.begin()+i+1, r.end());
                for(auto& u:res)u=bk(u);
                return res;
            }
            continue;
        }

        bool rev=false;
        if(ib)swap(a, b), rev=true;
        for(auto& u:ladder(h, a)){
            auto e=u.back();
            if(e.second!=2)continue;
            pair<int, int> ns={e.first, 3};
            if(!solvable(h, w-2, sh(ns), sh(b)))continue;
            auto r=build(h, w-2, sh(ns), sh(b));
            vector<pair<int, int>> res=u;
            for(auto c:r)c.second+=2, res.push_back(c);
            for(auto& c:res)c=bk(c);
            if(rev)reverse(res.begin(), res.end());
            return res;
        }
    }
    return vector<pair<int, int>>();
}

void solve(){
    int n, m, y1, x1, y2, x2;
    cin>>n>>m>>y1>>x1>>y2>>x2;
    pair<int, int> s={y1, x1}, e={y2, x2};

    if(!solvable(n, m, s, e)){
        cout<<"NO\n";
        return;
    }

    auto p=build(n, m, s, e);
    string ans;
    for(int i=0; i+1<(int)p.size(); i++){
        int a=p[i+1].first-p[i].first, b=p[i+1].second-p[i].second;
        ans+=(a==-1?'U':a==1?'D':b==-1?'L':'R');
    }
    cout<<"YES\n"<<ans<<"\n";
}

int main(){
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--)solve();
    return t+1;
}
