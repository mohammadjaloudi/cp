typedef long long i64;
i64 binpow(__int128_t x,i64 y,i64 mod){
    i64 ans = 1;
    x %= mod;
    while(y){
        if(y & 1) ans = (x*ans)%mod;
        y >>=1ll;
        x = (x*x)%mod;
    }
    return ans;
}
bool is_prime(i64 n){
    if(n <= 1) return 0;
    else if(n == 2) return 1;
    else if(n == 3) return 1;
    else if(!(n & 1)) return 0;
    vector<i64> bases = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022}; // 2^64
    // if number less than 2^32, {2,7,61} enough
 
    i64 d = n-1;
    int s = 0;
    while(!(d & 1)){d/=2;s++;}

    // 
    for(int a : bases){
        if(a >= n) break;
        i64 x = binpow(a,d,n);
 
 
        if(x == 1 || x == n-1) continue;
       
        bool worked = 0;
        for(int _ = 0; _ < s-1 && !worked; _++){
            x = binpow(x,2,n);
            if(x == n-1){worked = 1;break;}
        }
        
        if(!worked){
            return 0;
        }
    }
    return 1;
}
