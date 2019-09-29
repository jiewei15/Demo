
#include<bits/stdc++.h>
#define inc(i,a,b) for(int i = a;i <= b;i++)
#define sub(i,a,b) for(int i = a;i >= b;i--)
#define p_b(x) push_back(x)
using namespace std;
const int maxn = 109;
const int maxk = 10009;
const int maxr = 10009;
const int inf = 0x3f3f3f3f;
int K,N,R,S,D,L,T;
int tot,len;
int minlen[maxn][maxk];
/// minlen[node][fee]数组记录1~node点花费fee时的最短距离
int flag[maxn];
struct edge {
	int s,d,l,t;
	int next;
}e[maxk];
int head[maxn];
void init() {
	tot = 0;len = inf;
	memset(head,-1,sizeof(head));
	memset(flag,0,sizeof(flag));
	flag[1] = 1;
	for(int i = 1;i <= maxn-5;i++)
		for(int j = 0;j < maxk-5;j++)
			minlen[i][j] = inf;
}
void add(int u,int v,int l,int t) {
	++tot;
	e[tot].next = head[u];
	e[tot].s = u;
	e[tot].d = v;
	e[tot].l = l;
	e[tot].t = t;
	head[u] = tot;
}

void dfs(int u = 1,int le = 0,int fe = 0) {
	if(fe > K || le > minlen[u][fe] || le > len) return;
	if(u == N) {len = min(len,le);return;}
	if(le < minlen[u][fe]) {
		for(int v = fe;v <= K;v++)
			minlen[u][v] = le;
		for(int k = head[u];~k;k = e[k].next) {
			int v = e[k].d;
			if(flag[v] == 1) continue;
			flag[v] = 1;
			dfs(v,le+e[k].l,fe+e[k].t);
			flag[v] = 0;
		}
	}
}

int main() {
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	while(cin >> K >> N >> R) {
	init();
	inc(i,1,R) {
		cin >> S >> D >> L >> T;
		add(S,D,L,T);
	}
	dfs();
	if(len == inf) cout << '-1' << endl;
	else cout << len << endl;
	}
	fclose(stdin);
	fclose(stdout);
}
//#include <bits/stdc++.h>
//#define INF 0x3f3f3f3f
//using namespace std;
///// minlen[node][fee]数组记录1~ node 点在 fee 花费时的最短距离
///// 假如搜索到 i 点而花费为 fe 时 le 超过了已记录到的 minlen[i][fe]
///// 则可结束本次搜索
//int s[10005],d[10005],l[10005],t[10005],flag[105];
//int k,n,r,len,minlen[105][10005],first[105],nexti[10005];
//
//void DFS(int i,int le,int fe) {
//    if(fe>k || le>minlen[i][fe] || le>len) return;
// /// 用minlen数组记下 i 点在 fe 花费时的最短距离,若超过则可停止继续搜索了
//
//    if(i==n) {
//        len=min(len,le);
//        //printf("%d\n",len);
//        return ;
//    }
//    else {
//        if(le<minlen[i][fe]) /// 若存在更短的距离 则更新minlen的值
//            for(int j=fe;j<=k;j++)
//                minlen[i][j]=le;
//
//        int in=first[i];
//        while(in!=-1) {
//            if(!flag[d[in]]) {
//                flag[d[in]]=1; /// 避免自环情况
//                DFS(d[in],le+l[in],fe+t[in]);
//                flag[d[in]]=0;
//            }
//            in=nexti[in];
//        } /// 邻接表遍历
//
//    }
//
//}
//int main() {
//    while(~scanf("%d%d%d",&k,&n,&r)) {
//        memset(flag,0,sizeof(flag));
//        for(int i=1;i<101;i++)
//            for(int j=0;j<10001;j++)
//                minlen[i][j]=200000;
//        memset(first,-1,sizeof(first));
//
//        for(int i=1;i<=r;i++) {
//            scanf("%d%d%d%d",&s[i],&d[i],&l[i],&t[i]);
//            nexti[i]=first[s[i]];
//            first[s[i]]=i;
//        } /// 建邻接表 可避免重边引起的错误
//
//        flag[1]=1; len=INF;
//        DFS(1,0,0);
//
//        if(len==INF) printf("-1\n");
//        else printf("%d\n",len);
//    }
//
//    return 0;
//}
//
////#include<cstdio>
////#include<iostream>
////#include<cstring>
////using namespace std;
////struct node {
////	int len[11];
////	int val[11];
////    int num,flag;
////}m[101][101];
////
////int f[101];
////int minlen[101][10001];
////int K,N,R;
////int sum_v=0,sum_l=0,minn=0x3f3f3f3f;
////
////void search(int c) {
////	if(sum_l>minn||sum_v>K||sum_l>=minlen[c][sum_v])
////	return;
////	if(c==N) {
////		if(sum_l<minn)minn=sum_l;
////		return;
////	}
////	else {
////		if(sum_l<minlen[c][sum_v])
////		for(int i=sum_v;i<=K;i++)
////		minlen[c][i]=sum_l;
////	//---------------------------------|
////	for(int i=0;i<=N;i++)
////	if(m[c][i].len[0]!=0)
////	if(f[i]==0&&c!=i&&m[c][i].flag==0) {
////		for(int j=0;j<m[c][i].num;j++) {
////			sum_l+=m[c][i].len[j];
////			sum_v+=m[c][i].val[j];
////			m[c][i].flag=1;
////			f[i]=1;
////			search(i);
////			sum_l-=m[c][i].len[j];
////			sum_v-=m[c][i].val[j];
////			m[c][i].flag=0;
////			f[i]=0;
////		}
////	}
////	//---------------------------------|
////	}
////}
////
////int main() {
////	int s,d,l,t,i,j,k;
////	memset(m,0,sizeof(m));
////	memset(f,0,sizeof(f));
////
////	for(i=0;i<101;i++)
////	for(j=0;j<10001;j++)
////	minlen[i][j]=0x3f3f3f3f;
////
////	scanf("%d%d%d",&K,&N,&R);
////	for(i=1;i<=R;i++) {
////		scanf("%d%d%d%d",&s,&d,&l,&t);
////		m[s][d].len[m[s][d].num]=l;
////		m[s][d].val[m[s][d].num]=t;
////		m[s][d].num++;
////	}
////
////	f[1]=1;
////	search(1);
////
////	if(minn==0x3f3f3f3f)
////		printf("-1\n");
////	else
////		printf("%d\n",minn);
////	return 0;
////}
