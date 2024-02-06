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