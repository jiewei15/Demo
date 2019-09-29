HDU 6315
 
https://www.cnblogs.com/taozi1115402474/p/9370310.html
题意

初始a数组为0，给你一个全排列的b数组，q次询问add x y为a数组区间x y增加1，
query x y查询a数组整除b数组对应下标的和

题解

区间操作很容易想到线段树

初始每个叶子节点赋值为b[i]，维护一个区间最小值min，和区间和sum

对于每个add，区间[X,Y]最小值减1，如果当前区间最小值=1，就继续往下更新，
如果更新到叶子节点并且min=1，sum+1

对于每个query，查询区间[X,Y]sum，如果区间min=0，再去暴力更新区间
（可以知道一共q次询问，q/1+q/2+q/3+....q/n为调和级数，复杂度O(logn)）

总复杂度O（nlog^2 n）

代码
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;

int a[N<<2],lazy[N<<2],b[N],sum[N<<2];
int n;
void PushUp(int rt)
{
    a[rt]=min(a[rt<<1],a[rt<<1|1]);
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int rt)
{
    if(lazy[rt]==0)return;
    lazy[rt<<1]+=lazy[rt];
    lazy[rt<<1|1]+=lazy[rt];
    a[rt<<1]-=lazy[rt];
    a[rt<<1|1]-=lazy[rt];
    lazy[rt]=0;
}
void Build(int l,int r,int rt)
{
    lazy[rt]=0;sum[rt]=0;
    if(l==r)
    {
        a[rt]=b[l];
        return;
    }
    int mid=(l+r)>>1;
    Build(l,mid,rt<<1);
    Build(mid+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(a[rt]>1&&L<=l&&r<=R)
    {
        lazy[rt]++;
        a[rt]--;
        return;
    }
    if(a[rt]==1&&l==r)
    {
        sum[rt]++;
        lazy[rt]=0;
        a[rt]=b[l];
        return;
    }
    int mid=(l+r)>>1;
    PushDown(rt);
    if(L<=mid)Update(L,R,l,mid,rt<<1);
    if(R>mid)Update(L,R,mid+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)return sum[rt];
    if(a[rt]==0)Update(L,R,1,n,1);
    int mid=(l+r)>>1,ans=0;
    PushDown(rt);
    if(L<=mid)ans+=Query(L,R,l,mid,rt<<1);
    if(R>mid)ans+=Query(L,R,mid+1,r,rt<<1|1);
    PushUp(rt);
    return ans;
}
int main()
{
    int q,x,y;
    char op[10];
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        Build(1,n,1);
        for(int i=0;i<q;i++)
        {
            scanf("%s%d%d",op,&x,&y);
            if(op[0]=='a')
                Update(x,y,1,n,1);
            else
                printf("%d\n",Query(x,y,1,n,1));
        }
    }
    return 0;
}


https://blog.csdn.net/qq_36368339/article/details/81214204
HDU 6315 Naive Operations【线段树+lazy】
题意：给你一段固定的序列1~n，当作分母，两次操作：add,L,R，区间所有的分子+1；
query,L,R，查询区间和a[i]/b[i](向下取整)a[i]/b[i](向下取整). 
分析： 
区间维护sum和lazy，暴力更新lazy会TLE。由于分母固定，那就维护一个
区间sub[root]=min(b[i]−a[i]sub[root]=min(b[i]−a[i]%b[i])b[i])，
只有当sub[root]=0时，才会更新lazy和sum。 
ps：注意一点，实时更新sub值，不然lazy值的覆盖会导致sum出错.
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 4e5 + 10;
int b[MAXN];
int sub[MAXN], sum[MAXN], lazy[MAXN];

void up(int root) {
    sum[root] = sum[root << 1] + sum[root << 1 | 1];
    sub[root] = min(sub[root << 1], sub[root << 1 | 1]);
}

void down(int root) {
    lazy[root << 1] += lazy[root], sub[root << 1] -= lazy[root];
    lazy[root << 1 | 1] += lazy[root], sub[root << 1 | 1] -= lazy[root];
    lazy[root] = 0;
}

void build(int root, int L, int R) {
    sum[root] = 0;
    lazy[root] = 0; //切记在区间前更新
    if(L == R) {
        scanf("%d", &b[L]);
        sub[root] = b[L];
        return ;
    }
    int mid = (L + R) >> 1;
    build(root << 1, L, mid);
    build(root << 1 | 1, mid + 1, R);
    up(root);
}

void update1(int root, int L, int R) {
    if(L == R) {
        sum[root]++;
        sub[root] = b[L];
        return ;
    }
    int mid = (L + R) >> 1;
    down(root);
    if(!sub[root << 1]) update1(root << 1, L, mid);
    if(!sub[root << 1 | 1]) update1(root << 1 | 1, mid + 1, R);
    up(root);
}

void update(int root, int L, int R, int l, int r) {
    if(L >= l && R <= r) {
        lazy[root]++;
        sub[root]--;
        if(!sub[root]) update1(root, L, R);
        return;
    }
    int mid = (L + R) >> 1;
    down(root);
    if(l <= mid) update(root << 1, L, mid, l, r);
    if(r > mid) update(root << 1 | 1, mid + 1, R, l, r);
    up(root);
}

int query(int root, int L, int R, int l, int r) {
    if(L >= l && R <= r) {
        return sum[root];
    }
    int ans = 0;
    int mid = (L + R) >> 1;
    down(root);
    if(l <= mid) ans += query(root << 1, L, mid, l, r);
    if(r > mid) ans += query(root << 1 | 1, mid + 1, R, l, r);
    up(root);
    return ans;
}

int main() {
    int n, q;
    while(scanf("%d %d", &n, &q) != EOF) {
        build(1, 1, n);
        char s[10];
        int a, b;
        while(q--) {
            scanf("%s%d%d", s, &a, &b);
            if(s[0] == 'a') update(1, 1, n, a, b);
            else printf("%d\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}
--------------------- 
作者：HPU王小二 
来源：CSDN 
原文：https://blog.csdn.net/qq_36368339/article/details/81214204 
版权声明：本文为博主原创文章，转载请附上博文链接！





https://www.cnblogs.com/tiberius/p/9369683.html

思路：本题的思路总的来说就是暴力 + 剪枝。

我们依然用线段树来维护：

定义结点node{ l , r , minn , contirbute} 分别为某个区间的左右端点，和该
区间（b序列）内的最小值与该区间对答案的贡献。

当我们修改到某一个区间的时候，如果该区间的minn > 1，那么minn--，并且给该区
间打上懒标记。

如果该区间的minn == 1，那么我们看一下这个区间的左右两个子区间，对于minn > 1
的子区间，我们就采取上面的操作。

对于minn == 1的子区间，我们就一直往下找，直到定位到了最底层的叶子节点，
对于该子节点的minn，我们将它复原，但是把它的contribute += 1。

其实就是利用minn值来剪枝。

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;

struct node{
    int l,r,minn,contri;
    node(int a = 0,int b = 0,int c = 0,int d = 0){
        l = a,r = b,minn = c,contri = d;
    }
};

node store[maxn<<2];
int depot[maxn],add[maxn<<2],n,q;
char op[10];

void pushup(int id){
    store[id].contri = store[id<<1].contri + store[id<<1 | 1].contri;
    store[id].minn = min(store[id<<1].minn,store[id<<1 | 1].minn);
}
void pushdown(int id){
    if(add[id]){
        store[id<<1].minn -= add[id];
        store[id<<1 | 1].minn -= add[id];
        add[id<<1] += add[id];
        add[id<<1 | 1] += add[id];
        add[id] = 0;
    }
}
void build(int l,int r,int id){
    store[id].l = l,store[id].r = r;
    if(l == r){
        store[id].minn = depot[l];
        store[id].contri = 0;
        return;
    }
    int mid = (l + r)>>1;
    build(l,mid,id<<1);
    build(mid + 1,r,id<<1 | 1);
    pushup(id);
}
void modify(int l,int r,int id){
    
    if(store[id].l == l && store[id].r == r && store[id].minn > 1){
        store[id].minn -= 1;
        add[id] += 1;
        return;
    }
    if(store[id].l == store[id].r){
        store[id].minn -= 1;
        add[id] += 1;
        if(store[id].minn <= 0){
            store[id].minn = depot[l];
            store[id].contri += 1;
        }
        return;
    }
    pushdown(id);
    int mid = (store[id].l + store[id].r)>>1;
    if(r <= mid) modify(l,r,id<<1);
    else if(mid < l) modify(l,r,id<<1 | 1);
    else{
        modify(l,mid,id<<1);
        modify(mid + 1,r,id<<1 | 1);
    }
    pushup(id);
}
int query(int l,int r,int id){
    if(store[id].l == l && store[id].r == r){
        return store[id].contri;
    }
    pushdown(id);
    int mid = (store[id].l + store[id].r)>>1;
    int ret = 0;
    if(r <= mid) ret = query(l,r,id<<1);
    else if(mid < l) ret = query(l,r,id<<1 | 1);
    else ret = query(l,mid,id<<1) + query(mid + 1,r,id<<1 | 1);
    pushup(id);
    return ret;
}

int main(){
    while(scanf("%d%d",&n,&q) == 2){
        memset(add,0,sizeof(add));
        for(int i = 1;i <= n;++i){
            scanf("%d",&depot[i]);
        }
        build(1,n,1);
        for(int i = 0;i < q;++i){
            int l,r;
            scanf("%s%d%d",op,&l,&r);
            if(op[0] == 'a'){
                modify(l,r,1);
            }
            else{
                int ans = query(l,r,1);
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}