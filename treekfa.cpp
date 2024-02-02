#include <cstdio>
#define MAXN 500005
using namespace std;
void dfs1(int x);
void dfs2(int x);
void add_edge(int u,int v);
inline void get(unsigned int x);
unsigned int s;
long long tk,tx,aans;
int n,q,root,cnt,ans,head[MAXN],nxt[MAXN],to[MAXN],dis[MAXN],siz[MAXN],num[MAXN],numr[MAXN],fa[MAXN],ffa[MAXN],hvson[MAXN];
bool p[MAXN],vis[MAXN];
int main(){
	scanf("%d%d%u",&n,&q,&s);
	for (int i=1,u;i<=n;i++){
		scanf("%d",&u);
		add_edge(u,i);
		if (u==0) root=i;
	}
	cnt=0;
	fa[root]=ffa[root]=root,dis[root]=1;
	dfs1(root);
	dfs2(root);
	for (int i=1,x,k;i<=q;i++){
		get(s);
		tx=((long long)s^(long long)ans)%(long long)n+1;
		get(s);
		tk=((long long)s^(long long)ans)%(long long)dis[tx];
		x=tx,k=tk;
		while(dis[x]-dis[ffa[x]]<k){
			k-=dis[x]-dis[ffa[x]]+1;
			x=fa[ffa[x]];
		}
		x=numr[num[x]-k];
		ans=x;
		aans^=(long long)i*(long long)ans;
	}
	printf("%lld",aans);
}
void dfs1(int x){
	p[x]=1;
	siz[x]=1;
	for (int u=head[x],v;u;u=nxt[u]){
		v=to[u];
		if (p[v]) continue;
		dis[v]=dis[x]+1;
		fa[v]=x;
		dfs1(v);
		siz[x]+=siz[v];
		if (siz[v]>siz[hvson[x]]) hvson[x]=v;
	}
}
void dfs2(int x){
	vis[x]=1;
	cnt++;
	num[x]=cnt;
	numr[cnt]=x;
	if (hvson[x]){
		ffa[hvson[x]]=ffa[x];
		dfs2(hvson[x]);
	}
	for (int u=head[x],v;u;u=nxt[u]){
		v=to[u];
		if (vis[v]) continue;
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
