
【BZOJ 4034】[HAOI2015]树上操作 差分+dfs序+树状数组
我们只要看出来这道题 数组表示的含义就是 
某个点到根节点路径权值和就行 
那么我们可以把最终答案 
看做 k*x+b x就是其深度 ，
我们发现dfs序之后，
修改一个点是差分一个区间，
修改一个点的子树，
可以看做对于子树中的每一个点进行 a*(deep[x]-deep[root]+1) 
root是子树根节点，那么我们对 k 用a差分区间 
对b用 -a*(deep[root]-1)差分区间

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#define MAXN 100010
using namespace std;
typedef long long LL;
LL k[MAXN], b[MAXN];
int n,m;
inline LL sum_k(int x)
{
    LL sum=0;
    while(x>0) sum+=k[x],x-=x&(-x);   
    return sum;       
}
inline void ins_k(int x,LL key)
{
    while(x<=n) k[x]+=key,x+=x&(-x);
}
inline LL sum_b(int x)
{
    LL sum=0;
    while(x>0) sum+=b[x],x-=x&(-x);
    return sum;
}
inline void ins_b(int x,LL key)
{
    while(x<=n) b[x]+=key,x+=x&(-x);
} 
int l[MAXN],r[MAXN];
struct VIA
{
    int to,next;
}c[MAXN<<1];
int head[MAXN], t, Ti, deep[MAXN];
inline void add(int x,int y)
{
  c[++t].to=y;
  c[t].next=head[x];
  head[x]=t;
}
void dfs(int x)
{
   l[x]=++Ti;
   for(int i=head[x];i;i=c[i].next)
   if(l[c[i].to]==0)
   {
     deep[c[i].to] = deep[x] + 1;
     dfs(c[i].to);
   }
   r[x]=Ti;
}
int temp[MAXN];
inline void Init()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&temp[i]);
    for(int i=1;i<n;i++)
    {
       int x,y;
       scanf("%d%d",&x,&y);
       add(x,y);
       add(y,x); 
    }
    deep[1]=1;
    dfs(1);
    for(int i=1;i<=n;i++)
     ins_b(l[i],temp[i]), ins_b(r[i]+1,-temp[i]);
}
inline void work()
{
    while(m--)
    {
      int opt,x,a;
      scanf("%d%d",&opt, &x);
      if(opt==1)
      {
        scanf("%d",&a);
        ins_b(l[x], a), ins_b(r[x]+1, -a);
      }else
      if(opt==2)
      {
        scanf("%d",&a);
        ins_k(l[x],a), ins_k(r[x]+1,-a);
        ins_b(l[x], -(LL)a * (deep[x]-1)), ins_b(r[x]+1, (LL)a * (deep[x]-1));
      }else
      {
        LL ans = sum_k(l[x])*deep[x] + sum_b(l[x]);
        printf("%lld\n",ans);
      }
    }
}
int main()
{
    Init();
    work();
    return 0;
}

//|||||||||||||||||||||||||||||||||||||||||
/**_________________________________________*/


#include<cstdio>
typedef long long ll;
const int N = 1000000 + 5;
ll c[N][3],dep[N];
int last[N],cnt,in[N],out[N],scnt,n,m,T,a[N];
struct Edge{ int to, next; }e[N*4];
void modify( int x, ll val, int key ){ for( int i = x; i <= scnt; i += i&(-i) ) c[i][key] += val; }
ll query( int x, int key ){
  ll res = 0; for( int i = x; i; i -= i&(-i) ) res += c[i][key];
  return res;
}
void insert( int u, int v ){
  e[++cnt].to = v; e[cnt].next = last[u]; last[u] = cnt;
  e[++cnt].to = u; e[cnt].next = last[v]; last[v] = cnt;
}
void dfs( int x, int fa ){
  in[x] = ++scnt;
  for( int i = last[x]; i; i = e[i].next )
    if( e[i].to != fa ){
      dep[e[i].to] = dep[x] + 1; dfs(e[i].to,x);
    }
  out[x] = ++scnt;
}
int main(){
  scanf("%d%d", &n, &m);
  for( int i = 1; i <= n; i++ ) scanf("%d", &a[i]);
  for( int i = 1,u,v; i < n; i++ ){
    scanf("%d%d", &u, &v); insert( u, v );
  }
  dfs(1,0);
  for( int i = 1; i <= n; i++ ) modify( in[i], a[i], 0 ), modify( out[i], -a[i], 0 );
  for( int i = 1; i <= m; i++ ){
    scanf("%d", &T); int k,x; 
    if( T == 1 ){
      scanf("%d%d", &k, &x);
      modify( in[k], x, 0 ); modify( out[k], -x, 0 );
    } if( T == 2 ){
      scanf("%d%d", &k, &x);
      modify( in[k], x, 1 ); modify( out[k], -x, 1 );
      modify( in[k], dep[k]*(ll)x, 2 ); modify( out[k], -dep[k]*(ll)x, 2 );
    } if( T == 3 ){
      scanf("%d", &x);
      printf("%lld\n",query(in[x],1)*(dep[x]+1)+query(in[x],0)-query(in[x],2));
    }
  }
  return 0;
}

/**——————————————————————————————————————————————————————*/

[bzoj4034][HAOI2015]树上操作——树状数组+dfs序
Brief Description
您需要设计一种数据结构支持以下操作：

把某个节点 x 的点权增加 a 。
把某个节点 x 为根的子树中所有点的点权都增加 a 。
询问某个节点 x 到根的路径中所有点的点权和。
Algorithm Design
我们考察操作对于查询的贡献。
对于操作1，如果节点y是节点x的后代，那么可以贡献a
对于操作2，如果节点y是节点x的后代，那么可以贡献a∗(depy−depx+1)
我们可以使用两个树状数组来维护贡献。

Code
#include <cstdio>
#define lowbit(i) (i) & -(i)
const int maxn = 101000;
#define ll long long
ll bit[2][maxn];
ll n, m, cnt = 0;
void change(ll id, ll pos, ll val) {
  for (ll i = pos; i <= n; i += lowbit(i)) {
    bit[id][i] += val;
  }
}
ll query(ll id, ll pos) {
  ll ans = 0;
  for (ll i = pos; i; i -= lowbit(i)) {
    ans += bit[id][i];
  }
  return ans;
}

struct edge {
  ll to, next;
} e[maxn << 1];

ll l[maxn], r[maxn], dfn = 0, val[maxn], deep[maxn], head[maxn], q[maxn];
void add(ll x, ll y) {
  e[++cnt].to = y;
  e[cnt].next = head[x];
  head[x] = cnt;
}
void add_edge(ll x, ll y) {
  add(x, y);
  add(y, x);
}
void dfs(ll x, ll fa) {
  l[x] = ++dfn;
  q[dfn] = x;
  for (ll i = head[x]; i; i = e[i].next) {
    if (e[i].to != fa) {
      deep[e[i].to] = deep[x] + 1;
      dfs(e[i].to, x);
    }
  }
  r[x] = dfn;
}

int main() {
  //  freopen("haoi2015_t2.in", "r", stdin);
  //  freopen("haoi2015_t2.out", "w", stdout);
  scanf("%lld %lld", &n, &m);
  for (ll i = 1; i <= n; i++) {
    scanf("%lld", &val[i]);
  }
  for (ll i = 1; i < n; i++) {
    ll x;
    ll y;
    scanf("%lld %lld", &x, &y);
    add_edge(x, y);
  }
  dfs(1, 0);
  for (ll i = 1; i <= n; i++) {
    change(1, l[i], val[i]);
    change(1, r[i] + 1, -val[i]);
  }
  while (m--) {
    ll opt, x, y;
    scanf("%lld %lld", &opt, &x);
    if (opt == 1) {
      scanf("%lld", &y);
      change(1, l[x], y);
      change(1, r[x] + 1, -y);
    }
    if (opt == 2) {
      scanf("%lld", &y);
      change(0, l[x], y);
      change(1, l[x], -deep[x] * y + y);
      change(0, r[x] + 1, -y);
      change(1, r[x] + 1, deep[x] * y - y);
    }
    if (opt == 3) {
      printf("%lld\n", query(0, l[x]) * deep[x] + query(1, l[x]));
    }
  }
}

/**————————————————————————————————————————————————*/

bzoj4034 T2 树链剖分&树状数组
2016年03月14日 19:17:23 lych_cys 阅读数：479
版权声明：转载请注明：http://blog.csdn.net/lych_cys https://blog.csdn.net/lych_cys/article/details/50888917
  一种明显的做法是直接树链剖分然后用区间修改区间查询树状数组（我写的这种）或者线段树来维护吧。。这样做是O(Nlog^2N)的。

  但是还可以做到O(NlogN)。首先可以发现它是单点链上查询，那么可以考虑用差分的思想，或者考虑将单点修改直接变成区间修改然后就只用单点简单查询了。

  首先考虑单点修改，这种操作只对它所在的子树中的所有点的答案有影响，也就是所在的子树中每一个点的答案+a，这个可以用dfs序列转化为区间修改。

  然后考虑对子树x的修改，那么对所在的子树中某一个点p，点p的答案+a*(d[p]-d[x]+1)=+a*d[p]+(a-a*d[x])，注意到括号中的部分是常数（即对每一个p来说相同）

  用上面的单点修改即可。然后我们还需要一个数组b（另外一个假设是a）维护每一个点的d[p]被加上了多少次。这样还是区间修改。

  那么查询的答案就是ai+bi*d[i]了，直接上查分的树状数组转化为单点修改前缀查询。O(NlogN)，这个应该是最快的写法了。

  AC代码如下（树链剖分+区间修改区间查询树状数组）：


#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 100005
using namespace std;
 
int n, m, tot, dfsclk, a[N]；
int fst[N], pnt[N<<1], nxt[N<<1]
int bg[N], ed[N];
int fa[N], anc[N], son[N], sz[N];

ll c[2][N];
int read(){
  int x=0,fu=1; char ch=getchar();
  while (ch<'0' || ch>'9'){ if (ch=='-') fu=-1; ch=getchar(); }
  while (ch>='0' && ch<='9'){ x=x*10+ch-'0'; ch=getchar(); }
  return x*fu;
}
void add(int x,int y){
  pnt[++tot]=y; nxt[tot]=fst[x]; fst[x]=tot;
}
void ins(int k,int x,ll t){
  for (; x<=n; x+=x&-x) c[k][x]+=t;
}
ll getsum(int k,int x){
  ll sum=0; for (; x; x-=x&-x) sum+=c[k][x]; return sum;
}
void mdy(int x,int y,ll z){
  ins(0,x,z); ins(0,y+1,-z); ins(1,x,z*(x-1)); ins(1,y+1,-z*y);
}
ll qry(int x,int y){
  return getsum(0,y)*y-getsum(1,y)-getsum(0,x-1)*(x-1)+getsum(1,x-1);
}
void dfs(int x){
  sz[x]=1; int p;
  for (p=fst[x]; p; p=nxt[p]){
    int y=pnt[p];
    if (y!=fa[x]){
      fa[y]=x; dfs(y); sz[x]+=sz[y];
      if (sz[y]>sz[son[x]]) son[x]=y;
    }
  }
}
void divide(int x,int tp){
  bg[x]=++dfsclk; anc[x]=tp; int p;
  if (son[x]) divide(son[x],tp);
  for (p=fst[x]; p; p=nxt[p]){
    int y=pnt[p];
    if (y!=son[x] && y!=fa[x]) divide(y,y);
  }
  ed[x]=dfsclk;
}
int main(){
  n=read(); m=read(); int i,k,x,y; ll ans;
  for (i=1; i<=n; i++) a[i]=read();
  for (i=1; i<n; i++){
    x=read(); y=read(); add(x,y); add(y,x);
  }
  dfs(1); divide(1,1);
  for (i=1; i<=n; i++) mdy(bg[i],bg[i],a[i]);
  while (m--){
    k=read();
    if (k==1){
      x=read(); y=read(); mdy(bg[x],bg[x],(ll)y);
    } else if (k==2){
      x=read(); y=read(); mdy(bg[x],ed[x],(ll)y);
    } else{
      x=read(); ans=0;
      for (; x; x=fa[anc[x]]) ans+=qry(bg[anc[x]],bg[x]);
      printf("%lld\n",ans);
    }
  }
  return 0;
}

by lych

2016.3.14