#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<cstring>
#define maxn 11005
#define lowbit (x&(-x))
using namespace std;

int N, n, m, top;
int s[maxn], rt[maxn], b[maxn], c[maxn], head[maxn];
set<int> col[maxn];
set<int> ::itreator pre, it, next;

struct Tree {
	int l, r, sum;
}t[maxn * 100];

struct Ques {
	int x, y;
	char ch;
	void init() {
		scanf("%c",&ch);
		if(ch == 'Q') {
			scanf("%d%d",&x,&y);
		}
		else {
			scanf("%d%d",&x,&y);
			b[++n] = y;
		}
	}
}q[maxn];

void init() {
	scanf("%d%d",&n,&m);
	N = n;
	for(int i = 1;i <= N;i++) {
		scanf("%d",&c[i]);
		b[i] = c[i];
	}
	for(int i = 1;i <= m;i++) {
		q[i].init();
	}

}

int main() {
	init();
}