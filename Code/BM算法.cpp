#include<stdio.h>
#include<string.h>
//BM算法：http://www.cnblogs.com/lanxuezaipiao/p/3452579.html#undefined
#define MAX_CHAR 256
#define SIZE 256
#define MAX(x, y) (x) > (y) ? (x) : (y)

void suffix(char *pattern, int m, int suff[]) {
	suff[m - 1] = m;
	int f, g = m - 1;
	for(int i = m - 2;i >= 0;i--) {
		if(i > g && suff[i + m - 1 - f] < i - g)
			suff[i] = suff[i + m - 1 - f];
		else {
			if(i < g) g = i;
			f = i;
			while(g >= 0 && pattern[g] == pattern[g + m - 1 - f])
				--g;
			suff[i] = f - g;
		}
	}
}

/**计算坏字符数组bmBc[]*/
void PreBmBc(char *pattern, int m, int bmBc[]) {
	/**这个计算应该很容易，似乎只需要bmBc[i] = m - 1 - i就行了，
但这样是不对的，因为i位置处的字符可能在pattern中多处出现，而我们
需要的是最右边的位置，这样就需要每次循环判断了，非常麻烦，性能差。
	这里有个小技巧，就是使用字符作为下标而不是位置数字作为下标。
这样只需要遍历一遍即可，这貌似是空间换时间的做法，但如果是纯8位字符
也只需要256个空间大小，而且对于大模式，可能本身长度就超过了256，所
以这样做是值得的（这也是为什么数据越大，BM算法越高效的原因之一）。
*/
	for(int i = 0;i < MAX_CHAR;i++) 
		bmBc[i] = m;
	for(int i = 0;i < m - 1;i++) 
		bmBc[pattern[i]] = m - 1 - i;
}

/**计算好后缀数组bmGs[]*/
void PreBmGs(char *pattern, int m, int bmGs[]) {
	int suff[SIZE];

	//计算后缀数组
	suffix(pattern, m, suff);

	//先全部赋值为m， 包含Case3
	for(int i = 0;i < m;i++) 
		bmGs[i] = m;

	//Case2
	for(int i = m - 1, j = 0;i >= 0;i--) {
		if(suff[i] == i + 1) {
			for(; j < m - i - 1;j++) {
				if(bmGs[j] == m) 
					bmGs[j] = m - i - 1;
			}
		}
	}

	//Case1
	for(int i = 0;i <= m - 2;i++) 
		bmGs[m - 1 - suff[i]] = m - i - 1;
}

void BoyerMoore(char *pattern, int m, char *text, int n) {
	int bmBc[MAX_CHAR], bmGs[SIZE];

	// Preprocessing
	PreBmBc(pattern, m, bmBc);
	PreBmGs(pattern, m, bmGs);

	//Searching
	int i, j = 0;
	while(j <= n - m) {
		//BM算法在移动模式串的时候是从左到右，而进行比较的时候是从右到左的
		for(i = m - 1;i >= 0 && pattern[i] == text[i + j]; i--) ;
		if(i < 0) {
			printf("Find it, the position is %d\n",j);
			j += bmGs[0];
			return ;
		}
		else {
			/**BM算法的精华就在于BM(text, pattern),也就是BM算法当不匹配的时候
		一次性可以跳过不止一个字符。即它不需要对被搜索的字符串中的字符进行逐一比较，
		而会跳过其中某些部分。通常搜索关键字越长，算法速度越快。它的效率来自于这样的事实：
		对于每一次失败的匹配尝试，算法都能够使用这些信息来排除尽可能多的无法匹配的位置。
		即它充分利用待搜索字符串的一些特征，加快了搜索的步骤。
			BM算法实际上包含两个并行的算法（也就是两个启发策略）：
		坏字符算法（bad-character shift）和好后缀算法（good-suffix shift）。
		这两种算法的目的就是让模式串每次向右移动尽可能大的距离（即上面的BM()尽可能大）。
		*/
			j += MAX(bmBc[text[i + j]] - m + i + 1, bmGs[i]);
		}
	}

	printf("No find.\n");
}


int main() {
	char text[256], pattern[256];

	while(~scanf("%s%s",text,pattern)) {
		BoyerMoore(pattern, strlen(pattern), text, strlen(text));
		printf("\n");
	}
	return 0;
}