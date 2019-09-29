#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define LL long long
#define inc(i,j,k) for(int i=j;i<=k;i++)
#define dec(i,j,k) for(int i=j;i>=k;i--)
#define gcd(i,j) __gcd(i,j)
#define mem(i,j) memset(i,j,sizeof(i))
const int N=2e5+5;

int rd, dfn[2][15][50][50];
int fx, tot, a[15];
LL dp[2][15][50][50];
// dp[f][w][s][m]
// f为1说明不是上界 此时为第w位数 
// 剩下的数位总和为s 此时的数位总和%f(x)为m

LL DFS(int f,int w,int s,int m) {
    if(w==0) return (s==0&&m==0);
    // 所有位都枚举过了则w=0
    // 所有数位总和为fx则s=0
    // x%fx==0则m=0
    if(dfn[f][w][s][m]==rd) return dp[f][w][s][m];
    dfn[f][w][s][m]=rd;
    LL res=0LL;
    int l=max(0,s-9*(w-1)), r=min((f ? 9:a[w]),s);
    for(int i=l;i<=r;i++) // 枚举当前位的数
        res+=DFS(f|(i<a[w]),w-1,s-i,(m*10+i)%fx);
    // 之前不是上界 或 当前位不是上界 则到目前为止都不达上界
    // 位数-1 剩余数位总和需减去当前位的数 更新余数
    return dp[f][w][s][m]=res;
}

LL solve(int x) {
    mem(dp,0); mem(dfn,0);
    int tot=0;
    while(x) { a[++tot]=x%10; x/=10; }
    int all=tot*9;
    LL res=0LL;
    for(fx=1;fx<=all;fx++) // 枚举所有数位总和
        ++rd, res+=DFS(0,tot,fx,0);
    //printf("%lld\n",res);
    return res;
}

int main()
{
    int _; scanf("%d",&_);
    inc(i,1,_) {
        int l,r; scanf("%d%d",&l,&r); rd=0;
        printf("Case %d: ",i);
        printf("%lld\n",solve(r)-solve(l-1));
    }

    return 0;
}

设f[len][x][k]表示长度为len，首位为x，交错和为k的数之和，g[len][x][k]表示长度为len，首位为x，交错和为k的数的个数。
然后转移比较简单自己歪歪或看我的code，询问时注意：rep(i,0,len-2) rep(j,1,9) (res+=f[i][j][k+200])%=MOD;
#include<cstdio>
#include<cctype>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define rep(i,s,t) for(int i=s;i<=t;i++)
#define dwn(i,s,t) for(int i=s;i>=t;i--)
#define ren for(int i=first[x];i!=-1;i=next[i])
using namespace std;
inline int read() {
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}
typedef long long ll;
ll f[20][10][410],g[20][10][410],xp[20];
const int MOD=1000000007;
void init() {
    rep(i,0,9) f[0][i][i+200]=i,g[0][i][i+200]=1;
    xp[0]=1;
    rep(len,1,19) {
        xp[len]=(xp[len-1]*10)%MOD;
        rep(k,-200,200) rep(x,0,9) rep(y,0,9) if(x-k>=-200&&x-k<=200) {
            f[len][x][x-k+200]+=f[len-1][y][k+200]+(g[len-1][y][k+200]*(xp[len]*x))%MOD;
            (g[len][x][x-k+200]+=g[len-1][y][k+200])%=MOD;
            f[len][x][x-k+200]%=MOD;
        }
    }
}
int bit[20],len,k;
ll cal(ll x) {
    if(x<=0) return 0;
    ll res=0,cur2=0;int cur=0,c=0;len=0;
    while(x) bit[len++]=x%10,x/=10;
    rep(i,0,len-2) rep(j,1,9) (res+=f[i][j][k+200])%=MOD;
    dwn(i,len-1,0) {
        c^=1;
        rep(j,0,bit[i]-1) {
            if(!j&&i==len-1) continue;
            if(c) (res+=f[i][j][k-cur+200]+g[i][j][k-cur+200]*cur2)%=MOD;
            else (res+=f[i][j][cur-k+200]+g[i][j][cur-k+200]*cur2)%=MOD;
        }
        if(c) cur+=bit[i];
        else cur-=bit[i];
        (cur2+=bit[i]*xp[i])%=MOD;
    }
    return res;
}
int main() {
    init();
    ll l,r;
    scanf("%lld%lld",&l,&r);k=read();
    printf("%lld\n",(cal(r+1)-cal(l)+MOD)%MOD);
    return 0;
}

数位dp入门模板
https://blog.csdn.net/wust_zzwh/article/details/52100392
typedef long long ll;
int a[20];
ll dp[20][state];//不同题目状态不同
ll dfs(int pos,/*state变量*/,bool lead/*前导零*/,bool limit/*数位上界变量*/)//不是每个题都要判断前导零
{
    //递归边界，既然是按位枚举，最低位是0，那么pos==-1说明这个数我枚举完了
    if(pos==-1) return 1;/*这里一般返回1，表示你枚举的这个数是合法的，那么这里就需要你在枚举时必须每一位都要满足题目条件，也就是说当前枚举到pos位，一定要保证前面已经枚举的数位是合法的。不过具体题目不同或者写法不同的话不一定要返回1 */
    //第二个就是记忆化(在此前可能不同题目还能有一些剪枝)
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
    /*常规写法都是在没有限制的条件记忆化，这里与下面记录状态是对应，具体为什么是有条件的记忆化后面会讲*/
    int up=limit?a[pos]:9;//根据limit判断枚举的上界up;这个的例子前面用213讲过了
    ll ans=0;
    //开始计数
    for(int i=0;i<=up;i++)//枚举，然后把不同情况的个数加到ans就可以了
    {
        if() ...
        else if()...
        ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的
        /*这里还算比较灵活，不过做几个题就觉得这里也是套路了
        大概就是说，我当前数位枚举的数是i，然后根据题目的约束条件分类讨论
        去计算不同情况下的个数，还有要根据state变量来保证i的合法性，比如题目
        要求数位上不能有62连续出现,那么就是state就是要保存前一位pre,然后分类，
        前一位如果是6那么这意味就不能是2，这里一定要保存枚举的这个数是合法*/
    }
    //计算完，记录状态
    if(!limit && !lead) dp[pos][state]=ans;
    /*这里对应上面的记忆化，在一定条件下时记录，保证一致性，当然如果约束条件不需要考虑lead，这里就是lead就完全不用考虑了*/
    return ans;
}
ll solve(ll x)
{
    int pos=0;
    while(x)//把数位都分解出来
    {
        a[pos++]=x%10;//个人老是喜欢编号为[0,pos),看不惯的就按自己习惯来，反正注意数位边界就行
        x/=10;
    }
    return dfs(pos-1/*从最高位开始枚举*/,/*一系列状态 */,true,true);//刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位视为0嘛
}
int main()
{
    ll le,ri;
    while(~scanf("%lld%lld",&le,&ri))
    {
        //初始化dp数组为-1,这里还有更加优美的优化,后面讲
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}



https://ac.nowcoder.com/acm/contest/view-submission?submissionId=40466856


#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define N 11
#define int long long
using namespace std;

inline void rd(int &x) {
    x = 0;int w = 0;char ch = 0;
    while(!isdigit(ch)) w |= ch == '-',ch = getchar();
    while(isdigit(ch)) x = (x<<3)+(x<<1)+(ch^48),ch = getchar();
    x = w?-x:x;
}

int len,num[N];
int L[55],R[55],mod,ans[55];
int f[N][82][82];

int dp(int now,int sum,int m,int ok) {
    if(!now) return sum==mod and !m;
    if(ok and ~f[now][sum][m]) return f[now][sum][m];
    int lim = (ok ? 9 : num[now]),t=0;
    for(int i = 0;i <= lim;i++)
        t += dp(now-1,sum+i,(m*10+i)%mod,ok | (i<lim));
    if(ok) return f[now][sum][m] = t;
    return t;
}

int solve(int n) {
    for(len = 0;n;num[++len] = n%10,n /= 10);
    return dp(len,0,0,0);
}

int T,tot;
void work() {
    for(mod = 1;mod < 82;mod++) {
        memset(f,-1,sizeof f);
        for(int i = 1;i <= T;i++)
            ans[i] += solve(R[i]) - solve(L[i]-1);
    }
    for(int i = 1;i <= T;i++)
        printf("Case %lld: %lld\n",++tot,ans[i]);
}

signed main() {
    cin>>T;
    for(int i = 1;i <= T;i++)
        cin>>L[i]>>R[i];
    work();
}


#include<cstdio>
const int N=500010,P=1000000007;
int n,i,j,ans,a[N],l[N],v[N];
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int main(){
  scanf("%d",&n);
  for(i=1;i<=n;i++)
    scanf("%d",&a[i]);
  for(i=1;i<=n;i++)
    for(v[i]=a[i],j=l[i]=i; j; j=l[j]-1){
        v[j] = gcd(v[j],a[i]);
        while(l[j]>1 && gcd(a[i],v[l[j]-1]) == gcd(a[i],v[j]))
            l[j] = l[l[j]-1];
        ans=(1LL*v[j]*(j-l[j]+1)+ans)%P;
  }
  printf("%d",ans);
}


#include<bits/stdc++.h>
using namespace std;
int a[20];
int dp[20][2];
int dfs(int pos,int pre,int sta,bool limit) {
    if(pos == -1) 
        return 1;
    if(!limit && dp[pos][sta] != -1) 
        return dp[pos][sta];
    int up = limit ? a[pos]:9;
    int tmp = 0;
    for(int i = 0;i <= up;i++) {
        if(pre == 6 && i == 2)
            continue;
        if(i == 4) 
            continue;
        tmp += dfs(pos-1, i, i == 6, limit && i == a[pos]);
    }
    if(!limit) 
        dp[pos][sta] = tmp;
    return tmp;
}
int solve(int x) {
    int pos = 0;
    while(x) {
        a[pos++] = x%10;
        x /= 10;
    }
    return dfs(pos-1,-1,0,true);
}
int main() {
    int le,ri;
    while(~scanf("%d%d",&le,&ri) && le+ri) {
        memset(dp,-1,sizeof(dp));
        cout<<solve(ri) - solve(le-1)<<endl;
    }
    return 0;
}



/**
 *    author:  tourist
 *    created: 06.04.2019 12:41:49       
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<long long> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  int m;
  cin >> m;
  vector<long long> b(m);
  for (int i = 0; i < m; i++) {
    long long foo, bar;
    cin >> foo >> bar;
    b[i] = bar - foo + 1;
  }
  vector<pair<long long, int>> events;
  for (int i = 0; i < n - 1; i++) {
    events.emplace_back(a[i + 1] - a[i], -1);
  }
  for (int i = 0; i < m; i++) {
    events.emplace_back(b[i], i); 
  }
  sort(events.begin(), events.end());
  long long ans = 0;
  long long T = 0;
  long long active = n;
  vector<long long> res(m);
  for (auto& e : events) {
    ans += (e.first - T) * active;
    T = e.first;
    if (e.second == -1) {
      active--;
    } else {
      res[e.second] = ans;
    }
  }
  for (int i = 0; i < m; i++) {
    if (i > 0) {
      cout << " ";
    }
    cout << res[i];
  }
  cout << '\n';
  return 0;
}