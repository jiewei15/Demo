https://blog.csdn.net/qq_38329396/article/details/77412150
可并堆-STL-pbds详解
2017年08月19日 14:25:35 玄学家OIer 阅读数：1501
 版权声明：本文为博主原创文章，未经博主允许不得转载。	https://blog.csdn.net/qq_38329396/article/details/77412150
对于堆的合并，我们首先想到的是朴素的nlogn出堆之后nlogn入堆。实质上，有一种更为高效的数据结构——可并堆。即为在保证堆顶极值的前提下实现logn的时间合并两个堆。

与普通堆相比，左偏树的每个结点多了一个距离值NPL(Null Path Length)即该结点一直向右儿子走，到达空结点的距离。基于NPL，我们便可以发现，交换变得有序了：在保证了左儿子NPL大于右儿子NPL的时候，效率有所提升。 
首先，如果左子树为空，那么把左右交换必然不会使右子树变高，所以效率提高。 
第二，如果左子树的NPL比较小，那么交换后必然使右子树的高度变小，所以效率提高。 
其他方面大体和堆相同。 
然而这并不是我要说的主题，万能的C++给了我们神奇的STL，什么可并堆统统都给你封装好了吗~ 
实现代码如下

#include<cstdio> 
#include<algorithm> 
#include<ext/pb_ds/assoc_container.hpp> 
#include<ext/pb_ds/priority_queue.hpp> 
//pb_ds库中的优先队列，支持合并
#define LOL int, less<int>, binomial_heap_tag 
using namespace std; 
using namespace __gnu_pbds; //使其名称空间可用
const int MAXN=1e5+5; 
__gnu_pbds::priority_queue<LOL> q1[MAXN]; //不打前面那串会和std下的优先队列混淆
int n,m,x,y; 
int f[MAXN]; //记录是否在同一集合，并查集实现
int fd(int x){ 
    if(x==f[x]) return f[x]; 
    else return f[x]=fd(f[x]); 
} 
int main(){ 
    scanf("%d",&n); 
    for(register int i=1;i<=n;++i){ 
        scanf("%d",&x); 
        q1[i].push(x); 
        f[i]=i; 
    } 
    scanf("%d",&m); 
    for(register int i=1;i<=m;++i){ 
        scanf("%d%d",&x,&y); 
        int fx=fd(x),fy=fd(y); 
        if(fx==fy){ 
            printf("-1\n"); 
            continue; 
        } 
        int xa=q1[fx].top(); 
        q1[fx].pop(); 
        q1[fx].push(xa/2); 
        int xb=q1[fy].top(); 
        q1[fy].pop(); 
        q1[fy].push(xb/2); 
        q1[fy].join(q1[fx]); //合并的关键操作，join函数
        f[fx]=fy; 
        int xc=q1[fd(fx)].top(); 
        printf("%d\n",xc); 
    } 
    return 0; 
}


https://www.cnblogs.com/Kv-Stalin/p/8857600.html
