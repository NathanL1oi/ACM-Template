struct segtree{
    int n;
    vector<int> v,lz;
    const vector<int> &a;
    segtree(int n_,const vector<int> &a_):a(a_){
        n=n_;
        v.assign(n<<2,0);
        lz.assign(n<<2,0);
        build(1,1,n);
    }
    void build(int x,int l,int r){
        if (l==r){
            v[x]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        pushup(x);
    }
    void pushup(int x){
        v[x]=v[x<<1]+v[x<<1|1];
    }
    void pushdown(int x){
        v[x<<1]+=lz[x],v[x<<1|1]+=lz[x];
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
        if (ql>=l&&qr<=r){
            v[x]+=c;
            lz[x]+=c;
            return ;
        }
        int mid=(l+r)>>1;
        pushdown(x);
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
        pushdown(x);
        int res1=0,res2=0;
        if (ql<=mid) res1=query(x<<1,l,mid,ql,qr);
        if (qr>mid) res2=query(x<<1|1,mid+1,r,ql,qr);
        return res1+res2;
    }
};