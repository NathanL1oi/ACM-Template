void KMP(string &s,string &t,vector<int> &ans){
	int n=s.size(),m=t.size();
	vector<int> kmp(m+1,-1);
	for (int i=1,j=-1;i<m;i++){
		while(j>=0&&t[j+1]!=t[i]) j=kmp[j];
		if (t[j+1]==t[i]) j++;
		kmp[i]=j;
	}
	for (int i=0,j=-1;i<n;i++){
		while(j>=0&&t[j+1]!=s[i]) j=kmp[j];
		if (t[j+1]==s[i]) j++;
		if (j==m-1){
			ans.push_back(i-m+1);
			j=kmp[j];
		}
	}
}