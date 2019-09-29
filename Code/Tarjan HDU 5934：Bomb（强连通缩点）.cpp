//有向图强连通分量的Tarjan算法:https://www.byvoid.com/zhs/blog/scc-tarjan
//HDU 5934：Bomb（强连通缩点）:https://www.cnblogs.com/fightfordream/p/6093256.html
//hdu 5934 题目:http://acm.hdu.edu.cn/showproblem.php?pid=5934
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<iostream>
using namespace std;
#define inf 0x3f3f3f3f

const int maxn = 1009;

struct Bomb {
    long long x, y, r, c;//炸弹信息:(x,y)坐标，r爆炸半径，c引燃代价
}p[maxn];

int cnt;//dfs时间戳
int num;//缩点后有几个强连通分量
int in[maxn],out[maxn];//in[i],out[i]表示第i个连通分量的入度和出度
int belong[maxn];//表示顶点i在第belong[i]个强连通分量里
int vis[maxn];//表示顶点是否在栈里
int dfn[maxn];//DFN(u)为节点u搜索的次序编号(时间戳)
int low[maxn];//Low(u)为u或u的子树能够追溯到的最早的栈中节点的次序号
/**
Low(u)=Min
{
    DFN(u),
    Low(v),(u,v)为树枝边，u为v的父节点
    DFN(v),(u,v)为指向栈中节点的后向边(非横叉边)
}
*/

vector<int> G[maxn];
stack<int> S;

void init() {
    cnt = num = 0;
    while(!S.empty()) S.pop();
    memset(vis, 0 ,sizeof(vis));
    memset(dfn, 0 ,sizeof(dfn));
    memset(belong,0,sizeof(belong));
    memset(in, 0, sizeof(in));
    memset(out ,0 ,sizeof(out));
}

bool check(int u,int v) {
    int t = (p[u].x - p[v].x) * (p[u].x - p[v].x);
    int d = (p[u].y - p[v].y) * (p[u].y - p[v].y);
    return 1LL * (t + d) <= 1LL * (p[u].r * p[u].r);
}


/**
	Tarjan算法是基于对图深度优先搜索的算法，每个强连通分量为搜索树中的一棵子树。
搜索时，把当前搜索树中未处理的节点加入一个堆栈，回溯时可以判断栈顶到栈中的节点
是否为一个强连通分量。
*/

/*
tarjan(u)
{
    DFN[u]=Low[u]=++Index                      // 为节点u设定次序编号和Low初值
    Stack.push(u)                              // 将节点u压入栈中
    for each (u, v) in E                       // 枚举每一条边
        if (v is not visted)               // 如果节点v未被访问过
            tarjan(v)                  // 继续向下找
            Low[u] = min(Low[u], Low[v])
        else if (v in S)                   // 如果节点v还在栈内
            Low[u] = min(Low[u], DFN[v])
    if (DFN[u] == Low[u])                      // 如果节点u是强连通分量的根
        repeat
            v = S.pop                  // 将v退栈，为该强连通分量中一个顶点
            print v
        until (u== v)
}
*/
void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    S.push(u);
    vis[u] = 1;
    for(auto& v : G[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);//Low(v),(u,v)为树枝边，u为v的父节点
        }
        else if(vis[v])
            low[u] = min(low[u], dfn[v]);//DFN(v),(u,v)为指向栈中节点的后向边(非横叉边)
    }
    if(dfn[u] == low[u]) {//当DFN(u)=Low(u)时，以u为根的搜索子树上所有节点是一个强连通分量
            ++num;
            int v;
        do{
            v = S.top();
            S.pop();
            belong[v] = num;
            vis[v] = 0;
        }while(u != v);
    }
}

int main() {
    int T, cas = 0;
    scanf("%d",&T);
    while(T--) {
        int n;
        scanf("%d",&n);
        init();
        for(int i = 1;i <= n;i++) {
            scanf("%lld%lld%lld%lld",&p[i].x,&p[i].y,&p[i].r,&p[i].c);
            G[i].clear();
        }
        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= n;j++) {
                if(i != j && check(i,j)) G[i].push_back(j);
            }
        }
        for(int i = 1;i <= n;i++) {
            if(!dfn[i]) tarjan(i);
        }
        for(int u = 1;u <= n;u++) {
            for(auto& v : G[u]) {
                if(belong[u] != belong[v]) {
                    out[belong[u]] ++;
                    in[belong[v]] ++;
                }
            }
        }
        long long ans = 0;
        for(int i = 1;i <= num; i++) {
            if(in[i] == 0) {
                int mi = inf;
                for(int j = 1;j <= n;j++) {
                    if(belong[j] == i) {
                        mi = min(mi, p[j].c);
                    }
                }
                ans += mi;
            }
        }
        printf("Case #%d: %lld\n",++cas,ans);
    }
    return 0;
}

