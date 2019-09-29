#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
#define M 100005
using namespace std;
int n,m;
int father[M];
int rank1[M];
struct tree
{
    int from,to,cose;
    friend bool operator < (tree a,tree b)
    {
        return a.cose>b.cose;
    }
};
priority_queue<tree>q;
vector<int>v[M],w[M];
void getmap()
{
    while(!q.empty())
    q.pop();
    int i,j;
    for(i=1;i<=m;i++)
    {
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    tree e;
    e.from=a;
    e.to=b;
    e.cose=c;
    q.push(e);
    }
}
int find(int son)
{
    return father[son]==son?son:find(father[son]);
}
void unite(int x,int y)
{
    if(x==y)
    return;
    else if(rank1[x]<rank1[y])
    {
        father[x]=y;
    }
    else
    {
        father[y]=x;
        if(rank1[x]==rank1[y])
        rank1[x]++;
    }
}
long long ans1;
void kruskal()
{
    int i;
    for(i=0;i<=n;i++)
    {
        father[i]=i;
        rank1[i]=0;
    }
    while(!q.empty())
    {
        tree p=q.top();
        q.pop();
        int xx,yy;
        xx=find(p.from);
        yy=find(p.to);
        unite(xx,yy);
        if(xx!=yy)
        {
            ans1+=p.cose;
            v[p.from].push_back(p.to);w[p.from].push_back(p.cose);
            v[p.to].push_back(p.from);w[p.to].push_back(p.cose);
        }
    }
}
int u[M];
int countc(int a,int b)
{
    u[a]=1;
    int i;
    for(i=0;i<v[a].size();i++)
    {
        if(v[a][i]!=b)
        {
            u[a]+=countc(v[a][i],a);
        }
    }
    return u[a];
}
long long ss;
void dfs(int a,int fa)
{
for(int i=0;i<v[a].size();i++)
if(v[a][i]!=fa)
{
int ch=v[a][i];
ss+=(long long)(n-u[ch])*u[ch]*w[a][i];
dfs(ch,a);
}
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        ans1=0;
        ss=0;
        getmap();
        kruskal();
        countc(1,0);
        dfs(1,0);
            int i;
        for(int i=1;i<M;i++)
         {
           v[i].clear();
          w[i].clear();
         }
        printf("%lld %.2lf\n",ans1,(ss*2.0)/(1.0*n*(n-1)));
    }
}

