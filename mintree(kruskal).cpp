#include <cstdio>
#include <algorithm>
#define MAXN 5005
#define MAXM 200005
using namespace std;
struct inf{
	int u;
	int v;
	int c;
}edge[MAXM];
int ff(int x);
bool cmp(inf a,inf b){return a.c<b.c;}
int n,m,ans,ffa[MAXN],cnt;
bool p[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].c);
	for (int i=1;i<=n;i++) ffa[i]=i;
	sort(edge,edge+m,cmp);
	for (int i=0,u,v,c;i<m;i++){
		u=edge[i].u,v=edge[i].v,c=edge[i].c;
		if (ff(u)==ff(v)) continue;
		ans+=c;
		cnt++;
		ffa[ffa[v]]=ffa[u];
	}
	if (cnt==n-1) printf("%d",ans);
	else printf("orz");
}
int ff(int x){
	if (ffa[x]==x) return x;
	return ffa[x]=ff(ffa[x]);
}
