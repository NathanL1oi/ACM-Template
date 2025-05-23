## 杂项

### 代码模板
```cpp {.line-numbers}
#include <bits/stdc++.h>
using namespace std;
using i64=long long;
using i128=__int128;
const double eps=1e-9;
void solve();
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
}
void solve(){
}
```

### int128
```cpp {.line-numbers}
using i128=__int128;
istream &operator>>(istream &is,i128 &n){
    string s;
    is>>s;
    n=0;
    for (int i=0,len=s.size();i<len;i++){
        n=n*10+s[i]-'0';
    }
    return is;
}
ostream &operator<<(ostream &os,i128 n){
    string s;
    while(n){
        s+='0'+n%10;
        n/=10;
    }
    std::reverse(s.begin(),s.end());
    if (s.size()==0) s="0";
    return os<<s;
}
```
<div STYLE="page-break-after: always;"></div>

## 数据结构

### 树状数组
```cpp {.line-numbers}
template <typename T>
struct Fenwick{
    int n;
    std::vector<T> v;
    Fenwick(int n_=0){
        init(n_+1);
    }
    void init(int n_){
        n=n_;
        v.assign(n,T{});
    }
    void add(int x,const T &c){
        for (;x<=n;x+=x&(-x)) v[x]+=c;
    }
    T query(int x){
        T res{};
        for (;x;x-=x&(-x)) res+=v[x];
        return res;
    }
    T rangeSum(int l,int r){
        return query(r)-query(l-1);
    }
    int kth (const T &k){
        int x=0;
        T cur{};
        for (int i=1<<__lg(n);i;i>>=1){
            if (x+i<=n&&cur+v[x+i]<=k){
                x+=i;
                cur+=v[x];
            }
        }
        return x;
    }
};
```

### 线段树
```cpp {.line-numbers}
struct segtree{
    const int INF=0x3f3f3f3f;
    int n;
    vector<int> v,lz,mx,mi;
    const vector<int> &a;
    segtree(int n_,const vector<int> &a_):a(a_){
        n=n_;
        v.assign(n<<2,0);
        mx.assign(n<<2,0);
        mi.assign(n<<2,INF);
        lz.assign(n<<2,0);
        build(1,1,n);
    }
    void build(int x,int l,int r){
        if (l==r){
            v[x]=a[l];
            mx[x]=mi[x]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void pushup(int x){
        v[x]=v[x<<1]+v[x<<1|1];
        mx[x]=max(mx[x<<1],mx[x<<1|1]);
        mi[x]=min(mi[x<<1],mi[x<<1|1]);
    }
    void pushdown(int x,int l,int r){
        int mid=(l+r)>>1;
        v[x<<1]+=lz[x]*(mid-l+1),v[x<<1|1]+=lz[x]*(r-mid);
        mx[x<<1]+=lz[x],mx[x<<1|1]+=lz[x];
        mi[x<<1]+=lz[x],mi[x<<1|1]+=lz[x];
        lz[x<<1]+=lz[x],lz[x<<1|1]+=lz[x];
        lz[x]=0;
    }
    void add(int x,int c){
        add(1,1,n,x,x,c);
    }
    void add(int ql,int qr,int c){
        add(1,1,n,ql,qr,c);
    }
    void add(int x,int l,int r,int ql,int qr,int c){
        if (l>=ql&&r<=qr){
            v[x]+=(r-l+1)*c;
            mx[x]+=c;
            mi[x]+=c;
            lz[x]+=c;
            return ;
        }
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        if (ql<=mid) add(x<<1,l,mid,ql,qr,c);
        if (qr>mid) add(x<<1|1,mid+1,r,ql,qr,c);
        pushup(x);
    }
    int query(int l,int r){
        return query(1,1,n,l,r);
    }
    int query(int x,int l,int r,int ql,int qr){
        if (l>=ql&&r<=qr) return v[x];
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        int res1=0,res2=0;
        if (ql<=mid) res1=query(x<<1,l,mid,ql,qr);
        if (qr>mid) res2=query(x<<1|1,mid+1,r,ql,qr);
        return res1+res2;
    }
    int querymx(int l,int r){
        return querymx(1,1,n,l,r);
    }
    int querymx(int x,int l,int r,int ql,int qr){
        if (l>=ql&&r<=qr) return mx[x];
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        int res1=-INF,res2=-INF;
        if (ql<=mid) res1=querymx(x<<1,l,mid,ql,qr);
        if (qr>mid) res2=querymx(x<<1|1,mid+1,r,ql,qr);
        return max(res1,res2);
    }
    int querymi(int l,int r){
        return querymi(1,1,n,l,r);
    }
    int querymi(int x,int l,int r,int ql,int qr){
        if (l>=ql&&r<=qr) return mi[x];
        int mid=(l+r)>>1;
        pushdown(x,l,r);
        int res1=INF,res2=INF;
        if (ql<=mid) res1=querymi(x<<1,l,mid,ql,qr);
        if (qr>mid) res2=querymi(x<<1|1,mid+1,r,ql,qr);
        return min(res1,res2);
    }
};
```

### 主席树
```cpp {.line-numbers}
struct PST{
    const int INF=0x3f3f3f3f;
    vector<int> root,v,lson,rson,lz;
    const vector<int> &a;
    int n;
    int cnt=0;
    PST(int n_,const vector<int> &a_):a(a_){
        n=n_;
        root.assign(n+5,0);
        lson.assign(n<<5,0);
        rson.assign(n<<5,0);
        v.assign(n<<5,0);
        lz.assign(n<<5,0);
        build(root[0],1,n);
    }
    void build(int &x,int l,int r){
        x=++cnt;
        if (l==r){
            v[x]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        build(lson[x],l,mid);
        build(rson[x],mid+1,r);
        pushup(x);
    }
    void pushup(int x){
        v[x]=v[lson[x]]+v[rson[x]];
    }
    void pushdown(int x,int l,int r){
        int ls=lson[x],rs=rson[x];
        int mid=(l+r)>>1;
        if (ls) v[ls]+=(mid-l+1)*lz[x];
        if (rs) v[rs]+=(r-mid)*lz[x];
        lz[x]=0;
    }
    void add(int oldrt,int rt,int qx,int c){
        add(root[oldrt],root[rt],1,n,qx,qx,c);
    }
    void add(int oldrt,int rt,int ql,int qr,int c){
        add(root[oldrt],root[rt],1,n,ql,qr,c);
    }
    void add(int oldx,int &x,int l,int r,int ql,int qr,int c){
        x=++cnt;
        v[x]=v[oldx];
        lz[x]=lz[oldx];
        lson[x]=lson[oldx],rson[x]=rson[oldx];
        if (l>=ql&&r<=qr){
            v[x]+=c*(r-l+1);
            lz[x]+=c;
            return ;
        }
        pushdown(oldx,l,r);
        lz[x]=0;
        int mid=(l+r)>>1;
        if (ql<=mid) add(lson[oldx],lson[x],l,mid,ql,qr,c);
        if (qr>mid) add(rson[oldx],rson[x],mid+1,r,ql,qr,c);
        pushup(x);
    }
    int query(pair<int,int> qp,int qx){
        auto [lx,rx]=qp;
        int res1=query(root[rx],1,n,qx,qx);
        int res2=query(root[lx-1],1,n,qx,qx);
        return res1-res2;
    }
    int query(pair<int,int> qp,int ql,int qr){
        auto [lx,rx]=qp;
        int res1=query(root[rx],1,n,ql,qr);
        int res2=query(root[lx-1],1,n,ql,qr);
        return res1-res2;
    }
    int query(int x,int qx){
        return query(root[x],1,n,qx,qx);
    }
    int query(int x,int ql,int qr){
        return query(root[x],1,n,ql,qr);
    }
    int query(int x,int l,int r,int ql,int qr){
        if (l>=ql&&r<=qr){
            return v[x];
        }
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        int res1=0,res2=0;
        if (ql<=mid) res1=query(lson[x],l,mid,ql,qr);
        if (qr>mid) res2=query(rson[x],mid+1,r,ql,qr);
        return res1+res2;
    }
};
```

### 并查集
```cpp {.line-numbers}
struct DSU{
    vector<int> fa,sz;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        fa.resize(n+5);
        iota(fa.begin(),fa.end(),0);
        sz.assign(n+5,1);
    }
    int find(int x){
        while(x!=fa[x]){
            x=fa[x]=fa[fa[x]];
        }
        return x;
    }
    bool same(int a,int b){
        return find(a)==find(b);
    }
    void merge(int a,int b){
        a=find(a),b=find(b);
        if (a==b) return ;
        if (sz[a]<sz[b]) swap(a,b);
        sz[a]+=sz[b];
        fa[b]=a;
    }
    int size(int x){
        return sz[find(x)];
    }
};
```
<div STYLE="page-break-after: always;"></div>

## 图论

### 割点
```cpp {.line-numbers}
struct SCC{
    int n;
    int cur,cnt;
    vector<int> dfn,low,bel;
    vector<int> stk;
    vector<vector<int>> adj;
    SCC(){}
    SCC(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        adj.assign(n,{});
        dfn.assign(n,-1);
        low.resize(n);
        bel.assign(n,-1);
        stk.clear();
        cur=cnt=0;
    }
    void addedge(int u,int v){
        adj[u].push_back(v);
    }
    void dfs(int x){
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for (auto v:adj[x]){
            if (dfn[v]==-1){
                dfs(v);
                low[x]=min(low[x],low[v]);
            }else if (bel[v]==-1){
                low[x]=min(low[x],dfn[v]);
            }
        }
        if (dfn[x]==low[x]){
            int v;
            do{
                v=stk.back();
                bel[v]=cnt;
                stk.pop_back();
            }while(v!=x);
            cnt++;
        }
    }
    vector<int> work(){
        for (int i=0;i<n;i++){
            if (dfn[i]==-1) dfs(i);
        }
        return bel;
    }
    struct Graph{
        int n;
        vector<pair<int,int>> edges;
        vector<int> siz,cnte;
    };
    Graph g;
    void initGraph(){
        g.n=cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
    }
    Graph compress(){
        initGraph();
        for (int i=0;i<n;i++){
            g.siz[bel[i]]++;
            for (auto j:adj[i]){
                if (bel[i]<bel[j]){
                    g.edges.emplace_back(bel[i],bel[j]);
                }else if (i<j){
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};
```

### 割边
```cpp {.line-numbers}
set<pair<int,int>> E;
struct EBCC{
    int n;
    int cur,cnt;
    vector<int> dfn,low,bel;
    vector<int> stk;
    vector<vector<int>> adj;
    EBCC(){}
    EBCC(int _n){
        n=_n;
        adj.assign(n,{});
        dfn.assign(n,-1);
        low.resize(n);
        bel.assign(n,-1);
        stk.clear();
        cur=cnt=0;
    }
    void addedge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x,int fa){
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for (auto v:adj[x]){
            if (v==fa) continue;
            if (dfn[v]==-1){
                E.emplace(x,v);
                dfs(v,x);
                low[x]=min(low[x],low[v]);
            }else if (bel[v]==-1&&dfn[v]<dfn[x]){
                E.emplace(x,v);
                low[x]=min(low[x],dfn[v]);
            }
        }
        if (dfn[x]==low[x]){
            int v;
            do{
                v=stk.back();
                bel[v]=cnt;
                stk.pop_back();
            }while(v!=x);
            cnt++;
        }
    }
    vector<int> work(){
        dfs(0,-1);
        // for (int i=0;i<n;i++){
        //     if (dfn[i]==-1) dfs(i,-1);
        // }
        return bel;
    }
    struct Graph{
        int n;
        vector<pair<int,int>> edges;
        vector<int> siz,cnte;
    };
    Graph g;
    void initGraph(){
        g.n=cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
    }
    Graph compress(){
        initGraph();
        for (int i=0;i<n;i++){
            g.siz[bel[i]]++;
            for (auto j:adj[i]){
                if (bel[i]<bel[j]){
                    g.edges.emplace_back(bel[i],bel[j]);
                }else if (i<j){
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};
```

### 2-SAT
```cpp {.line-numbers}
struct SCC{
    int n;
    int cur,cnt;
    vector<int> dfn,low,bel;
    vector<int> stk;
    vector<vector<int>> adj;
    SCC(){}
    SCC(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        adj.assign(n,{});
        dfn.assign(n,-1);
        low.resize(n);
        bel.assign(n,-1);
        stk.clear();
        cur=cnt=0;
    }
    void addedge(int u,int v){
        adj[u].push_back(v);
    }
    void dfs(int x){
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for (auto v:adj[x]){
            if (dfn[v]==-1){
                dfs(v);
                low[x]=min(low[x],low[v]);
            }else if (bel[v]==-1){
                low[x]=min(low[x],dfn[v]);
            }
        }
        if (dfn[x]==low[x]){
            int v;
            do{
                v=stk.back();
                bel[v]=cnt;
                stk.pop_back();
            }while(v!=x);
            cnt++;
        }
    }
    vector<int> work(){
        for (int i=0;i<n;i++){
            if (dfn[i]==-1) dfs(i);
        }
        return bel;
    }
};
struct TwoSAT{
    int n;
    vector<bool> ans;
    SCC scc;
    TwoSAT(){};
    TwoSAT(int _n):n(_n),ans(_n),scc(SCC(_n<<1)){}
    void addClause(int u,bool f,int v,bool g){
        scc.addedge((u<<1)+!f,(v<<1)+g);
        scc.addedge((v<<1)+!g,(u<<1)+f);
    }
    bool SAT(){
        vector<int> id=scc.work();
        for (int i=0;i<n;i++){
            if (id[i<<1]==id[i<<1|1]) return 0;
            ans[i]=id[i<<1]>id[i<<1|1];
        }
        return 1;
    }
    vector<bool> answer(){return ans;}
};
```
<div STYLE="page-break-after: always;"></div>

## 数学

### 逆元
```cpp {.line-numbers}
struct INV{
    i64 n=0,p=1e9+7;
    vector<i64> inv;
    INV(){}
    INV(i64 _n,i64 _p){
        n=_n;
        p=_p;
        inv.assign(n+1,0);
        init();
    }
    void init(){
        inv[1]=1;
        for (int i=2;i<=n;i++){
            inv[i]=(p-p/i)*inv[p%i]%p;
        }
    }
    i64 operator[](int x){
        return inv[x];
    }
    i64 get(int x){
        if (x==1) return 1;
        return (p-p/x)*get(p%x)%p;
    }
};
```

### 质数筛
```cpp {.line-numbers}
struct sieve{
    vector<int> minp,primes;
    sieve(int n){
        minp.assign(n+1,0);
        for (int i=2;i<=n;i++){
            if (minp[i]==0){
                minp[i]=i;
                primes.push_back(i);
            }
            for (auto p:primes){
                if (i*p>n) break;
                minp[i*p]=p;
                if (p==minp[i]) break;
            }
        }
    }
    bool isprime(int x){
        return minp[x]==x;
    }
    int size(){
        return primes.size();
    }
    vector<int>& getprimes(){
        return primes;
    }
};
```

### 递归逆元
```cpp {.line-numbers}
long long inv(long long x){
	if (x==1) return 1;
	return (m-m/x)*inv(m%x)%m;
}
//m is mod number
```

### 矩阵
```cpp {.line-numbers}
const int mod=1e9+7;
struct Matrix{
    int n,m;
    vector<vector<int>> v;
    Matrix(int _n,int _m){
        n=_n,m=_m;
        v.assign(n,vector<int>(m,0));
    }
    Matrix(const vector<vector<int>> &a){
        n=a.size();
        m=a[0].size();
        v.resize(n);
        for (int i=0;i<n;i++) v[i]=a[i];
    }
    void init(){
        for (int i=0;i<n;i++) v[i][i]=1;
    }
    void display(){
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++) cout<<v[i][j]<<" \n"[j==m-1];
        }
    }
    void expow(int k){
        Matrix res(n,n);
        res.init();
        while(k){
            if (k&1) res=res*(*this);
            *this=(*this)*(*this);
            k>>=1;
        }
        *this=res;
    }
    Matrix friend operator*(const Matrix &a,const Matrix &b){
        int nn=a.n,mm=b.m;
        Matrix res(nn,mm);
        for (int i=0;i<nn;i++){
            for (int j=0;j<mm;j++){
                for (int k=0;k<nn;k++){
                    res.v[i][j]=(res.v[i][j]+a.v[i][k]*b.v[k][j])%mod;
                }
            }
        }
        return res;
    }
};
```

### Mint&Mlong(带模整数)
```cpp {.line-numbers}
using i64=long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 998244353;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1000000007;
using Z = MInt<P>;

```

### 组合数
```cpp {.line-numbers}
struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        m = std::min(m, Z::getMod() - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
};
```
<div STYLE="page-break-after: always;"></div>