// tradeoff.cpp -- 証拠約数の予算 D と必要な shift k のトレードオフ。
//   k_D(p) = min { k=3(4) : ∃ e | C_k^2, e ≡ t1 or t2 (mod k), d(e) <= D }
// D=1 は古典的な恒等式 (p ≡ -4 mod k の Type II / p ≡ ... の Type I)。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):100000000; int KCAP=argc>2?atoi(argv[2]):20003;
  const int NB=9; ll BUD[NB]={1,2,4,8,16,32,64,128,256};
  vector<int> HS={1,121,169,289,361,529};
  ll Nmax=LIM/4+KCAP+32; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> psmall; for(int i=2;i<50000;i++) if(spf[i]==i) psmall.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(int q:psmall){ if(1LL*q*q>n)break; if(n%q==0) return false;} return true; };
  vector<pair<int,ll>> cur,nxt;
  vector<ll> mx(NB,0), unres(NB,0); vector<vector<ll>> all(NB); ll hard=0;
  vector<ll> sumk(NB,0);
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    hard++; vector<ll> kD(NB,-1); int left=NB;
    for(int k=3;k<=KCAP&&left>0;k+=4){ ll C=(p+k)/4; if((p+k)%4)continue; if(C>Nmax)break;
      int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k);
      cur.clear(); cur.push_back({1%k,1}); ll c=C;
      while(c>1){ int q=spf[c]; int a=0; while(c%q==0){c/=q;a++;}
        nxt.clear(); ll qp=1;
        for(int e=0;e<=2*a;e++){ ll dp=1; for(int i2=0;i2<(e+1)/2;i2++) dp*=q; int qm=(int)(qp%k);
          for(auto&[rr,dd]:cur){ ll nd=dd*dp; if(nd>256) continue; nxt.push_back({(int)(1LL*rr*qm%k),nd}); }
          qp*=q; }
        cur.swap(nxt); if(cur.empty())break; }
      ll bd=LLONG_MAX; for(auto&[rr,dd]:cur) if(rr==t1||rr==t2) bd=min(bd,dd);
      if(bd==LLONG_MAX) continue;
      for(int b=0;b<NB;b++) if(kD[b]<0 && bd<=BUD[b]){ kD[b]=k; left--; }
    }
    for(int b=0;b<NB;b++){ if(kD[b]<0) unres[b]++; else { mx[b]=max(mx[b],kD[b]); all[b].push_back(kD[b]); sumk[b]+=kD[b]; } }
   } if(!any)break; }
  printf("LIM=%lld KCAP=%d hard=%lld\n\n",LIM,KCAP,hard);
  printf("# 証拠約数の予算 D に対する必要 shift k_D(p)\n");
  printf("  D   max k_D   mean   p99      p99.9   未解決(k<=%d)\n",KCAP);
  for(int b=0;b<NB;b++){ auto v=all[b]; sort(v.begin(),v.end());
    ll p99=v.empty()?0:v[(size_t)(v.size()*0.99)], p999=v.empty()?0:v[(size_t)(v.size()*0.999)];
    printf("%4lld %8lld %8.1f %6lld %8lld %10lld\n",BUD[b],mx[b],v.empty()?0.0:(double)sumk[b]/v.size(),p99,p999,unres[b]); }
  return 0;
}
