long long inv(long long x){
	if (x==1) return 1;
	return (m-m/x)*inv(m%x)%m;
}
//m is mod number
