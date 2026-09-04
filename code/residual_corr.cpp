// residual_corr.cpp -- survivor の各 (p, NR rank) の miss を、(k, d(C^2)) で
// 較正した確率 q と比べ、残差相関を測る。輸送可能な依存が残るかの判定。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int jacobi(ll a,ll n){a%=n;if(a<0)a+=n;int r=1;while(a){while(!(a&1)){a>>=1;ll m=n&7;if(m==3||m==5)r=-r;}swap(a,n);if((a&3)==3&&(n&3)==3)r=-r;a%=n;}return n==1?r:0;}
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
static int bk(int k){ return min(23,(int)(log2((double)k)*3)); }
static int bd(int d){ return min(23,(int)(log2((double)d)*3)); }
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):100000000; int RB=argc>2?atoi(argv[2]):20000; int MR=argc>3?atoi(argv[3]):32;
  vector<int> HS={1,121,169,289,361,529};
  map<int,vector<int>> AT={{1,{0,1,3}},{121,{0,1,3,4,8,11}},{169,{0,1,2,3,7}},
    {289,{0,1,2,3,7,11}},{361,{0,1,3,8,14}},{529,{0,1,2,3,7}}};
  ll Nmax=LIM/4+RB+32; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> pr; for(int i=2;i<=RB;i++) if(spf[i]==i) pr.push_back(i);
  vector<int> psmall; for(int i=2;i<50000;i++) if(spf[i]==i) psmall.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(int q:psmall){ if(1LL*q*q>n)break; if(n%q==0) return false;} return true; };
  // pass 1: 収集
  struct Rec{ int k; int d; char miss; };
  vector<vector<Rec>> data; data.reserve(20000);
  vector<int> firstHit; vector<ll> plist;
  vector<ll> divs; divs.reserve(1<<17);
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    ll N=(p+3)/4; bool cand=true;
    for(int j:AT[h]){ ll c=N+j; while(c>1){int q=spf[c];while(c%q==0)c/=q; if(jacobi(q,p)==-1){cand=false;break;}} if(!cand)break;}
    if(!cand)continue;
    vector<Rec> v; int rank=0,fh=-1;
    for(int r:pr){ if(r<11||p%r==0)continue; if(jacobi(r,p)!=-1)continue; if(rank>=MR)break;
      int j=(int)((r-N%r)%r); int k=4*j+3; ll C=N+j,c=C;
      divs.clear(); divs.push_back(1);
      while(c>1){int q=spf[c];int a=0;while(c%q==0){c/=q;a++;} size_t sz=divs.size();ll pw=1;
        for(int e=1;e<=2*a;e++){pw*=q;for(size_t i2=0;i2<sz;i2++)divs.push_back(divs[i2]*pw);} }
      int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k); bool hit=false;
      for(ll d:divs){int rr=(int)(d%k); if(rr==t1||rr==t2){hit=true;break;}}
      v.push_back({k,(int)divs.size(),(char)(hit?0:1)}); if(hit&&fh<0)fh=rank; rank++; }
    data.push_back(move(v)); firstHit.push_back(fh); plist.push_back(p);
   } if(!any)break; }
  ll n=data.size(); printf("survivors=%lld\n",n);
  // 較正表 q[bk][bd]
  static double sum[24][24]; static ll cntb[24][24];
  memset(sum,0,sizeof sum); memset(cntb,0,sizeof cntb);
  for(auto&v:data) for(auto&rc:v){ sum[bk(rc.k)][bd(rc.d)]+=rc.miss; cntb[bk(rc.k)][bd(rc.d)]++; }
  auto q=[&](int k,int d)->double{ int a=bk(k),b=bd(d); if(cntb[a][b]<40) return -1; return sum[a][b]/cntb[a][b]; };
  // 残差相関
  const int CB=12;
  static double sxy[CB][CB], sxx[CB], sn[CB][CB]; static ll nn[CB];
  memset(sxy,0,sizeof sxy); memset(sxx,0,sizeof sxx); memset(sn,0,sizeof sn); memset(nn,0,sizeof nn);
  static double rawj[CB][CB]; static double rawm[CB]; memset(rawj,0,sizeof rawj); memset(rawm,0,sizeof rawm); ll nfull=0;
  for(auto&v:data){ if((int)v.size()<CB) continue; nfull++;
    double e[CB]; bool ok[CB];
    for(int i=0;i<CB;i++){ double qq=q(v[i].k,v[i].d); ok[i]=(qq>=0); e[i]=ok[i]? v[i].miss-qq : 0; if(ok[i]) sxx[i]+=e[i]*e[i], nn[i]++; rawm[i]+=v[i].miss; }
    for(int i=0;i<CB;i++)for(int j=0;j<CB;j++){ if(ok[i]&&ok[j]){ sxy[i][j]+=e[i]*e[j]; sn[i][j]++; } rawj[i][j]+=v[i].miss*v[j].miss; }
  }
  printf("full-depth survivors (>=%d ranks)=%lld\n\n",CB,nfull);
  printf("# 生の miss 相関 joint/(mi*mj/n)\n   "); for(int j=0;j<CB;j++)printf("%6d",j); printf("\n");
  for(int i=0;i<CB;i++){printf("%3d",i); for(int j=0;j<CB;j++){double ex=rawm[i]*rawm[j]/nfull; printf("%6.2f", ex>0?rawj[i][j]/ex:0);} printf("\n");}
  printf("\n# (k,d) 較正後の残差相関 (0.00 = 依存なし)\n   "); for(int j=0;j<CB;j++)printf("%6d",j); printf("\n");
  for(int i=0;i<CB;i++){printf("%3d",i);
    for(int j=0;j<CB;j++){ double den=sqrt(sxx[i]/max(1LL,nn[i]))*sqrt(sxx[j]/max(1LL,nn[j]));
      double c=sn[i][j]?sxy[i][j]/sn[i][j]:0; printf("%6.2f", den>0? c/den:0);} printf("\n");}
  // 較正モデルによる「全 rank miss」確率の予測 vs 実測
  double predAllMiss=0; ll obsAllMiss=0;
  for(auto&v:data){ if((int)v.size()<CB)continue; double pr_=1; bool ok=true; for(int i=0;i<CB;i++){double qq=q(v[i].k,v[i].d); if(qq<0){ok=false;break;} pr_*=qq;} if(ok)predAllMiss+=pr_;
    bool am=true; for(int i=0;i<CB;i++) if(!v[i].miss){am=false;break;} if(am)obsAllMiss++; }
  printf("\n# 最初の %d rank が全て miss: 実測=%lld  独立モデル予測=%.2f\n",CB,obsAllMiss,predAllMiss);
  // first-hit rank の decade 別最大
  map<int,int> mx; map<int,ll> cnt2;
  for(size_t i=0;i<plist.size();i++){int d=0;ll p=plist[i];while(p>=10){p/=10;d++;} mx[d]=max(mx.count(d)?mx[d]:-1,firstHit[i]); cnt2[d]++;}
  printf("\n# decade 別 max first-hit rank (survivor 数)\n");
  for(auto&[d,m]:mx) printf("10^%d..10^%d : %d  (n=%lld)\n",d,d+1,m,cnt2[d]);
  return 0;
}
