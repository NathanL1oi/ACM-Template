#include <cstdio>
#include <queue>
#define MAXN 100005
#define MAXM 200005
#define INF 1000000005
using namespace std;
struct inf{
	int pos;
	int cost;
	friend bool operator< (inf a,inf b){return a.cost>b.cost;}
};
priority_queue<inf> q;
void add_edge(int u,int v,int c);
int n,m,s,dis[MAXN],head[MAXN],to[MAXM<<1],nxt[MAXM<<1],cost[MAXM<<1],cnt,tmp;
bool p[MAXN];
int main(){
	scanf("%d%d%d",&n,&m,&s);
	for (int i=0,u,v,c;i<m;i++){
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
	}
	for (int i=1;i<=n;i++) dis[i]=INF;
	dis[s]=0;
	q.push((inf){s,0});
	while(!q.empty()){
		tmp=q.top().pos;
		q.pop();
		if (p[tmp]) continue;
		p[tmp]=1;
		for (int u=head[tmp],v,c;u;u=nxt[u]){
			v=to[u],c=cost[u];
			if (p[v]) continue;
			if (dis[v]>dis[tmp]+c){
				dis[v]=dis[tmp]+c;
				q.push((inf){v,dis[v]});
			}
		}
	}
	for (int i=1;i<=n;i++) printf("%d ",dis[i]);
}
void add_edge(int u,int v,int c){
	cnt++;
	nxt[cnt]=head[u],to[cnt]=v,cost[cnt]=c;
	head[u]=cnt;
}
