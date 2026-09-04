// fast_layers.cpp -- 層 (d,e) の閉じた形だけを使って、予算 D の未被覆密度を測る。
//   層 (d,e):  p は覆われる  <=>  n = p+4e が k ≡ -n (mod 4d) なる約数を持つ
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static vector<int> spf;
int main(int argc,char**argv){
  ll LO=argc>1?atoll(argv[1]):0, LIM=argc>2?atoll(argv[2]):100000000; int DMAX=argc>3?atoi(argv[3]):32;
  vector<pair<ll,ll>> DE;
  for(ll d=1;d<=DMAX;d++) for(ll e=d;e<=d*d;e++){ if((d*d)%e) continue;
    ll t=e,dd=1; for(ll q=2;q*q<=t;q++) if(t%q==0){int a=0;while(t%q==0){t/=q;a++;} ll pw=1;for(int i=0;i<(a+1)/2;i++)pw*=q; dd*=pw;}
    if(t>1)dd*=t; if(dd==d) DE.push_back({d,e}); }
  stable_sort(DE.begin(),DE.end());
  ll Emax=0; for(auto&[d,e]:DE) Emax=max(Emax,e);
  ll Nmax=LIM+4*Emax+8; spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> HS={1,121,169,289,361,529};
  vector<ll> minD(DMAX+2,0); ll hard=0; ll uncovered=0;
  vector<ll> ds; ds.reserve(1<<14);
  vector<ll> perLayer(DE.size(),0);
  for(ll t=LO/840;;t++){ bool any=false;
   for(int h:HS){ ll p=840*t+h; if(p>=LIM)continue; if(p<LO)continue; any=true; if(p<11)continue; if(spf[p]!=p)continue;
    hard++; ll best=-1;
    for(size_t i=0;i<DE.size();i++){ auto [d,e]=DE[i]; if(best>0&&d>best) break;
      ll m=4*d, n=p+4*e; int tgt=(int)(((-n)%m+m)%m);
      ds.clear(); ds.push_back(1); ll c=n; bool ok=false;
      while(c>1){ int q=spf[c]; int a=0; while(c%q==0){c/=q;a++;} size_t s=ds.size(); ll pw=1;
        for(int j=1;j<=a;j++){ pw*=q; for(size_t z=0;z<s;z++) ds.push_back(ds[z]*pw);} }
      for(ll k:ds) if(k%m==tgt){ok=true;break;}
      if(ok){ perLayer[i]++; if(best<0) best=d; } }
    if(best<0) uncovered++; else minD[best]++;
   } if(!any&&840*t>=LIM) break; }
  printf("range=[%lld,%lld) hard=%lld DMAX=%d layers=%zu\n\n",LO,LIM,hard,DMAX,DE.size());
  printf("# 予算 D に対する未被覆割合\n D    新規       累積      未被覆割合\n");
  ll cum=0; for(int d=1;d<=DMAX;d++){ cum+=minD[d];
    if(minD[d]||d==1||d==2||d==4||d==8||d==16||d==32) printf("%2d %8lld %10lld  %.6f\n",d,minD[d],cum,(double)(hard-cum)/hard); }
  printf("未被覆 (d<=%d) = %lld (%.6f)\n",DMAX,uncovered,(double)uncovered/hard);
  printf("\n# 単独層の被覆率 (上位)\n d    e     割合\n");
  vector<pair<double,size_t>> v; for(size_t i=0;i<DE.size();i++) v.push_back({(double)perLayer[i]/hard,i});
  sort(v.rbegin(),v.rend());
  for(int i=0;i<12&&i<(int)v.size();i++) printf("%2lld %4lld  %.4f\n",DE[v[i].second].first,DE[v[i].second].second,v[i].first);
  return 0;
}
