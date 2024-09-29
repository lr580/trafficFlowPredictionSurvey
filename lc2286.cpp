#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 1, maxm = maxn << 2;
using ll = long long;
struct SegTr {
    int mx[maxm], laz[maxm], loc[maxm];
    ll sum[maxm];
    void pushup(int p) {
        mx[p] = max(mx[p<<1], mx[p<<1|1]);
        sum[p] = sum[p<<1] + sum[p<<1|1];
    }
    void build(int p, int lf, int rf, int m) {
        laz[p] = 0;
        if(lf==rf) {
            mx[p]=sum[p]=m;
            loc[lf]=p;
            return;
        }
        int cf=(lf+rf)>>1;
        build(p<<1, lf, cf, m);
        build(p<<1|1, cf+1, rf, m);
        pushup(p);
    }
    void pushdown(int p, int lf, int rf) {
        if(laz[p]) {
            int cf=(lf+rf)>>1;
            laz[p<<1] = laz[p];
            mx[p<<1] = laz[p];
            sum[p<<1] = (cf-lf+1)*laz[p];
            laz[p<<1|1] = laz[p];
            mx[p<<1|1] = laz[p];
            sum[p<<1|1] = (rf-cf)*laz[p];
            laz[p] = 0;
        }
    }
    ll query(int p, int lf, int rf, int l, int r) {
        if(l>r) return 0;
        if(l<=lf && rf<=r) return sum[p];
        int cf=(lf+rf)>>1;
        ll res=0;
        pushdown(p, lf, rf);
        if(l<=cf) res+=query(p<<1, lf, cf, l, r);
        if(cf<r) res+=query(p<<1|1, cf+1, rf, l, r);
        return res;
    }
    //区间[l,r]每个值变化为v
    void modify(int p, int lf, int rf, int l, int r, int v) {
        if(l>r) return;
        if(l<=lf && rf<=r) {
            mx[p] = v;
            laz[p] = v;
            sum[p] = (rf-lf+1)*v;
            return;
        }
        int cf = (lf+rf)>>1;
        pushdown(p, lf, rf);
        if(l<=cf) modify(p<<1, lf, cf, l, r, v);
        if(cf<r) modify(p<<1|1, cf+1, rf, l, r, v);
        pushup(p);
    }
    //找到最小点，满足该点值>=k
    int findMin(int p, int lf, int rf, int k) {
        if(mx[p]<k) return -1;
        if(lf==rf) return lf;
        int cf = (lf+rf)>>1;
        pushdown(p, lf, rf);
        if(mx[p<<1]>=k) return findMin(p<<1, lf, cf, k);
        return findMin(p<<1|1, cf+1, rf, k);
    }
    //找到最小点x，满足[1,x]的和>=k
    int findMinSum(int p, int lf, int rf, int k) {
        if(sum[p]<k) return -1;
        if(lf==rf) return lf;
        int cf = (lf+rf)>>1;
        pushdown(p, lf, rf);
        if(sum[p<<1]>=k) 
            return findMinSum(p<<1, lf, cf, k);
        return findMinSum(p<<1|1, cf+1, rf, k-sum[p<<1]);
    }
} t;
class BookMyShow {
    int n, m;
public:
    BookMyShow(int n, int m) {
        this->n = n;
        this->m = m;
        t.build(1, 1, n, m);
    }
    
    vector<int> gather(int k, int maxRow) {
        int r = t.findMin(1, 1, n, k);
        if(r==-1 || r-1>maxRow) {
            return {};
        }
        int left = t.sum[t.loc[r]];
        int c = m - left + 1;
        t.modify(1,1,n,r,r,left-k);
        return {r-1,c-1};
    }
    
    bool scatter(int k, int maxRow) {
        int r = t.findMinSum(1, 1, n, k);
        if(r==-1 || r-1>maxRow) {
            return false;
        }
        int s = t.query(1,1,n,1,r-1); // [1,r-1]
        t.modify(1,1,n,1,r-1,0);
        t.modify(1,1,n,r,r,t.sum[t.loc[r]]-(k-s));
        return true;
    }
};
void test(int n) {
    for(int i=1;i<=n;++i) {
        cout<<t.sum[t.loc[i]]<<' ';
    } cout << '\n';
}
signed main() {
    BookMyShow t(2,5);
    for(auto v:t.gather(4,0)) {
        cout<<v<<' ';
    } cout << '\n'; test(2);
    for(auto v:t.gather(2,0)) {
        cout<<v<<' ';
    } cout << '\n'; test(2);
    cout<<t.scatter(5,1)<<'\n'; test(2);
    cout<<t.scatter(5,1)<<'\n'; test(2);
}
/*
signed main() {
    t.build(1,1,5,10);
    cout<<t.findMin(1,1,5,9)<<'\n';
    cout<<t.findMin(1,1,5,10)<<'\n';
    cout<<t.findMin(1,1,5,11)<<'\n';
    cout<<t.findMinSum(1,1,5,29)<<'\n';
    cout<<t.findMinSum(1,1,5,30)<<'\n';
    cout<<t.findMinSum(1,1,5,31)<<'\n';
    cout<<t.query(1,1,5,2,3)<<'\n';
    t.modify(1,1,5,2,4,1);
    cout<<"After\n";
    cout<<t.sum[t.loc[4]]<<' '<<t.sum[t.loc[5]]<<'\n';
    cout<<t.findMin(1,1,5,9)<<'\n';
    cout<<t.findMin(1,1,5,10)<<'\n';
    cout<<t.findMin(1,1,5,11)<<'\n';
    cout<<t.findMinSum(1,1,5,10)<<'\n';
    cout<<t.findMinSum(1,1,5,12)<<'\n';
    cout<<t.findMinSum(1,1,5,13)<<'\n';
    cout<<t.findMinSum(1,1,5,14)<<'\n';
    cout<<t.findMinSum(1,1,5,23)<<'\n';
    cout<<t.findMinSum(1,1,5,24)<<'\n';
    cout<<t.query(1,1,5,2,3)<<'\n';
    cout<<t.query(1,1,5,1,5)<<'\n';
    cout<<t.query(1,1,5,4,4)<<'\n';
    return 0;
}
*/