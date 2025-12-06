auto KMP=[&](string s,string t)->vector<int> {
    int n=s.size(),m=t.size();
    s='@'+s;
    t='@'+t;
    vector<int> kmp(m+1),res;
    for (int i=2,j=0;i<=m;i++){
        while(j&&t[j+1]!=t[i]) j=kmp[j];
        if (t[j+1]==t[i]) j++;
        kmp[i]=j;
    }
    for (int i=1,j=0;i<=n;i++){
        while(j&&s[i]!=t[j+1]) j=kmp[j];
        if (s[i]==t[j+1]&&++j==m){
            res.push_back(i-m+1);
            j=kmp[j];
        }
    }
    return res;
};
