// cert_size.cpp -- hit 証拠の最小サイズ。
// e | C_k^2 が t1/t2 を踏むとき、e | d^2 かつ d | C_k を満たす最小の d は
//   d(e) = prod q^ceil(a_q/2)。
// dmin(p) = min over k<=KMAX, over hitting e, d(e)。
// dmin が小さく有界なら covering congruence (多項式恒等式) で証明できることになる。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int jacobi(ll a,ll n){a%=n;if(a<0)a+=n;int r=1;while(a){while(!(a&1)){a>>=1;ll m=n&7;if(m==3||m==5)r=-r;}swap(a,n);if((a&3)==3&&(n&3)==3)r=-r;a%=n;}return n==1?r:0;}
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):30000000; int KMAX=argc>2?atoi(argv[2]):107;
  vector<int> HS={1,121,169,289,361,529};
  ll Nmax=LIM/4+KMAX+32; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> psmall; for(int i=2;i<50000;i++) if(spf[i]==i) psmall.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(int q:psmall){ if(1LL*q*q>n)break; if(n%q==0) return false;} return true; };
  // (residue mod k, d(e)) のペアを再帰生成
  vector<pair<int,ll>> cur, nxt;
  map<ll,ll> dminHist; ll hard=0; ll noHit=0;
  vector<pair<ll,ll>> big; map<int,ll> maxByDec; map<int,ll> nByDec;
  ll sumLog=0; ll cntLog=0;
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    hard++; ll best=-1;
    for(int k=3;k<=KMAX;k+=4){ ll C=(p+k)/4; if((p+k)%4)continue;
      int t1=(k-invm(4,k))%k, t2=(int)((k-C%k)%k);
      cur.clear(); cur.push_back({1%k,1});
      ll c=C;
      while(c>1){ int q=spf[c]; int a=0; while(c%q==0){c/=q;a++;}
        nxt.clear(); ll qp=1;
        for(int e=0;e<=2*a;e++){ ll dpart=1; for(int i2=0;i2<(e+1)/2;i2++) dpart*=q;
          int qm=(int)(qp%k);
          for(auto&[rr,dd]:cur){ if(best>=0 && dd*dpart>=best) continue; nxt.push_back({(int)(1LL*rr*qm%k), dd*dpart}); }
          qp*=q; }
        cur.swap(nxt);
        if(cur.empty()) break; }
      for(auto&[rr,dd]:cur) if(rr==t1||rr==t2) if(best<0||dd<best) best=dd;
    }
    if(best<0){ noHit++; if(big.size()<25)big.push_back({p,-1}); }
    else { ll b=1; while(b<best) b*=2; dminHist[b]++; if(best>1000&&big.size()<25)big.push_back({p,best});
      int d=0;ll q2=p;while(q2>=10){q2/=10;d++;} maxByDec[d]=max(maxByDec.count(d)?maxByDec[d]:0LL,best); nByDec[d]++;
      sumLog+=(ll)(log((double)best)*1000); cntLog++; }
   } if(!any)break; }
  printf("LIM=%lld KMAX=%d hard=%lld noHitWithinKMAX=%lld\n",LIM,KMAX,hard,noHit);
  printf("\n# dmin(p) = 最小の証拠約数サイズ、2 べきビン\nbin(<=) count cum frac\n");
  ll cum=0; for(auto&[b,c]:dminHist){cum+=c;printf("%12lld %8lld %8lld %.4f\n",b,c,cum,(double)cum/hard);} 
  printf("\n# decade 別 max dmin\n");
  for(auto&[d,m]:maxByDec) printf("10^%d..10^%d : %lld  (n=%lld)\n",d,d+1,m,nByDec[d]);
  printf("\n# geometric mean dmin = %.1f\n", cntLog?exp((double)sumLog/cntLog/1000.0):0.0);
  printf("\n# dmin > 1e5 の例\n"); for(auto&[p,d]:big) printf("p=%lld dmin=%lld\n",p,d);
  return 0;
}
