#include <bits/stdc++.h>
using namespace std;
static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
int main(int argc,char**argv){int LIM=argc>1?atoi(argv[1]):20000000; int NMAX=(LIM+59)/4+5;
 vector<int> spf(NMAX+1); for(int i=2;i<=NMAX;i++)if(!spf[i]){spf[i]=i;if(1LL*i*i<=NMAX)for(long long j=1LL*i*i;j<=NMAX;j+=i)if(!spf[j])spf[j]=i;}
 vector<bool> comp(LIM+1); for(int i=2;1LL*i*i<=LIM;i++)if(!comp[i])for(long long j=1LL*i*i;j<=LIM;j+=i)comp[j]=1;
 map<int,vector<int>> ks={{1,{3,7,15}},{121,{3,7,15,19,35,47}},{169,{3,7,11,15,31}},{289,{3,7,11,15,31,47}},{361,{3,7,15,35,59}},{529,{3,7,11,15,31}}};
 map<int,long long> hard,surv; map<int,vector<int>> first;
 auto pure=[&](int C,int k){int x=C; while(x>1){int q=spf[x]; if(jacobi(q%k,k)!=1)return false; while(x%q==0)x/=q;} return true;};
 for(int p=5;p<LIM;p+=4){if(comp[p])continue;int h=p%840;if(!ks.count(h))continue;hard[h]++;bool ok=true;for(int k:ks[h]){int C=(p+k)/4;if(!pure(C,k)){ok=false;break;}}if(ok){surv[h]++;if(first[h].size()<20)first[h].push_back(p);}}
 long long H=0,S=0; for(auto [h,v]:ks){H+=hard[h];S+=surv[h];cout<<"h="<<h<<" hard="<<hard[h]<<" allpure="<<surv[h]<<" first=";for(int p:first[h])cout<<p<<",";cout<<"\n";} cout<<"TOTAL hard="<<H<<" allpure="<<S<<" ratio="<<setprecision(8)<<(H?double(S)/H:0)<<"\n";
}
