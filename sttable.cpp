#include <cstdio>
#include <iostream>
#define MAXX 17
#define MAXN 100005
using namespace std;
int n,m,dp[MAXN][MAXX],ans,tmp;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&dp[i][0]);
	for (int x=1;x<MAXX;x++){
		tmp=n-(1<<x)+1;
		for (int i=1;i<=tmp;i++) dp[i][x]=max(dp[i][x-1],dp[i+(1<<(x-1))][x-1]);
	}
	int l,r,d;
	while(m--){
		scanf("%d%d",&l,&r);
		d=r-l+1;
		for (tmp=MAXX;tmp>=0;tmp--){
			if ((1<<tmp)<=d) break;
		}
		ans=max(dp[l][tmp],dp[r-(1<<tmp)+1][tmp]);
		printf("%d\n",ans);
	}
}
