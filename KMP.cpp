#include <cstdio>
#include <cstring>
#define MAXN 1000005
using namespace std;
int n,m,kmp[MAXN];
char s[MAXN],t[MAXN];
int main(){
	scanf("%s",s+1);
	scanf("%s",t+1);
	n=strlen(s+1);
	m=strlen(t+1);
	for (int i=2,j=0;i<=m;i++){
		while(j&&t[j+1]!=t[i]) j=kmp[j];
		if (t[j+1]==t[i]) j++;
		kmp[i]=j;
	}
	for (int i=0,j=0;i<=n;i++){
		while(j&&s[i]!=t[j+1]) j=kmp[j];
		if (s[i]==t[j+1]) j++;
		if (j==m){
			printf("%d\n",i-m+1);
			j=kmp[j];
		}
	}
	for (int i=1;i<=m;i++) printf("%d ",kmp[i]);
}
