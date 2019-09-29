/**
墨墨购买了一套N支彩色画笔（其中有些颜色可能相同），摆成一排，你需要回答墨墨的提问。
墨墨会像你发布如下指令： 
						1、 Q L R代表询问你从第L支画笔到第R支画笔中共有几种不同颜色的画笔。 
					    2、 R P Col 把第P支画笔替换为颜色Col。

为了满足墨墨的要求，你知道你需要干什么了吗？

Input
第1行两个整数N，M，分别代表初始画笔的数量以及墨墨会做的事情的个数。
第2行N个整数，分别代表初始画笔排中第i支画笔的颜色。
第3行到第2+M行，每行分别代表墨墨会做的一件事情，格式见题干部分。

Output
对于每一个Query的询问，你需要在对应的行中给出一个数字，代表第L支画笔到第R支画笔中共有几种不同颜色的画笔。

Sample Input
6 5
1 2 3 4 5 5
Q 1 4
Q 2 6
R 1 2
Q 1 4
Q 2 6
Sample Output
4
4
3
4
HINT
对于100%的数据，N≤10000，M≤10000，修改操作不多于1000次，所有的输入数据中出现的所有整数均大于等于1且不超过10^6。


--------------------- 
作者：lvzelong2014 
来源：CSDN 
原文：https://blog.csdn.net/lvzelong2014/article/details/76576740?utm_source=copy 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
#include<set>
#define maxn 11005
using namespace std;

int read() {
	char ch = getchar(); int x = 0,f = 1;
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}

char read2() {
	char ch = getchar();
	while(ch != 'Q' && ch != 'R') ch = getchar();
	return ch;
}

int N, n, m, top;
int s[maxn], root[maxn], b[maxn], c[maxn], head[maxn];
set<int> col[maxn];
set<int> ::iterator pre, it, next;
int lowbit(int x) {
	return x&-x;
}

struct Tree {
	int l, r, sum;
}t[maxn * 100];

struct Ques {
	int x, y;
	char ch;
	void init() {
		ch = read2();
		if(ch == 'Q') {x = read(); y = read();}
		else {x = read(); b[++n] = y = read();}
	}
}q[maxn];

void build_tree(int &p, int L, int R) {
	t[p = ++top].sum = 0;
	if(L == R) return ;
	int mid = (L + R) >>1;
	build_tree(t[p].l, L, mid);
	build_tree(t[p].r, mid+1, R);
}

void add_tree(int &cur_p, int pre_p, int pos, int add, int L, int R) {
	t[cur_p = ++top] = t[pre_p];
	t[cur_p].sum += add;
	if(L == R) return ;
	int mid = (L + R) >>1;
	if(pos <= mid) {
		add_tree(t[cur_p].l, t[pre_p].l, pos, add, L, mid);
	}
	else {
		add_tree(t[cur_p].r, t[pre_p].r, pos, add, mid+1, R);
	}
}

void creat_tree(int p, int pos, int add) {
	while(p <= N) {
		int y;
		add_tree(y, s[p], pos, add, 0, n);
		s[p] = y;
		y += lowbit(p);
	}
}

int sum(int p, int L, int R, int k) {
	if(L == R) return t[p].sum;
	int mid = (L + R) >>1;
	if(k <= mid) {
		return sum(t[p].l, L, mid, k);
	}
	else {
		return t[t[p].l].sum + sum(t[p].r, mid+1, R, k);
	} 
}

int query(int pos, int k) {
	int ans = sum(root[pos], 0, n, k);
	for(int i = pos; i; i -= lowbit(i)) {
		ans += sum(s[i], 0, n, k);
	}
	return ans;
}

void init() {
	n = N = read(); m = read();
	for(int i = 1; i <= N; i++) {
		b[i] = c[i] = read();
	} 
	for(int i = 1; i <= m; i++) {
		q[i].init();
	}
	sort(b+1, b+n+1);
	n = unique(b+1, b+n+1) -b -1;
	for(int i = 1;i <= n; i++) {
		col[i].insert(0);
	}
	build_tree(root[0], 0, n);
	for(int i = 1;i <= N; i++) {
		s[i] = root[0];
	}
	for(int i = 1;i <= N; i++) {
		c[i] = lower_bound(b+1, b+n+1, c[i]) -b;
		add_tree(root[i], root[i-1], head[c[i]], 1, 0, n);
		head[c[i]] = i;
		col[c[i]].insert(i);
	}
}

void change(int pos, int nc) {
	nc = lower_bound(b+1, b+n+1, nc) -b;
	int oc = c[pos];
	pre = next = it = col[oc].lower_bound(pos);
	pre--; next++;
	creat_tree(pos, *pre, -1);
	if(next != col[oc].end()) {
		creat_tree(*next, pos, -1);
		creat_tree(*next, *pre, 1);
	}
	col[oc].erase(if);
	col[nc].insert(pos);
	c[pos] = nc;
	pre = next = it = col[nc].lower_bound(pos);
	pre--; next++;
	creat_tree(pos, *pre, 1);
	if(next != col[nc].end()) {
		creat_tree(*next, pos, 1);
		creat_tree(*next, pre, -1);
	}
}

void solve() {
	for(int i = 1;i <= m;i++) {
		if(q[i].ch == 'Q') {
			printf("%d\n",query(q[i].y, q[i].x - 1) -query(q[i].x - 1, q[i].x - 1));
		}
		else {
			change(q[i].x, q[i].y);
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}