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