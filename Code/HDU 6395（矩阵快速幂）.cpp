//https://blog.csdn.net/weixin_39453270/article/details/81661394
#include <bits/stdc++.h>
#define maxn 100005
using namespace std;
const int mod=1e9+7;
typedef long long ll;
struct Marix{
    ll mo[3][3];
    Marix(){
        memset(mo,0,sizeof(mo));
    }
};
Marix mul(Marix a,Marix b){
    Marix c;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                c.mo[i][j]=(c.mo[i][j]+a.mo[i][k]*b.mo[k][j])%mod;
            }
        }
    }
    return c;
}
Marix powmod(Marix a,ll n){//矩阵快速幂模板
    Marix tmp;
    for(int i=0;i<3;i++){
        tmp.mo[i][i]=1;
    }
    while(n){
        if(n&1) tmp=mul(tmp,a);
        n>>=1;
        a=mul(a,a);
    }
    return tmp;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        ll a,b,c,d,p,n;
        scanf("%lld%lld%lld%lld%lld%lld",&a,&b,&c,&d,&p,&n);
        if(n==1){
            printf("%lld\n",a);
            continue;
        }
        if(n==2){
            printf("%lld\n",b);
            continue;
        }
        Marix m;
        m.mo[0][0]=d,m.mo[0][1]=c,m.mo[1][0]=1,m.mo[2][2]=1;
        bool vis=0;
        for(ll i=3;i<=n;){
            if(p/i==0){//倘若当前项大于p了，则直接用矩阵快速幂求解剩下的项
                Marix tmp;
                tmp=m;
                tmp=powmod(tmp,n-i+1);
                ll res=(tmp.mo[0][0]*b+tmp.mo[0][1]*a+tmp.mo[0][2])%mod;
                printf("%lld\n",res);
                vis=1;
                break;
            }//否则，不断的分段求解矩阵的值，并将矩阵的值进行修改
            ll j=min(n,p/(p/i));
            Marix tmp;
            tmp=m;
            tmp.mo[0][2]=p/i;
            tmp=powmod(tmp,j-i+1);
            ll A=(tmp.mo[1][0]*b+tmp.mo[1][1]*a+tmp.mo[1][2])%mod;
            ll B=(tmp.mo[0][0]*b+tmp.mo[0][1]*a+tmp.mo[0][2])%mod;
            a=A,b=B;
            i=j+1;
        }
        if(!vis) printf("%lld\n",b);
    }
    return 0;
}



http://acm.hdu.edu.cn/showproblem.php?pid=6470

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

const int M = 123456789;

mat mul(mat &A, mat & B) {
	mat C(A.size(), vec(B[0].size()));
	for(int i = 0;i < A.size();i++)
		for(int k = 0;k < B.size();k++)
			for(int j = 0;j < B[0].size();j++)
				C[i][j] = (C[i][j] + A[i][k]*B[k][j]%M)%M;
	return C;
}

mat pow(mat A,ll n) {
	mat B(A.size(),vec(A.size()));
	for(int i = 0;i < A.size();i++)
		B[i][i] = 1;
	while(n > 0) {
		if(n & 1) B = mul(B,A);
		A = mul(A,A);
		n >>= 1;
	}
	return B;
}

int main() {
	int T;
	scanf("%d",&T);
	ll n;
	mat A(6, vec(6));
	while(T--) {
		scanf("%lld",&n);
		for(int i = 0;i < 6;i++) 
			for(int j = 0;j < 6;j++) 
				A[i][j] = 0;
		A[0][0] = 1; A[0][1] = 2; A[0][2] = 1;
        A[1][0] = 1;
        A[2][2] = 1; A[2][3] = 3; A[2][4] = 3; A[2][5] = 1;
        A[3][3] = 1; A[3][4] = 2; A[3][5] = 1;
        A[4][4] = 1; A[4][5] = 1;
        A[5][5] = 1;
        A = pow(A, n-2);

        mat B(6,vec(1));
        B[0][0] = 2;
        B[1][0] = 1;
        B[2][0] = 27;
        B[3][0] = 9;
        B[4][0] = 3;
        B[5][0] = 1;
        B = mul(A,B);
        ll ans = B[0][0];
        printf( "%lld\n", ans );
	}
}
