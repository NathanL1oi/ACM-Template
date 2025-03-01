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