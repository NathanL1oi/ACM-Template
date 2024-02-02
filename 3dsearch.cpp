#include <cstdio>
#define MAXN 15
using namespace std;
double f(double x);
int n;
double l,r,mid,a[MAXN];
const double eps=1e-6;
int main(){
	scanf("%d%lf%lf",&n,&l,&r);
	for (int i=n;i>=0;i--) scanf("%lf",a+i);
	while(r-l>=eps){
		mid=(l+r)/2;
		if (f(mid+eps)>f(mid-eps)) l=mid;
		else r=mid;
	}
	printf("%.5lf",r);
}
double f(double x){
	double res=0,tmp=1;
	for (int i=0;i<=n;i++){
		res+=tmp*a[i];
		tmp*=x;
	}
	return res;
}
