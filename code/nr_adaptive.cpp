#include <bits/stdc++.h>
using namespace std;
static long long modpow(long long a,long long e,long long m){long long r=1;for(;e;e>>=1,a=(__int128)a*a%m)if(e&1)r=(__int128)r*a%m;return r;}
static int legendre(long long p,int r){int x=p%r;if(x==0)return 0;long long z=modpow(x,(r-1)/2,r);return z==1?1:-1;}
static bool isprime64(uint64_t n){if(n<2)return false;for(uint64_t p:{2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}){if(n%p==0)return n==p;}uint64_t d=n-1,s=0;while(!(d&1))d>>=1,s++;auto mul=[&](uint64_t a,uint64_t b){return (__uint128_t)a*b%n;};auto pw=[&](uint64_t a,uint64_t e){uint64_t z=1;while(e){if(e&1)z=mul(z,a);a=mul(a,a);e>>=1;}return z;};for(uint64_t a:{2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}){if(a%n==0)continue;uint64_t x=pw(a%n,d);if(x==1||x==n-1)continue;bool ok=0;for(uint64_t u=1;u<s;u++){x=mul(x,x);if(x==n-1){ok=1;break;}}if(!ok)return false;}return true;}
static vector<int> primes_upto(int B){vector<bool>c(B+1);vector<int>p;for(int i=2;i<=B;i++)if(!c[i]){p.push_back(i);if(1LL*i*i<=B)for(long long j=1LL*i*i;j<=B;j+=i)c[j]=1;}return p;}
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static set<int> P(int k,long long x){int a=x%k;if(a<0)a+=k;return {1,a,(int)(1LL*a*a%k)};}
static set<int> mulset(int k,const set<int>&A,const set<int>&B){set<int>C;for(int a:A)for(int b:B)C.insert(1LL*a*b%k);return C;}
static set<int> seedbox(int k,int s){set<int>D={1};for(int q:{2,3,5,7})if(s%q==0)D=mulset(k,D,P(k,q));return D;}
static bool minimal_hit(long long p,int r,int &kout){long long N=(p+3)/4;int j=(int)((r-(N%r))%r);int k=4*j+3;kout=k; long long C=N+j; if(C%r)return false; int s=std::gcd(210LL,C);if(s%r==0)return false; long long m=C/(1LL*s*r);auto B=mulset(k,seedbox(k,s),P(k,r));B=mulset(k,B,P(k,m));int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k);return B.count(t1)||B.count(t2);}
int main(int argc,char**argv){long long LIM=argc>1?atoll(argv[1]):100000000;int RB=argc>2?atoi(argv[2]):1000;auto rs=primes_upto(RB);long long hard=0,leastHit=0,anyHit=0;map<int,long long> leastR, firstHitR;vector<tuple<long long,int,int,int>> bad;
for(long long t=0;;t++){long long p=840*t+1;if(p>=LIM)break;if(!isprime64(p))continue;hard++;int lr=0,lk=0,fr=0,fk=0;for(int r:rs){if(r<=7||p==r)continue;if(legendre(p,r)!=-1)continue;if(!lr){lr=r;int kk;bool h=minimal_hit(p,r,kk);lk=kk;if(h){leastHit++;fr=r;fk=kk;break;}}int kk;if(minimal_hit(p,r,kk)){fr=r;fk=kk;break;}}
if(lr)leastR[lr]++;if(fr){anyHit++;firstHitR[fr]++;}else if(bad.size()<50)bad.push_back({p,lr,lk,fr});}
cerr<<"hard="<<hard<<" leastHit="<<leastHit<<" anyHit<="<<RB<<"="<<anyHit<<" bad="<<hard-anyHit<<"\n";cout<<"# least nonresidue r distribution\n";for(auto [r,c]:leastR)cout<<r<<" "<<c<<"\n";cout<<"# first adaptive-hit r distribution\n";for(auto [r,c]:firstHitR)cout<<r<<" "<<c<<"\n";cout<<"# bad examples\n";for(auto [p,r,k,f]:bad)cout<<p<<" least_r="<<r<<" k="<<k<<"\n";}
