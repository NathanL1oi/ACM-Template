set<pair<int,int>> E;
struct EBCC{
    int n;
    int cur,cnt;
    vector<int> dfn,low,bel;
    vector<int> stk;
    vector<vector<int>> adj;
    EBCC(){}
    EBCC(int _n){
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
        adj[v].push_back(u);
    }
    void dfs(int x,int fa){
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        for (auto v:adj[x]){
            if (v==fa) continue;
            if (dfn[v]==-1){
                E.emplace(x,v);
                dfs(v,x);
                low[x]=min(low[x],low[v]);
            }else if (bel[v]==-1&&dfn[v]<dfn[x]){
                E.emplace(x,v);
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
        dfs(0,-1);
        // for (int i=0;i<n;i++){
        //     if (dfn[i]==-1) dfs(i,-1);
        // }
        return bel;
    }
    struct Graph{
        int n;
        vector<pair<int,int>> edges;
        vector<int> siz,cnte;
    };
    Graph g;
    void initGraph(){
        g.n=cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
    }
    Graph compress(){
        initGraph();
        for (int i=0;i<n;i++){
            g.siz[bel[i]]++;
            for (auto j:adj[i]){
                if (bel[i]<bel[j]){
                    g.edges.emplace_back(bel[i],bel[j]);
                }else if (i<j){
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};