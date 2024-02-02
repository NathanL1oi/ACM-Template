#include <cstdio>
#define MAXN 100005
using namespace std;
void add_edge(int u,int v);
void dfs1(int x);
void dfs2(int x);
void build(int x,int l,int r);
void pushup(int x);
void pushdown(int x,int l,int r);
void changev(int x,int l,int r,int ql,int qr,long long c);
long long quev(int x,int l,int r,int ql,int qr);
void op1(int u,int v,long long c);
void op2(int u,int v);
int n,m,root,cnt,cntn,num[MAXN],dis[MAXN],head[MAXN],to[MAXN<<1],nxt[MAXN<<1],siz[MAXN],hvson[MAXN],fa[MAXN],ffa[MAXN];
long long mod,ta[MAXN],a[MAXN],v[MAXN<<4],lztag[MAXN<<4];
bool p[MAXN],vis[MAXN];
int main(){
	scanf("%d%d%d%lld",&n,&m,&root,&mod);
	for (int i=1;i<=n;i++) scanf("%lld",ta+i);
	for (int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	fa[root]=ffa[root]=root;
	dfs1(root);
	dfs2(root);
	build(1,1,n);
	int opt,u,v;
	long long c;
	while(m--){
		scanf("%d",&opt);
		if (opt==1){
			scanf("%d%d%lld",&u,&v,&c);
			op1(u,v,c);
		}
		if (opt==2){
			scanf("%d%d",&u,&v);
			op2(u,v);
		}
		if (opt==3){
			scanf("%d%lld",&u,&c);
			changev(1,1,n,num[u],num[u]+siz[u]-1,c);
		}
		if (opt==4){
			scanf("%d",&u);
			printf("%lld\n",quev(1,1,n,num[u],num[u]+siz[u]-1));
		}
	}
}
void add_edge(int u,int v){
	cnt++;
	nxt[cnt]=head[u],to[cnt]=v;
	head[u]=cnt;
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
	cntn++;
	num[x]=cntn;
	a[cntn]=ta[x];
	vis[x]=1;
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
void build(int x,int l,int r){
	if (l==r){
		v[x]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushup(int x){v[x]=(v[x<<1]+v[x<<1|1])%mod;}
void pushdown(int x,int l,int r){
	int mid=(l+r)>>1;
	lztag[x<<1]=(lztag[x<<1]+lztag[x])%mod;
	lztag[x<<1|1]=(lztag[x<<1|1]+lztag[x])%mod;
	v[x<<1]=(v[x<<1]+lztag[x]*(mid-l+1))%mod;
	v[x<<1|1]=(v[x<<1|1]+lztag[x]*(r-mid))%mod;
	lztag[x]=0;
}
void changev(int x,int l,int r,int ql,int qr,long long c){
	if (l>=ql&&r<=qr){
		v[x]=(v[x]+c*(r-l+1))%mod;
		lztag[x]+=c;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if (mid>=ql) changev(x<<1,l,mid,ql,qr,c);
	if (mid<qr) changev(x<<1|1,mid+1,r,ql,qr,c);
	pushup(x);
}
long long quev(int x,int l,int r,int ql,int qr){
	if (l>=ql&&r<=qr) return v[x];
	int mid=(l+r)>>1;
	long long res=0;
	pushdown(x,l,r);
	if (mid>=ql) res+=quev(x<<1,l,mid,ql,qr);
	if (mid<qr) res+=quev(x<<1|1,mid+1,r,ql,qr);
	return res%mod;
}
void op1(int u,int v,long long c){
	while (ffa[u]!=ffa[v]){
		if (dis[ffa[u]]>=dis[ffa[v]]){
			changev(1,1,n,num[ffa[u]],num[u],c);
			u=fa[ffa[u]];
		}
		else{
			changev(1,1,n,num[ffa[v]],num[v],c);
			v=fa[ffa[v]];
		}
	}
	if (dis[u]>=dis[v]) changev(1,1,n,num[v],num[u],c);
	else changev(1,1,n,num[u],num[v],c);
}
void op2(int u,int v){
	long long res=0;
	while (ffa[u]!=ffa[v]){
		if (dis[ffa[u]]>=dis[ffa[v]]){
			res=(res+quev(1,1,n,num[ffa[u]],num[u]))%mod;
			u=fa[ffa[u]];
		}
		else{
			res=(res+quev(1,1,n,num[ffa[v]],num[v]))%mod;
			v=fa[ffa[v]];
		}
	}
	if (dis[u]>=dis[v]) res=(res+quev(1,1,n,num[v],num[u]))%mod;
	else res=(res+quev(1,1,n,num[u],num[v]))%mod;
	printf("%lld\n",res);
}
