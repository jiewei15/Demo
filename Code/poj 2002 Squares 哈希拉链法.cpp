/**	题意：在平面内给出 n 个点，问你这些点一共能组成几个不相等的正方形？
输入有多组测试数据，每组测试数据的第一行是一个整数 n，表示 n 个点，接下来
行，每行两个整数，表示一个坐标点，这 n 个点都不相同。（1<=n<=1000）
	思路：直接枚举四个点判断能否组成正方形肯定超时，不可取。
	普遍的做法是先枚举两个点，通过数学公式得到另外 2 个点，使得这四个点能够成正
方形。然后检查散点集中是否存在计算出来的那两个点，若存在，说明有一个正方形。
	先按他们的坐标从小到大排序，x 优先，之后是 y，这一步只是从插入顺序上优化一
下之后的哈希查找，哈希函数使用取余法，把 x+y 和除 MOD 取余。

枚举正方形最左边的两点坐标，然后计算出另外两点。证明就不具体展开了，可以
参考下图，已知两个点，然后做出两个全等三角形。之后就得出结论(x1+|y1-y2|, y1+|x1-
x2|),(x2+|y1-y2|,y2+|x1-x2|) 。当然这只是一种情况，其他情况类似。
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

const int M = 1031;
struct Point {
	int x, y;
};
Point p[1024];
int n;
int hash[M + 8], next[1024];

bool cmp(const Point& a,const Point& b) {
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

int hashcode(const Point &tp) {
	return abs(tp.x + tp.y) % M;
}

bool hash_search(const Point &tp) {
	int key = hashcode(tp);
	for(int i = hash[key]; ~i;i = next[i]) {
		if(tp.x == p[i].x && tp.y == p[i].y)
			return true;
	}
}

void insert_hash(int i) {
	int key = hashcode(p[i]);
	next[i] = hash[key];
	hash[key] = i;
}

int main() {
	Point p3, P4;
	int dx, dy, ans;
	while(~scanf("%d",&n)) {
		memset(hash,-1,sizeof(hash));
		memset(next,-1,sizeof(next));
		for(int i = 0;i < n;i++) { 
			scanf("%d%d",&p[i].x,&p[i].y);
		}
		sort(p,p+n,cmp);
		for(int i = 0;i < n;i++) {
			insert_hash(i);
		}

		ans = 0;
		for(int i = 0;i < n;i++) {
			for(int j = i+1;j < n;j++) {
				int dx = p[j].x - p[i].x;
				int dy = p[j].y - p[i].y;
				p3.x = p[i].x + dy;
				p3.y = p[i].y - dx;
				if(hash_search(p3)) {
					p4.x = p[j].x + dy;
					p4.y = p[j].y - dx;
					if(hash_search(p4))
						ans ++;
				}
			}
		}
		printf("%d\n",ans/2);
	}
	return 0;
}