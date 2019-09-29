https://www.cnblogs.com/clrs97/p/4944061.html

建立Trie，那么成为答案的串必须满足其终止节点到根路径上没有其它点。

对于Trie上每个节点维护一个bitset，表示哪些字符必须在哪些字符之前。

每到达一个可能成为答案的终止节点，对图进行拓扑排序进行判定。

时间复杂度O(262N+26|S|)。

#include<bits/stdc++.h>
using namespace std;

const int maxn = 30010;
const int maxm = 300030;
int n,cnt,len,st[maxn],en[maxn],fin[maxn],ans;
int tot,son[maxm][26],id[maxm],v[maxm],f[maxm][26];
int g[26][26],d[26],q[30];
char s[maxm],text[maxm];
int x,j,i,k;
void dfs(int x ) {
	if(id[x]) {
		for(i = 0;i < 26;i++)
			for(j = d[i] = 0;j < 26;j++)
				g[i][j] = 0;

		for(i = 0;i < 26;i++)
			for(int j = 0;j < 26;j++)
				if(i != j && (f[x][i] >> j&1))
					g[i][j] = 1, d[j] ++;

		int h = 1, t = 0;
		for(i = 0;i < 26;i++)
			if(!d[i]) q[++t] = i;
		while(h <= t) {
			int x = q[h++];
			for(i = 0;i < 26;i++)
				if(g[x][i])
					if(!(--d[i]))
						q[++t] = i;
		}
		if(t == 26) fin[id[x]] = 1, ans++;
		return;
	}

	for(int i = 0;i < 26;i++)
		if(son[x][i]) {
			int y = son[x][i];
			for(j = 0;j < 26;j++)
				f[y][j] = f[x][j];
			f[y][i] |= v[x];
			dfs(y);
		}
}

int main() {
	scanf("%d",&n);
	for(i = 1;i <= n;i++) {
		scanf("%s",s);
		len = strlen(s);
		st[i] = cnt;
		for(j = x = 0;j < len;x = son[x][k],j++)
			if(!son[x][k=text[cnt++]=s[j]-'a'])
				son[x][k] = ++tot, v[x] |= 1<<k;
		id[x] = i;
		en[i] = cnt;
	}
	dfs(0);
	for(printf("%d\n",ans),i = 1;i <= n;i++)
		if(fin[i]) {
			for(int j = st[i];j < en[i];j++)
				putchar(text[j]+'a');
			puts("");
		}
	return 0;
}


__________________________________________________________________
https://blog.csdn.net/jzq233jzq/article/details/77146093

Trie+拓扑排序——Luogu3065 [USACO12DEC]第一!First!
2017年08月13日 16:45:45 jzq233jzq 阅读数：281
 版权声明：本文为博主原创文章，转载请注明出处http://blog.csdn.net/jzq233jzq https://blog.csdn.net/jzq233jzq/article/details/77146093
题面：Luogu3065 
我们首先考虑一种情况，如果某一字符串的某个前缀是另外一个字符串，这个字符串不可能字典序最小。 
所以我们来考虑相同前缀的问题。如果某一字符串字典序最小，和它同前缀的字符串的相同前缀之后一位字母的大小顺序就可以确定。如果这一系列的关系没有矛盾的话，这个串就可以是最小的，反之不行。 
判断有无矛盾的话我们可以通过建连边跑拓扑排序解决。至于找前缀这种问题，交给Trie树就好了。

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <ctime>
#include <map>
#include <queue>
#include <cstdlib>
#include <string>
#include <climits>
#include <set>
#include <vector>
using namespace std;
bool b[300010];
int n,nedge=0,p[2010],nex[2010],head[2010],rd[2010];
int nxt[300010][26],ans=0,cnt=0,anss[200010];
char s[30010][310];
inline void pre(){
    nedge=0;memset(nex,0,sizeof nex);
    memset(head,0,sizeof head);memset(rd,0,sizeof rd);
}

inline void addedge(int a,int b){
    p[++nedge]=b;nex[nedge]=head[a];head[a]=nedge;
}

inline void insert(int x){
    int len=strlen(s[x]+1),now=0;
    for(int i=1;i<=len;i++){
        int p=s[x][i]-'a';
        if(!nxt[now][p])nxt[now][p]=++cnt;
        now=nxt[now][p];
    }
    b[now]=1;
}

inline bool check(int x){
    int len=strlen(s[x]+1),now=0;
    for(int i=1;i<=len;i++){
        int p=s[x][i]-'a';
        if(b[now])return 0;
        for(int i=0;i<26;i++)if(p!=i&&nxt[now][i])addedge(p+1,i+1),rd[i+1]++;
        now=nxt[now][p];
    }
    return 1;
}

inline bool topo(){
    queue<int>q;for(int i=1;i<=26;i++)if(!rd[i])q.push(i);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int k=head[now];k;k=nex[k])if(rd[p[k]]){
            rd[p[k]]--;if(!rd[p[k]])q.push(p[k]);
        }
    }
    for(int i=1;i<=26;i++)if(rd[i])return 0;
    return 1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        insert(i);
    }
    for(int i=1;i<=n;i++){
        pre();
        if(check(i)&&topo())anss[++ans]=i;
    }
    printf("%d\n",ans);
    for(int i=1;i<=ans;i++)printf("%s\n",s[anss[i]]+1);
    return 0;
}




#include<bits/stdc++.h>
using namespace std;


bool b[300030];
int n,nedge = 0,p[2010],nex[2010],head[2010],rd[2010];
int nxt[300010][26],ans = 0,cnt = 0,anss[200010];
char s[30010][310];


inline void pre() {
	nedge = 0;
	memset(nex,0,sizeof nex);
	memset(head,0,sizeof head);
	memset(rd,0,sizeof rd);
}

inline void addedge(int a,int b) {
	p[++nedge] = b;nex[nedge] = head[a];head[a] = nedge;
}

inline void insert(int x) {/**往trie中加入字符串*/
	int len = strlen(s[x]+1),now = 0;
	for(int i = 1;i <= len;i++) {
		int p = s[x][i] - 'a';
		if(!nxt[now][p]) nxt[now][p] += ++cnt;/**如果trie中的字符串的对应位置没有对应相同的字符，就在trie树中申请一个新节点，分配的地址为cnt*/
		now = nxt[now][p];/*迭代到下个节点*/
	}
	b[now] = 1;/**标记地址为now的节点为一个字符串的终点*/
}

inline bool check(int x) {
	int len  = strlen(s[x] + 1),now = 0;
	for(int i = 1;i <= len;i++) {
		int p = s[x][i] - 'a';
		if(b[now]) return 0;/**如果这个字符串有一个前缀字符串（即有字符串是这个字符串的前缀），那么，这个字符串不可能排在他的前缀字符串的前面*/
		for(int i = 0;i < 26;i++) 
			if(p != i && nxt[now][i]) 
				addedge(p+1,i+1),rd[i+1]++;/**i对应字符节点的入度加1，将这个字符串的字符p设定为比trie中其他字符串对应位i字符的字典序小，加边建图，求topo序，如果图没有环出现就不矛盾*/
		now = nxt[now][p];/**迭代这个字符串的下一个字符*/
	}
	return 1;
}

inline bool topo() {
	queue<int> q;
	for(int i = 1;i <= 26;i++)
		if(!rd[i]) q.push(i);/**将入度为零的节点加入队列*/
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int k = head[now];k;k=nex[k])
			if(rd[p[k]]) {
				rd[p[k]]--;
				if(!rd[p[k]]) q.push(p[k]);
			}
	}
	for(int i = 1;i <= 26;i++) 
		if(rd[i]) return 0;
	return 1;
}

int main() {

	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%s",s[i]+1);
		insert(i);
	}
	for(int i = 1;i <= n;i++) {
		pre();
		if(check(i) && topo()) anss[++ans] = i;
	}
	printf("%d\n",ans);
	for(int i = 1;i <= ans;i++) 
		printf("%s\n",s[anss[i]]+1);
	return 0;
	
}