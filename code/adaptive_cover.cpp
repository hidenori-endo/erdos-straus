#include <bits/stdc++.h>
using namespace std;
static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
static long long eg(long long a,long long b,long long&x,long long&y){if(!b){x=1;y=0;return a;}long long X,Y,g=eg(b,a%b,X,Y);x=Y;y=X-a/b*Y;return g;}static int invm(int a,int m){long long x,y;eg(a,m,x,y);x%=m;if(x<0)x+=m;return x;}
int main(int argc,char**argv){int LIM=argc>1?atoi(argv[1]):100000000; int KMAX=argc>2?atoi(argv[2]):403;int NMAX=(LIM+KMAX)/4+10;vector<int>spf(NMAX+1);for(int i=2;i<=NMAX;i++)if(!spf[i]){spf[i]=i;if(1LL*i*i<=NMAX)for(long long j=1LL*i*i;j<=NMAX;j+=i)if(!spf[j])spf[j]=i;}vector<bool>comp(LIM+1);for(int i=2;1LL*i*i<=LIM;i++)if(!comp[i])for(long long j=1LL*i*i;j<=LIM;j+=i)comp[j]=1;
map<int,vector<int>> base={{1,{3,7,15}},{121,{3,7,15,19,35,47}},{169,{3,7,11,15,31}},{289,{3,7,11,15,31,47}},{361,{3,7,15,35,59}},{529,{3,7,11,15,31}}};map<int,vector<int>> surv;
auto factors=[&](int C){vector<pair<int,int>>f;while(C>1){int q=spf[C],e=0;while(C%q==0)C/=q,e++;f.push_back({q,e});}return f;};
auto pure=[&](int C,int k){auto f=factors(C);for(auto [q,e]:f)if(jacobi(q%k,k)!=1)return false;return true;};
auto hit=[&](int p,int k){int C=(p+k)/4;auto f=factors(C);vector<char>S(k);S[1%k]=1;for(auto [q,e]:f){vector<int>basev;for(int a=0;a<k;a++)if(S[a])basev.push_back(a);int rr=1;for(int j=1;j<=2*e;j++){rr=1LL*rr*(q%k)%k;for(int a:basev)S[1LL*a*rr%k]=1;}}int t1=(k-invm(4,k))%k,t2=(k-C%k)%k;return S[t1]||S[t2];};
for(int p=5;p<LIM;p+=4){if(comp[p])continue;int h=p%840;if(!base.count(h))continue;bool ok=1;for(int k:base[h])if(!pure((p+k)/4,k)){ok=0;break;}if(ok)surv[h].push_back(p);}vector<int>cands;for(int k=3;k<=KMAX;k+=4)cands.push_back(k);
for(auto &[h,V]:surv){cout<<"== h="<<h<<" survivors="<<V.size()<<" ==\n";int n=V.size();vector<char>alive(n,1);int rem=n;for(int step=0;step<12&&rem;step++){int bk=-1,bc=0;vector<char>bh;for(int k:cands){int c=0;vector<char>hh(n);for(int i=0;i<n;i++)if(alive[i]&&hit(V[i],k))hh[i]=1,c++;if(c>bc){bc=c;bk=k;bh.swap(hh);}}if(bc==0)break;cout<<" step "<<step+1<<" k="<<bk<<" hits="<<bc<<" rem_before="<<rem<<"\n";for(int i=0;i<n;i++)if(alive[i]&&bh[i])alive[i]=0,rem--;}
cout<<" rem="<<rem<<" examples=";int z=0;for(int i=0;i<n&&z<20;i++)if(alive[i])cout<<V[i]<<",",z++;cout<<"\n";}
}
