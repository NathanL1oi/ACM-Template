#include <cstdio>
#define MAXN 100005
using namespace std;
void build(int x,int l,int r);
void pushup(int x);
int quev(int x,int l,int r,int ql,int qr);
void change1(int x,int l,int r,int cl,int cr,int cv);
void change2(int x,int l,int r,int cl,int cr,int cv);
void pushdown(int x,int l,int r);
int s[MAXN<<2],atag[MAXN<<1],mtag[MAXN<<1],n,a[MAXN],b,c,d,opt;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",a+i);
	build(1,1,n);
	while(scanf("%d",&opt)!=EOF){
		if (opt==1){
			scanf("%d%d",&b,&c);
			printf("%d\n",quev(1,1,n,b,c));
		}
		if (opt==2){
			scanf("%d%d%d",&b,&c,&d);
			change1(1,1,n,b,c,d);
		}
		if (opt==3){
			scanf("%d%d%d",&b,&c,&d);
			change2(1,1,n,b,c,d);
		}
	}
}
void build(int x,int l,int r){
	mtag[x]=1;
	if (l==r){s[x]=a[l]; return;}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void pushup(int x){s[x]=s[x<<1]+s[x<<1|1];}
void pushdown(int x,int l,int r){
	if (atag[x]==0&&mtag[x]==1) return ;
	int mid=(l+r)>>1;
	s[x<<1]=s[x<<1]*mtag[x]+(mid-l+1)*atag[x];
	s[x<<1|1]=s[x<<1|1]*mtag[x]+(r-mid)*atag[x];
	mtag[x<<1]*=mtag[x];
	mtag[x<<1|1]*=mtag[x];
	atag[x<<1]=atag[x<<1]*mtag[x]+atag[x];
	atag[x<<1|1]=atag[x<<1|1]*mtag[x]+atag[x];
	atag[x]=0,mtag[x]=1;
}
int quev(int x,int l,int r,int ql,int qr){
	if (ql<=l&&qr>=r){return s[x];}
	int mid=(l+r)>>1,sum;
	pushdown(x,l,r);
	if (mid>=ql) sum+=quev(x<<1,l,mid,ql,qr);
	if (mid<qr) sum+=quev(x<<1|1,mid+1,r,ql,qr);
	return sum;
}
void change1(int x,int l,int r,int cl,int cr,int cv){
	if (cl<=l&&cr>=r){
		s[x]+=cv*(r-l+1);
		atag[x]+=cv;
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(x,l,r);
	if (mid>=cl) change1(x<<1,l,mid,cl,cr,cv);
	if (mid<cr) change1(x<<1|1,mid+1,r,cl,cr,cv);
	pushup(x);
}
void change2(int x,int l,int r,int cl,int cr,int cv){
	if (cl<=l&&cr>=r){
		if (atag[x]) pushdown(x,l,r);
		s[x]*=cv;
		mtag[x]*=cv;
		return ;
	}
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	if (mid>=cl) change2(x<<1,l,mid,cl,cr,cv);
	if (mid<cr) change2(x<<1|1,mid+1,r,cl,cr,cv);
	pushup(x);
}
