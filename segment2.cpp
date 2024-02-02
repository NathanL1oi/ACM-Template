#include <cstdio>
#define MAXN 100005
using namespace std;
void build(int x,int l,int r);
void pushup(int x);
void pushdown(int x,int l,int r);
void changeva(int x,int l,int r,int ql,int qr,int c);
void changevm(int x,int l,int r,int ql,int qr,int c);
long long quev(int x,int l,int r,int ql,int qr);
int n,m;
long long p,a[MAXN],v[MAXN<<4],mtag[MAXN<<4],atag[MAXN<<4];
int main(){
	scanf("%d%d%lld",&n,&m,&p);
	for (int i=1;i<=n;i++) scanf("%lld",a+i);
	build(1,1,n);
	int opt,l,r,c;
	while(m--){
		scanf("%d",&opt);
		if (opt==1){
			scanf("%d%d%d",&l,&r,&c);
			changevm(1,1,n,l,r,c);
		}
		if (opt==2){
			scanf("%d%d%d",&l,&r,&c);
			changeva(1,1,n,l,r,c);
		}
		if (opt==3){
			scanf("%d%d",&l,&r);
			printf("%lld\n",quev(1,1,n,l,r));
		}
	}
}
void build(int x,int l,int r){
	if (l==r){
		v[x]=a[l];
		return ;
	}
	int mid=(l+r)>>1;
	mtag[x]=1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushup(int x){v[x]=v[x<<1]+v[x<<1|1];}
void pushdown(int x,int l,int r){
	if (atag[x]==0&&mtag[x]==1) return ;
	int mid=(l+r)>>1;
	v[x<<1]=(v[x<<1]*mtag[x]+atag[x]*(long long)(mid-l+1))%p;
	v[x<<1|1]=(v[x<<1|1]*mtag[x]+atag[x]*(long long)(r-mid))%p;
	mtag[x<<1]=mtag[x<<1]*mtag[x]%p;
	mtag[x<<1|1]=mtag[x<<1|1]*mtag[x]%p;
	atag[x<<1]=(atag[x<<1]*mtag[x]+atag[x])%p;
	atag[x<<1|1]=(atag[x<<1|1]*mtag[x]+atag[x])%p;
	mtag[x]=1,atag[x]=0;
}
void changeva(int x,int l,int r,int ql,int qr,int c){
	if (l>=ql&&r<=qr){
		v[x]=(v[x]+(long long)c*(long long)(r-l+1))%p;
		atag[x]=(atag[x]+(long long)c)%p;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if (ql<=mid) changeva(x<<1,l,mid,ql,qr,c);
	if (qr>mid) changeva(x<<1|1,mid+1,r,ql,qr,c);
	pushup(x);
}
void changevm(int x,int l,int r,int ql,int qr,int c){
	if (l>=ql&&r<=qr){
		if (atag[x]) pushdown(x,l,r);
		v[x]=v[x]*(long long)c%p;
		mtag[x]=mtag[x]*(long long)c%p;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if (ql<=mid) changevm(x<<1,l,mid,ql,qr,c);
	if (qr>mid) changevm(x<<1|1,mid+1,r,ql,qr,c);
	pushup(x);
}
long long quev(int x,int l,int r,int ql,int qr){
	if (l>=ql&&r<=qr) return v[x];
	int mid=(l+r)>>1;
	long long res=0;
	pushdown(x,l,r);
	if (ql<=mid) res+=quev(x<<1,l,mid,ql,qr);
	if (qr>mid) res+=quev(x<<1|1,mid+1,r,ql,qr);
	return res%p;
}
