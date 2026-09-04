// transport_test.cpp -- survivor 限定で、NR rank 間の miss 相関と hit 確率の
// スケーリング (2 d(C^2) / k か?) を測る。輸送 route の可否判定用。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int jacobi(ll a,ll n){a%=n;if(a<0)a+=n;int r=1;while(a){while(!(a&1)){a>>=1;ll m=n&7;if(m==3||m==5)r=-r;}swap(a,n);if((a&3)==3&&(n&3)==3)r=-r;a%=n;}return n==1?r:0;}
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):100000000; int RB=argc>2?atoi(argv[2]):20000; int MR=argc>3?atoi(argv[3]):64;
  vector<int> HS={1,121,169,289,361,529};
  map<int,vector<int>> AT={{1,{0,1,3}},{121,{0,1,3,4,8,11}},{169,{0,1,2,3,7}},
    {289,{0,1,2,3,7,11}},{361,{0,1,3,8,14}},{529,{0,1,2,3,7}}};
  ll Nmax=LIM/4+RB+32; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> pr; for(int i=2;i<=RB;i++) if(spf[i]==i) pr.push_back(i);
  auto isp=[&](ll n){return n>=2&&n<=Nmax&&spf[n]==n;};
  const int CB=16;
  vector<ll> joint(CB*CB,0), marg(CB,0); ll nsurv=0;
  vector<double> sumK(MR,0), sumD(MR,0); vector<ll> cnt(MR,0), hitc(MR,0);
  vector<ll> divs; divs.reserve(1<<17);
  vector<int> maxRankByDecade(20,-1);
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    ll N=(p+3)/4; bool cand=true;
    for(int j:AT[h]){ ll c=N+j; while(c>1){int q=spf[c];while(c%q==0)c/=q; if(jacobi(q,p)==-1){cand=false;break;}} if(!cand)break;}
    if(!cand) continue; nsurv++;
    int rank=0,fh=-1; unsigned mask=0;
    for(int r:pr){ if(r<11||p%r==0)continue; if(jacobi(r,p)!=-1)continue; if(rank>=MR)break;
      int j=(int)((r-N%r)%r); int k=4*j+3; ll C=N+j; ll c=C;
      divs.clear(); divs.push_back(1);
      while(c>1){int q=spf[c];int a=0;while(c%q==0){c/=q;a++;} size_t sz=divs.size();ll pw=1;
        for(int e=1;e<=2*a;e++){pw*=q;for(size_t i2=0;i2<sz;i2++)divs.push_back(divs[i2]*pw);} }
      int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k); bool hit=false;
      for(ll d:divs){int rr=(int)(d%k); if(rr==t1||rr==t2){hit=true;break;}}
      sumK[rank]+=k; sumD[rank]+=divs.size(); cnt[rank]++; if(hit){hitc[rank]++; if(fh<0)fh=rank;} else if(rank<CB) mask|=1u<<rank;
      rank++; }
    for(int i=0;i<CB;i++){ if(mask>>i&1){marg[i]++; for(int j2=0;j2<CB;j2++) if(mask>>j2&1) joint[i*CB+j2]++;} }
    int dec=0; ll q=p; while(q>=10){q/=10;dec++;} if(dec<20) maxRankByDecade[dec]=max(maxRankByDecade[dec],fh);
   } if(!any)break; }
  printf("LIM=%lld RB=%d survivors=%lld\n\n",LIM,RB,nsurv);
  printf("# rank: hit rate vs 2*mean_d/mean_k  (independent-random model)\n");
  printf("rank  meanK   meanD  hitrate  2d/k   ratio  cumSumHit\n");
  double cs=0;
  for(int i=0;i<MR;i++) if(cnt[i]){ double mk=sumK[i]/cnt[i],md=sumD[i]/cnt[i],hr=(double)hitc[i]/cnt[i],pred=2*md/mk;
    cs+=hr; printf("%4d %7.0f %7.1f %7.4f %7.4f %6.2f %8.3f\n",i,mk,md,hr,pred,pred>0?hr/pred:0,cs); }
  printf("\n# survivor miss correlation joint/(mi*mj/n), 1.0 = independent\n   ");
  for(int j=0;j<CB;j++)printf("%6d",j); printf("\n");
  for(int i=0;i<CB;i++){ printf("%3d",i);
    for(int j=0;j<CB;j++){ double e=(double)marg[i]*marg[j]/nsurv; printf("%6.2f", e>0?joint[i*CB+j]/e:0.0);} printf("\n");}
  printf("\n# max first-hit rank by decade of p\n");
  for(int d=0;d<20;d++) if(maxRankByDecade[d]>=0) printf("10^%d..10^%d : %d\n",d,d+1,maxRankByDecade[d]);
  return 0;
}
