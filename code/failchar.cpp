// 層の失敗条件を「n の素因子の mod 4d 類」で書けるかの検算
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static vector<int> spf;
int main(int argc,char**argv){
  ll LIM=argc>1?atoll(argv[1]):10000000;
  ll Nmax=LIM+64; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> HS={1,121,169,289,361,529};
  // (d,e,m) と主張する失敗条件
  struct T{ll d,e;};
  vector<T> ts={{1,1},{2,2},{3,3},{4,8},{5,5},{6,6},{7,7},{8,32}};
  ll hard=0; map<ll,ll> mism, fail;
  for(ll t=0;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; any=true; if(p<11)continue; if(spf[p]!=p)continue;
    hard++;
    for(auto&[d,e]:ts){ ll m=4*d, n=p+4*e; int tgt=(int)(((-n)%m+m)%m);
      // 真: n の約数に tgt があるか
      vector<ll> ds{1}; ll c=n; set<int> pres;
      while(c>1){int q=spf[c];int a=0;while(c%q==0){c/=q;a++;} pres.insert(q%m); size_t s=ds.size();ll pw=1;
        for(int j=1;j<=a;j++){pw*=q;for(size_t z=0;z<s;z++)ds.push_back(ds[z]*pw);} }
      bool truth=false; for(ll k:ds) if(k%m==tgt){truth=true;break;}
      // 主張: 素因子剰余の集合が生成する部分半群に tgt が入るか (mod m の乗法で閉包)
      set<int> S{1%(int)m};
      bool changed=true; while(changed){ changed=false; vector<int> add;
        for(int x:S) for(int r:pres){ int y=(int)(1LL*x*r%m); if(!S.count(y)) add.push_back(y); }
        for(int y:add) if(S.insert(y).second) changed=true; }
      bool claim=S.count(tgt)>0;
      if(claim!=truth) mism[d]++;
      if(!truth) fail[d]++;
    }
   } if(!any)break; }
  printf("hard=%lld\n d   失敗数   失敗率   「素因子剰余の生成半群が -n を含まない」との不一致\n",hard);
  for(auto&[d,f]:fail) printf("%2lld %8lld  %.4f  %lld\n",d,f,(double)f/hard,mism[d]);
  return 0;
}
