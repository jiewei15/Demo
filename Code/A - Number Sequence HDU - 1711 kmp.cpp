#include<stdio.h>
const int MAXN = 10010;

int a[MAXN*100], b[MAXN];
int len1, len2;
int next[MAXN];

void getnext() {
	int i = 0, j = -1;
	next[i] = j;
	while(i < len2) {
		if(j == -1 || b[i] == b[j]) {
			i++, j++;
			next[i] = j;
		}
		else j = next[j];
	}
}

int kmp() {
	getnext();
	int i = 0, j = 0;
	while(i < len1) {
		if(j == -1 || a[i] == b[j]) {
			i++, j++;
			if(j == len2) return i - j + 1;
		}
		else j = next[j];
	}
	return -1;
}

int main() {
	int T;
	int N, M;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&N,&M);
		for(int i = 0;i < N;i++) scanf("%d",&a[i]);
		for(int i = 0;i < M;i++) scanf("%d",&b[i]);
		len1 = N, len2 = M;
		printf("%d\n",kmp());
	}
	return 0;
}