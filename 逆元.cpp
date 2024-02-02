#include <cstdio>
using namespace std;
long long inv[3000005],n,p;
int main(){
	scanf("%lld%lld",&n,&p);
	inv[1]=1;
	printf("%lld\n",1);
	for (int i=2;i<=n;i++){
		inv[i]=(p-p/i)*inv[p%i]%p;
		printf("%lld\n",inv[i]);
	}
}