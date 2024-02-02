#include <cstdio>
#include <vector>
#define MAXN 500005
using namespace std;
void dfs1(int x);
void dfs2(int x);
void add_edge(int u,int v);
inline void get(unsigned int x);
unsigned int s;
long long tk,tx,aans;
int n,q,root,cnt,ans,head[MAXN],nxt[MAXN],to[MAXN],dis[MAXN],dep[MAXN],fa[MAXN][21],ffa[MAXN],f1[MAXN],lson[MAXN],tmp;
vector<int> up[MAXN],down[MAXN];
int main(){
	scanf("%d%d%u",&n,&q,&s);
	f1[0]=-1;
	for (int i=1,u;i<=n;i++){
		scanf("%d",&u);
		add_edge(u,i);
		if (u==0) root=i;
		f1[i]=f1[i>>1]+1;
	}
	cnt=0;
	fa[root][0]=ffa[root]=root,dep[root]=dis[root]=1;
	dfs1(root);
	dfs2(root);
	for (int i=1,x,k;i<=q;i++){
		get(s);
		tx=((long long)s^(long long)ans)%(long long)n+1;
		get(s);
		tk=((long long)s^(long long)ans)%(long long)dis[tx];
		x=tx,k=tk;
		if (k==0){
			ans=x;
			aans^=(long long)i*(long long)ans;
			continue;
		}
		x=fa[x][f1[k]];
		k-=1<<f1[k];
		k-=dis[x]-dis[ffa[x]];
		x=ffa[x];
		if (k>=0) x=up[x][k];
		else x=down[x][-k];
		ans=x;
		aans^=(long long)i*(long long)ans;
	}
	printf("%lld",aans);
}
void dfs1(int x){
	for (int u=head[x],v;u;u=nxt[u]){
		v=to[u];
		dep[v]=dis[v]=dis[x]+1;
		fa[v][0]=x;
		for (int i=0;fa[v][i];i++) fa[v][i+1]=fa[fa[v][i]][i];
		dfs1(v);
		if (dep[v]>dep[x]) dep[x]=dep[v],lson[x]=v;
	}
}
void dfs2(int x){
	if (x==ffa[x]){
		tmp=dep[x]-dis[x];
		for (int i=0,v=x;i<=tmp;i++){
			up[x].push_back(v);
			v=fa[v][0];
		}
		for (int i=0,v=x;i<=tmp;i++){
			down[x].push_back(v);
			v=lson[v];
		}
	}
	if (lson[x]){
		ffa[lson[x]]=ffa[x];
		dfs2(lson[x]);
	}
	for (int u=head[x],v;u;u=nxt[u]){
		v=to[u];
		if (v==lson[x]) continue;
		ffa[v]=v;
		dfs2(v);
	}
}
void add_edge(int u,int v){
	cnt++;
	nxt[cnt]=head[u],to[cnt]=v;
	head[u]=cnt;
}
inline void get(unsigned int x){
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	s=x;
}
