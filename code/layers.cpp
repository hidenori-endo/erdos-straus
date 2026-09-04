// layers.cpp -- 層 (d,e) の閉じた形の判定を、箱の総当たりと突き合わせる。
// 主張:
//   Type II 層 (d,e), d=d(e), e|d^2:  p は覆われる <=> n=p+4e が k ≡ -n (mod 4d) なる約数を持つ
//   Type I  層 (d,e):                 p は覆われる <=> 4e+1 が k ≡ -p (mod 4d) なる約数を持つ
// ground truth: Div(C_k^2) mod k の総当たり (k <= KCAP)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
static vector<ll> divisors(ll n){ vector<ll> ds{1};
  while(n>1){ int q=spf[n]; int a=0; while(n%q==0){n/=q;a++;} size_t s=ds.size(); ll pw=1;
    for(int i=1;i<=a;i++){ pw*=q; for(size_t j=0;j<s;j++) ds.push_back(ds[j]*pw);} } return ds; }
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):10000000; int DMAX=argc>2?atoi(argv[2]):8; int KCAP=argc>3?atoi(argv[3]):20003;
  // (d,e) 対: e | d^2, d(e)=d
  vector<pair<ll,ll>> DE;
  for(ll d=1;d<=DMAX;d++){ for(ll e=1;e<=d*d;e++){ if((d*d)%e) continue;
      ll x=e, dd=1; while(x>1){ int q=spf.empty()?0:0; (void)q; break; }
      // d(e) を直接計算
      ll t=e; dd=1; for(ll q=2;q*q<=t;q++){ if(t%q==0){int a=0;while(t%q==0){t/=q;a++;} ll pw=1;for(int i=0;i<(a+1)/2;i++)pw*=q; dd*=pw;} }
      if(t>1) dd*=t;
      if(dd==d) DE.push_back({d,e}); } }
  ll Emax=0; for(auto&[d,e]:DE) Emax=max(Emax,e);
  ll Nmax=max(LIM+4*Emax+8, LIM/4+KCAP+8); spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  fprintf(stderr,"(d,e) pairs = %zu : ",DE.size()); for(auto&[d,e]:DE) fprintf(stderr,"(%lld,%lld) ",d,e); fprintf(stderr,"\n");
  vector<int> HS={1,121,169,289,361,529};
  ll hard=0, mismatch=0; vector<ll> covByD(DMAX+1,0), covTypeI(DMAX+1,0);
  vector<ll> perLayerCov(DE.size(),0);
  vector<pair<int,ll>> cur,nxt;
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(spf[p]!=p)continue;
    hard++;
    // 閉じた形
    ll formulaD=-1;
    for(size_t i=0;i<DE.size();i++){ auto [d,e]=DE[i]; ll m=4*d;
      ll n=p+4*e; int tgt=(int)(((-n)%m+m)%m); bool ok=false;
      for(ll k: divisors(n)) if(k%m==tgt){ok=true;break;}
      if(!ok){ int tg2=(int)(((-p)%m+m)%m); for(ll k: divisors(4*e+1)) if(k%m==tg2){ ok=true; covTypeI[d]++; break; } }
      if(ok){ perLayerCov[i]++; if(formulaD<0||d<formulaD) formulaD=d; } }
    if(formulaD>0) covByD[formulaD]++;
    // ground truth: 予算 D<=DMAX で覆われる最小 D
    ll truthD=-1;
    for(int k=3;k<=KCAP&&truthD<0;k+=4){ ll C=(p+k)/4; if((p+k)%4)continue;
      int t1=(k-invm(4,k))%k,t2=(int)((k-C%k)%k);
      cur.clear(); cur.push_back({1%k,1}); ll c=C;
      while(c>1){ int q=spf[c]; int a=0; while(c%q==0){c/=q;a++;}
        nxt.clear(); ll qp=1;
        for(int ee=0;ee<=2*a;ee++){ ll dp=1; for(int i2=0;i2<(ee+1)/2;i2++) dp*=q; int qm=(int)(qp%k);
          for(auto&[rr,dd]:cur){ ll nd=dd*dp; if(nd>DMAX) continue; nxt.push_back({(int)(1LL*rr*qm%k),nd}); }
          qp*=q; }
        cur.swap(nxt); if(cur.empty())break; }
      for(auto&[rr,dd]:cur) if(rr==t1||rr==t2){ if(truthD<0||dd<truthD) truthD=dd; }
    }
    bool fa=(formulaD>0), tr=(truthD>0);
    if(fa!=tr){ if(mismatch<10) printf("MISMATCH p=%lld formulaD=%lld truthD=%lld\n",p,formulaD,truthD); mismatch++; }
   } if(!any)break; }
  printf("hard=%lld  formula vs 総当たり mismatch=%lld\n\n",hard,mismatch);
  printf("# 各層 (d,e) が単独で覆う割合\n d    e   覆う数   割合\n");
  for(size_t i=0;i<DE.size();i++) printf("%2lld %4lld %8lld  %.4f\n",DE[i].first,DE[i].second,perLayerCov[i],(double)perLayerCov[i]/hard);
  printf("\n# 最小 d 別の内訳 (累積 = D 予算)\n d  新規   累積   累積割合  TypeI 寄与\n");
  ll cum=0; for(int d=1;d<=DMAX;d++){ cum+=covByD[d]; printf("%2d %7lld %7lld  %.5f  %lld\n",d,covByD[d],cum,(double)cum/hard,covTypeI[d]); }
  printf("未被覆 (d<=%d) = %lld (%.5f)\n",DMAX,hard-cum,(double)(hard-cum)/hard);
  return 0;
}
