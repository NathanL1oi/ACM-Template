using i128=__int128;
istream &operator>>(istream &is,i128 &n){
    string s;
    is>>s;
    n=0;
    for (int i=0,len=s.size();i<len;i++){
        n=n*10+s[i]-'0';
    }
    return is;
}
ostream &operator<<(ostream &os,i128 n){
    string s;
    while(n){
        s+='0'+n%10;
        n/=10;
    }
    std::reverse(s.begin(),s.end());
    if (s.size()==0) s="0";
    return os<<s;
}