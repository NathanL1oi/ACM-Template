#include <cstdio>
#include <iostream>
#define MAXN 5005
#define MAXM 200005
#define INF 1000000005
using namespace std;
void add_edge(int u,int v,int c);
int n,m,cnt,head[MAXN],to[MAXM<<1],nxt[MAXM<<1],cost[MAXM<<1],ans,dis[MAXN];
bool p[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0,u,v,c;i<m;i++){
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
		add_edge(v,u,c);
	}
	for (int i=1;i<=n;i++) dis[i]=INF;
	for (int i=1,x=1,tmp,tmpc;i<n;i++){
		p[x]=1;
		tmp=0,tmpc=INF;
		for (int u=head[x],v,c;u;u=nxt[u]){
			v=to[u],c=cost[u];
			if (p[v]) continue;
			dis[v]=min(dis[v],c);
		}
		for (int i=1;i<=n;i++){
			if (p[i]) continue;
			if (dis[i]<tmpc) tmp=i,tmpc=dis[i];
		}
		if (tmp==0){printf("orz"); return 0;}
		ans+=tmpc;
		x=tmp;
	}
	printf("%d",ans);
}
void add_edge(int u,int v,int c){
	cnt++;
	nxt[cnt]=head[u],to[cnt]=v,cost[cnt]=c;
	head[u]=cnt;
}
