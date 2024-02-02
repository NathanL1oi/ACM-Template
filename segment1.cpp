#include <cstdio>
#include <iostream>
#define MAXN 100005
using namespace std;
void build(int x,int l,int r);
void changev(int x,int l,int r,int ql,int qr,int c);
void pushup(int x);
void pushdown(int x,int l,int r);
long long quev(int x,int l,int r,int ql,int qr);
int n,m;
long long a[MAXN],v[MAXN<<4],lztag[MAXN<<4];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",a+i);
	build(1,1,n);
	int l,r,c,opt;
	while(m--){
		scanf("%d",&opt);
		if (opt==1){
			scanf("%d%d%d",&l,&r,&c);
			changev(1,1,n,l,r,c);
		}
		else{
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
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushup(int x){v[x]=v[x<<1]+v[x<<1|1];}
void changev(int x,int l,int r,int ql,int qr,int c){
	if (l>=ql&&r<=qr){
		v[x]+=(long long)c*(r-l+1);
		lztag[x]+=(long long)c;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if (mid>=ql) changev(x<<1,l,mid,ql,qr,c);
	if (mid<qr) changev(x<<1|1,mid+1,r,ql,qr,c);
	pushup(x);
}
void pushdown(int x,int l,int r){
	if (lztag[x]==0) return ;
	int mid=(l+r)>>1;
	v[x<<1]+=lztag[x]*(mid-l+1),v[x<<1|1]+=lztag[x]*(r-mid);
	lztag[x<<1]+=lztag[x],lztag[x<<1|1]+=lztag[x];
	lztag[x]=0;
}
long long quev(int x,int l,int r,int ql,int qr){
	if (l>=ql&&r<=qr) return v[x];
	int mid=(l+r)>>1;
	long long res=0;
	pushdown(x,l,r);
	if (mid>=ql) res+=quev(x<<1,l,mid,ql,qr);
	if (mid<qr) res+=quev(x<<1|1,mid+1,r,ql,qr);
	return res;
}
