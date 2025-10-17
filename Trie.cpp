struct Trie{
    int lg=1;
    vector<array<int,2>> trie;
    vector<int> f,s;
    int tot=1;
    Trie(int n){
        lg=31;
        trie.resize(n*lg+1);
        f.assign(n*lg+1,0);
        s.assign(n*lg+1,0);
    };
    int newnode(){
        tot++;
        return tot;
    }
    void add(int x,int c=1){
        int p=1;
        s[p]+=c;
        for (int i=lg-1;i>=0;i--){
            int d=x>>i&1;
            if (!trie[p][d]) trie[p][d]=newnode();
            p=trie[p][d];
            s[p]+=c;
        }
        f[p]+=c;
    };
    void del(int x,int c=1){
        int p=1;
        s[p]-=c;
        for (int i=lg-1;i>=0;i--){
            int d=x>>i&1;
            p=trie[p][d];
            s[p]-=c;
        }
        f[p]-=c;
    };
    int query(int x){
        int res=0;
        int p=1;
        for (int i=lg-1;i>=0;i--){
            int d=x>>i&1;
            if (!s[trie[p][d]]) d=d^1;
            // if (!s[trie[p][d]]) return 0;
            p=trie[p][d];
            res+=d<<i;
        }
        return res;
    }
};