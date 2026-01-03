## 杂项

### 代码模板
![template](../template.cpp)

### int128
![int128](../int128.cpp)

<div STYLE="page-break-after: always;"></div>

## 数据结构

### 树状数组
![Fenwick](../Fenwick.cpp)

### 线段树
![SegmentTree](../SegmentTree.cpp)

- 动态开点(+dynamic)
```cpp
struct segtree{
    int n;
    int cnt=0,root=0;
    vector<int> v,lson,rson,lz;
    segtree (int _n,int _q){
        n=_n;
        int lg=__lg(n)+1;
        lg=lg<<1;
        v.assign(_q*lg,0);
        lson.assign(_q*lg,0);
        rson.assign(_q*lg,0);
        lz.assign(_q*lg,0);
    }
    void pushup(int &x){
        v[x]=v[lson[x]]+v[rson[x]];
    }
    void pushdown(int &x,int l,int r){
        int &ls=lson[x];
        int &rs=rson[x];
        int mid=(l+r)>>1;
        if (!ls) ls=++cnt;
        if (!rs) rs=++cnt;
        v[ls]+=(mid-l+1)*lz[x],v[rs]+=(r-mid)*lz[x];
        lz[ls]+=lz[x],lz[rs]+=lz[x];
        lz[x]=0;
    }
    void add(int x,int c){
        add(root,1,n,x,x,c);
    }
    void add(int l,int r,int c){
        add(root,1,n,l,r,c);
    }
    void add(int &x,int l,int r,int ql,int qr,int c){
        if (!x) x=++cnt;
        if (l>=ql&&r<=qr){
            v[x]+=(r-l+1)*c;
            lz[x]+=c;
            return ;
        }
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        if (ql<=mid) add(lson[x],l,mid,ql,qr,c);
        if (qr>mid) add(rson[x],mid+1,r,ql,qr,c);
        pushup(x);
    }
    int query(int x){
        return query(root,1,n,x,x);
    }
    int query(int l,int r){
        return query(root,1,n,l,r);
    }
    int query(int &x,int l,int r,int ql,int qr){
        if (l>=ql&&r<=qr) return v[x];
        pushdown(x,l,r);
        int mid=(l+r)>>1;
        int res=0;
        if (ql<=mid) res+=query(lson[x],l,mid,ql,qr);
        if (qr>mid) res+=query(rson[x],mid+1,r,ql,qr);
        return res;
    }
};
```

- 主席树
```cpp
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
![DSU](../DSU.cpp)

### Trie
- 01Trie
![01Trie](../Trie.cpp)

<div STYLE="page-break-after: always;"></div>

## 图论

### 割点
![SCC](../SCC.cpp)

### 割边
![EBCC](../EBCC.cpp)

### 2-SAT
![2-SAT](../2-SAT.cpp)

<div STYLE="page-break-after: always;"></div>

## 数学

### 逆元
![INV](../INV.cpp)

### 质数筛
![sieve](../sieve.cpp)

### 递归逆元
```cpp
long long inv(long long x){
	if (x==1) return 1;
	return (m-m/x)*inv(m%x)%m;
}
//m is mod number
```

### 矩阵
![Matrix](../Matrix.cpp)

### Mint&Mlong(动态带模整数)
![MINT](../MInt&MLong.cpp)

### 组合数(+MINT使用)
```cpp
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

### 扩展欧几里得(exgcd)
![exgcd](../exgcd.cpp)
