template <typename T>
struct Fenwick{
    int n;
    std::vector<T> v;
    Fenwick(int n_=0){
        init(n_);
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
};