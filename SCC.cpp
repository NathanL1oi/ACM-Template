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