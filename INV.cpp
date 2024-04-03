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