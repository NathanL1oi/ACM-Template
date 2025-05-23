struct sieve{
    vector<int> minp,primes;
    sieve(int n){
        minp.assign(n+1,0);
        for (int i=2;i<=n;i++){
            if (minp[i]==0){
                minp[i]=i;
                primes.push_back(i);
            }
            for (auto p:primes){
                if (i*p>n) break;
                minp[i*p]=p;
                if (p==minp[i]) break;
            }
        }
    }
    bool isprime(int x){
        return minp[x]==x;
    }
    int size(){
        return primes.size();
    }
    vector<int>& getprimes(){
        return primes;
    }
};