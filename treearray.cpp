#include <cstdio>
#define MAXN 500005
using namespace std;
void add(int x,int c);
int quev(int x);
int n,m,v[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1,a;i<=n;i++){
		scanf("%d",&a);
		add(i,a);
	}
	int opt,l,r;
	while(m--){
		scanf("%d",&opt);
		if (opt==1){
			scanf("%d%d",&l,&r);
			add(l,r);
		}
		if (opt==2){
			scanf("%d%d",&l,&r);
			printf("%d\n",quev(r)-quev(l-1));
		}
	}
}
void add(int x,int c){
	for (;x<=n;x+=x&(-x)) v[x]+=c;
}
int quev(int x){
	int res=0;
	for (;x;x-=x&(-x)) res+=v[x];
	return res;
}
