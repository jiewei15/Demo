#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

const int maxn = 1505;

map<int,int> linker;
map<int,int> used;
vector<int> mp[maxn];
int uN;


int prime(int n) {
	if(n <= 1) return 0;
	if(n == 2) return 1;
	if(n%2 == 0) return 0;
	int  upperBound = n/2;
	for(int k = 3;k <= upperBound;k += 2) {
		upperBound = n/k;
		if(n%k == 0) return 0;
	}
	return 1;
}

bool dfs(int u) {//寻找从k出发的对应项出的可增广路
	for(int i = 0;i < mp[u].size();i++) {//从邻接表中列举k能关联到顶点j
		if(!used[mp[u][i]]) {//j不在增广路上
			used[mp[u][i]] = 1;//把j加入增广路
			if(linker[mp[u][i]] == 0 || dfs(linker[mp[u][i]])) {//j是未盖点 或者 从j的对应项出发有可增广路
				linker[mp[u][i]] = u;//修改j的对应项为k
				return true;//则从k的对应项出有可增广路,返回true
			}
		}
	}
	return false;//则从k的对应项出没有可增广路,返回false
}


int hungary() {
	int res = 0;
	linker.clear();
	for(int u = 1;u <= uN;u++) {//从i的对应项出有可增广路
		used.clear();
		if(dfs(u)) res++;//匹配数++
	}
	return res;//匹配数
}


int main() {
	int T, cas = 0;
	scanf("%d",&T);
	while(T--) {
		int n, s;
		scanf("%d%d",&n,&s);
		if(n > s) swap(n, s);
		int p = 0;
		for(int i = s+1;i <= s+n;i++) {
			if(prime(i)) {
				p++;
				if(p >= 2) break;
			}
		}
		printf("Case #%d: ",++cas);
		if(p >= 2) {
			printf("No\n");
			continue;
		}
		for(int i = s+1;i <= s+n;i++) {
			for(int j = 1;j <= n;j++) {
				if(i%j == 0) 
					mp[j].push_back(i);
			}
		}
		uN = n;
		int hh = hungary();
		if(hh == n) 
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}