template <typename dt>
struct Segtree{
    int sz = 0;
    vector<dt>seg;
    dt id;
    function<dt(dt,dt)>op;
    void init(int n , function<dt(dt,dt)>temp , dt iden){
        id = iden;
        sz = 1;
        while(sz < n ) sz *= 2;
        seg.assign(2 * sz , id);
        op = temp;
    }
    void update(int i , dt v , int l = 0 , int r = -1 , int node = 0){
        if(r == -1) r = sz;
        if(r - l == 1){
            seg[node] = v;
            return;
        }
        int  mid = (l + r) / 2;
        if(i < mid) update(i , v , l , mid , 2 * node + 1);
        else update(i , v , mid , r , 2 * node + 2);
        seg[node] = op(seg[2 * node + 1] , seg[2  * node + 2]);
    }
    dt get(int ql , int qr , int l = 0 , int r = -1 , int node  =  0){
        if(r == -1) r =sz;
        if(l >= qr || r <= ql) return id;
        if(l >= ql && r <= qr) return seg[node];
        int mid = (l + r) / 2;
        return op(get(ql , qr , l , mid , 2 * node + 1)  , get(ql , qr , mid , r , 2 * node  + 2));
    };


// St.init(n , operation . Iden)
