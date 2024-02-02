#include <cstdio>
#include <string>
#define MAXN 100005
#define mod1 39989
#define mod2 1000000000
#define pdi pair<int,double>
using namespace std;
void changev(int x,int l,int r,int ql,int qr,int d);
pdi quev(int x,int l,int r,int pos);
void pushdown(int x,int l,int r,int d);
double cal(int d,int x);
int cmp(double a,double b);
pdi cmp2(pdi a,pdi b);
struct XD{
	double k;
	double b;
}xd[MAXN];
int n,lx,ly,rx,ry,las,v[mod1<<4],cnt;
const double eps=1e-9;
int main(){
	scanf("%d",&n);
	for (int i=1,lx,ly,rx,ry,opt;i<=n;i++){
		scanf("%d",&opt);
		if (opt){
			scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
			lx=(lx+las-1)%mod1+1,rx=(rx+las-1)%mod1+1;
			ly=(ly+las-1)%mod2+1,ry=(ry+las-1)%mod2+1;
			cnt++;
			if (lx>rx){
				swap(lx,rx); swap(ly,ry);
			}
			if (lx==rx) xd[cnt].k=0,xd[cnt].b=max(ly,ry);
			else{xd[cnt].k=(double)(ry-ly)/(rx-lx); xd[cnt].b=ly-xd[cnt].k*lx;}
			//printf("%lf\n",xd[cnt].k);
			changev(1,1,mod1,lx,rx,cnt);
		}
		else{
			scanf("%d",&lx);
			lx=(lx+las-1)%mod1+1;
			printf("%d\n",las=quev(1,1,mod1,lx).first);
		}
	}
}
void changev(int x,int l,int r,int ql,int qr,int d){
	if (ql<=l&&qr>=r){
		pushdown(x,l,r,d);
		return ;
	}
	int mid=(l+r)>>1;
	if (ql<=mid) changev(x<<1,l,mid,ql,qr,d);
	if (qr>mid) changev(x<<1|1,mid+1,r,ql,qr,d);
}
void pushdown(int x,int l,int r,int d){
	int mid=(l+r)>>1;
	if (cmp(cal(d,mid),cal(v[x],mid))==1) swap(d,v[x]);
	int bl=cmp(cal(d,l),cal(v[x],l)),br=cmp(cal(d,r),cal(v[x],r));
	if (bl==1||(bl==0&&d<v[x])) pushdown(x<<1,l,mid,d);
	if (br==1||(br==0&&d<v[x])) pushdown(x<<1|1,mid+1,r,d);
}
pdi quev(int x,int l,int r,int pos){
	if (l==r){
		return {v[x],cal(v[x],pos)};
	}
	int mid=(l+r)>>1;
	pdi res;
	if (pos<=mid) res=quev(x<<1,l,mid,pos);
	else res=quev(x<<1|1,mid+1,r,pos);
	return cmp2({v[x],cal(v[x],pos)},res);
}
double cal(int d,int x){return xd[d].k*x+xd[d].b;}
int cmp(double a,double b){
	if (a-b>eps) return 1;
	if (b-a>eps) return -1;
	return 0;
}
pdi cmp2(pdi a,pdi b){
	if (a.second-b.second>eps) return a;
	if (b.second-a.second>eps) return b;
	if (a.first<b.first) return a;
	return b;
}
