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