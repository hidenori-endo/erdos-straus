// min_hit_k.cpp -- survivor について exact box Div(C_k^2) が hit する最小 shift k を求める。
// 非 survivor は証明済み定理により k in {3,7,15}(class により 19..59) で hit するので、
// 最小 hit shift の最大値は survivor 上で達成される。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int jacobi(ll a,ll n){a%=n;if(a<0)a+=n;int r=1;while(a){while(!(a&1)){a>>=1;ll m=n&7;if(m==3||m==5)r=-r;}swap(a,n);if((a&3)==3&&(n&3)==3)r=-r;a%=n;}return n==1?r:0;}
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):100000000; int KMAX=argc>2?atoi(argv[2]):4003;
  vector<int> HS={1,121,169,289,361,529};
  map<int,vector<int>> AT={{1,{0,1,3}},{121,{0,1,3,4,8,11}},{169,{0,1,2,3,7}},
    {289,{0,1,2,3,7,11}},{361,{0,1,3,8,14}},{529,{0,1,2,3,7}}};
  ll Nmax=LIM/4+KMAX+32; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> psmall; for(int i=2;i<50000;i++) if(spf[i]==i) psmall.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(int q:psmall){ if(1LL*q*q>n)break; if(n%q==0) return false;} return true; };
  vector<ll> divs; divs.reserve(1<<18);
  map<int,ll> minkHist; ll surv=0, unresolved=0; vector<pair<ll,int>> big;
  map<int,int> maxByDec; map<int,ll> nByDec;
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    ll N=(p+3)/4; bool cand=true;
    for(int j:AT[h]){ ll c=N+j; while(c>1){int q=spf[c];while(c%q==0)c/=q; if(jacobi(q,p)==-1){cand=false;break;}} if(!cand)break;}
    if(!cand)continue; surv++;
    int mk=-1;
    for(int k=3;k<=KMAX;k+=4){ ll C=(p+k)/4; if((p+k)%4) continue; ll c=C;
      divs.clear(); divs.push_back(1);
      while(c>1){int q=spf[c];int a=0;while(c%q==0){c/=q;a++;} size_t sz=divs.size();ll pw=1;
        for(int e=1;e<=2*a;e++){pw*=q;for(size_t i2=0;i2<sz;i2++)divs.push_back(divs[i2]*pw);} }
      int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k); bool hit=false;
      for(ll d:divs){int rr=(int)(d%k); if(rr==t1||rr==t2){hit=true;break;}}
      if(hit){mk=k;break;} }
    if(mk<0){unresolved++; if(big.size()<40)big.push_back({p,-1});}
    else { minkHist[mk]++; if(mk>=100&&big.size()<40) big.push_back({p,mk}); }
    int d=0;ll q2=p;while(q2>=10){q2/=10;d++;} maxByDec[d]=max(maxByDec.count(d)?maxByDec[d]:-1,mk); nByDec[d]++;
   } if(!any)break; }
  printf("LIM=%lld KMAX=%d survivors=%lld unresolved=%lld\n\n",LIM,KMAX,surv,unresolved);
  printf("# survivor の最小 hit shift k の分布\nk count cum\n");
  ll cum=0; for(auto&[k,c]:minkHist){cum+=c;printf("%5d %7lld %7lld\n",k,c,cum);} 
  printf("\n# decade 別 max(min hit k)\n");
  for(auto&[d,m]:maxByDec) printf("10^%d..10^%d : %d  (survivor n=%lld)\n",d,d+1,m,nByDec[d]);
  printf("\n# 最小 hit k >= 100 の例\n");
  for(auto&[p,k]:big) printf("p=%lld  min_k=%d\n",p,k);
  return 0;
}
