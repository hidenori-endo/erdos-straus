// cert_complexity.cpp -- ES 証拠の複雑度
//   cert(p) = min over k=3(4), over e | C_k^2 with e = t1 or t2 (mod k), of max(k, d(e))
//   d(e) = prod q^ceil(a_q/2)   (e | d^2, d | C_k を満たす最小の d)
// cert(p) <= B なら p は「shift k<=B、証拠約数 d<=B」の有限族で覆われる。
// k を昇順に走らせ k >= best で打ち切れるので k は無制限に扱える。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):100000000;
  vector<int> HS={1,121,169,289,361,529};
  ll Nmax=LIM/4+4096; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> psmall; for(int i=2;i<50000;i++) if(spf[i]==i) psmall.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(int q:psmall){ if(1LL*q*q>n)break; if(n%q==0) return false;} return true; };
  vector<pair<int,ll>> cur,nxt;
  map<ll,ll> hist; map<int,ll> maxByDec,nByDec; vector<pair<ll,ll>> big; ll hard=0; double sumlog=0;
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(!isp(p))continue;
    hard++; ll best=LLONG_MAX;
    for(int k=3;;k+=4){ if(best!=LLONG_MAX && k>=best) break; if(k>4*Nmax) break;
      ll C=(p+k)/4; if((p+k)%4) continue; if(C>Nmax) break;
      int t1=(k-invm(4,k))%k, t2=(int)((k-C%k)%k);
      cur.clear(); cur.push_back({1%k,1}); ll c=C;
      while(c>1){ int q=spf[c]; int a=0; while(c%q==0){c/=q;a++;}
        nxt.clear(); ll qp=1;
        for(int e=0;e<=2*a;e++){ ll dp=1; for(int i2=0;i2<(e+1)/2;i2++) dp*=q; int qm=(int)(qp%k);
          for(auto&[rr,dd]:cur){ ll nd=dd*dp; if(best!=LLONG_MAX && nd>=best) continue;
            nxt.push_back({(int)(1LL*rr*qm%k), nd}); }
          qp*=q; }
        cur.swap(nxt); if(cur.empty()) break; }
      for(auto&[rr,dd]:cur) if(rr==t1||rr==t2){ ll v=max((ll)k,dd); if(v<best) best=v; }
    }
    ll b=1; while(b<best) b*=2; hist[b]++; sumlog+=log((double)best);
    int d=0;ll q2=p;while(q2>=10){q2/=10;d++;} maxByDec[d]=max(maxByDec.count(d)?maxByDec[d]:0LL,best); nByDec[d]++;
    if(best>200&&big.size()<30) big.push_back({p,best});
   } if(!any)break; }
  printf("LIM=%lld hard=%lld\n\n# cert(p) = min_k max(k, d(e)) の分布 (2 べきビン)\nbin(<=) count cum frac\n",LIM,hard);
  ll cum=0; for(auto&[b,c]:hist){cum+=c;printf("%10lld %8lld %8lld %.5f\n",b,c,cum,(double)cum/hard);} 
  printf("\n# decade 別 max cert\n"); for(auto&[d,m]:maxByDec) printf("10^%d..10^%d : %lld  (n=%lld)\n",d,d+1,m,nByDec[d]);
  printf("\n# geometric mean cert = %.2f\n", exp(sumlog/hard));
  printf("\n# cert > 200 の例\n"); for(auto&[p,c]:big) printf("p=%lld cert=%lld\n",p,c);
  return 0;
}
