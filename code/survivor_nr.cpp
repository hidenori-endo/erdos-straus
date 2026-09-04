// survivor_nr.cpp -- 反例候補 (atlas の全 pure 条件を満たす hard prime) に限定して
// external-NR induced shift の exact box を全 rank 走らせ、輸送構造を測る。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
static int jacobi(ll a, ll n){ a%=n; if(a<0)a+=n; int r=1;
  while(a){ while(!(a&1)){ a>>=1; ll m=n&7; if(m==3||m==5) r=-r; }
    swap(a,n); if((a&3)==3&&(n&3)==3) r=-r; a%=n; } return n==1?r:0; }
static int invm(int a,int m){int b=m,u=1,v=0;while(b){int t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}u%=m;if(u<0)u+=m;return u;}
static vector<int> spf;
struct Fac{ vector<pair<int,int>> f; };
static Fac factor(ll n){ Fac F; while(n>1){int q=spf[n];int a=0;while(n%q==0){n/=q;a++;}F.f.push_back({q,a});} return F; }

int main(int argc,char**argv){
  ll LIM = argc>1? atoll(argv[1]) : 100000000;
  int RB  = argc>2? atoi(argv[2])  : 2000;
  int MAXRANK = argc>3? atoi(argv[3]) : 40;
  vector<int> HS={1,121,169,289,361,529};
  // atlas: class -> pure が強制される j (= (k-3)/4)
  map<int,vector<int>> AT = {
    {1,{0,1,3}}, {121,{0,1,3,4,8,11}}, {169,{0,1,2,3,7}},
    {289,{0,1,2,3,7,11}}, {361,{0,1,3,8,14}}, {529,{0,1,2,3,7}} };

  ll Nmax = LIM/4 + RB + 32;
  spf.assign(Nmax+1,0);
  for(ll i=2;i<=Nmax;i++) if(!spf[i]) for(ll j=i;j<=Nmax;j+=i) if(!spf[j]) spf[j]=(int)i;
  vector<int> pr; for(int i=2;i<=RB;i++) if(spf[i]==i) pr.push_back(i);
  auto isp=[&](ll n){ if(n<2)return false; if(n<=Nmax) return spf[n]==n;
    for(ll q=2;q*q<=n;q++) if(n%q==0) return false;
    return true; };

  map<int,ll> hardC, survC;
  vector<ll> firstHit(MAXRANK+2,0);
  ll surv=0, persist=0;
  map<int,ll> missRankHist;   // rank -> miss 数 (survivor のみ)
  map<int,ll> seenRankHist;
  map<int,ll> missE1ByRank, missKltRByRank, leastMassLemmaViolations;
  // miss 構造
  ll missTot=0, missE1=0, missEeven=0, sameShiftPair=0, missWithSecondNR=0;
  map<int,ll> missByK, seenByK;
  vector<pair<ll,int>> worst; // (p, firstHitRank)
  vector<ll> divs; divs.reserve(1<<17);

  for(ll t=0;;t++){
    bool any=false;
    for(int h:HS){ ll p=840*t+h; if(p>=LIM) continue; any=true; if(p<11) continue;
      if(!isp(p)) continue;
      hardC[h]++;
      ll N=(p+3)/4;
      bool cand=true;
      for(int j: AT[h]){ Fac F=factor(N+j); for(auto&[q,a]:F.f) if(jacobi(q,p)==-1){cand=false;break;} if(!cand)break; }
      if(!cand) continue;
      survC[h]++; surv++;
      int rank=0, fh=-1;
      for(int r: pr){ if(r<11||p%r==0) continue; if(jacobi(r,p)!=-1) continue;
        if(rank>=MAXRANK) break;
        int j=(int)((r-N%r)%r); int k=4*j+3; ll C=N+j;
        Fac F=factor(C); int E=0; int nrCount=0; ll secondNR=0;
        divs.clear(); divs.push_back(1);
        for(auto&[q,a]:F.f){ if(jacobi(q,p)==-1){E+=a; nrCount++; if(q!=r&&!secondNR) secondNR=q;}
          size_t sz=divs.size(); ll pw=1; for(int e=1;e<=2*a;e++){pw*=q; for(size_t i2=0;i2<sz;i2++) divs.push_back(divs[i2]*pw);} }
        int t1=(k-invm(4,k))%k, t2=(int)((k-C%k)%k);
        bool hit=false; for(ll d:divs){int rr=(int)(d%k); if(rr==t1||rr==t2){hit=true;break;}}
        seenRankHist[rank]++; seenByK[k]++;
        if(!hit){ missRankHist[rank]++; missByK[k]++; missTot++;
          if(E==1){ missE1++; missE1ByRank[rank]++; }
          if(k<r){
            missKltRByRank[rank]++;
            // The mass lemma uses that r is the least NR prime, so it only
            // applies at rank zero.  Later ranks can legitimately have E=1.
            if(rank==0 && E<2) leastMassLemmaViolations[rank]++;
          }
          if(E%2==0) missEeven++;
          if(secondNR){ missWithSecondNR++; if(secondNR> j) sameShiftPair++; } }
        else if(fh<0) fh=rank;
        rank++; }
      if(fh>=0){ firstHit[fh]++; if(fh>=3&&worst.size()<60) worst.push_back({p,fh}); }
      else { persist++; firstHit[MAXRANK+1]++; if(worst.size()<60) worst.push_back({p,-1}); }
    }
    if(!any) break;
  }
  printf("LIM=%lld RB=%d MAXRANK=%d\n",LIM,RB,MAXRANK);
  printf("\n# hard / survivor by class\nh hard surv\n");
  ll th=0,ts=0; for(int h:HS){ printf("%4d %8lld %8lld\n",h,hardC[h],survC[h]); th+=hardC[h]; ts+=survC[h]; }
  printf("tot  %8lld %8lld\n",th,ts);
  printf("\n# survivor: first-hit NR rank (exact Div(C^2) box)\nrank count cum\n");
  ll cum=0; for(int i=0;i<MAXRANK;i++) if(firstHit[i]){cum+=firstHit[i];printf("%3d %8lld %8lld\n",i,firstHit[i],cum);}
  printf("none %lld\n",persist);
  printf("\n# survivor: miss structure by NR rank\nrank seen miss rate   E==1   k<r least_lemma_viol\n");
  for(int i=0;i<MAXRANK;i++) if(seenRankHist.count(i))
    printf("%3d %8lld %8lld %.4f %7lld %7lld %10lld\n",i,seenRankHist[i],
      missRankHist[i],(double)missRankHist[i]/seenRankHist[i],missE1ByRank[i],
      missKltRByRank[i],leastMassLemmaViolations[i]);
  printf("\n# miss structure: total=%lld  E==1:%lld  E even:%lld  has 2nd NR factor:%lld  (2nd NR induces same shift):%lld\n",
     missTot,missE1,missEeven,missWithSecondNR,sameShiftPair);
  printf("\n# miss rate by induced shift k (top 25)\nk seen miss rate\n");
  vector<pair<ll,int>> ks; for(auto&kv:seenByK) ks.push_back({kv.second,kv.first});
  sort(ks.rbegin(),ks.rend());
  for(int i=0;i<(int)ks.size()&&i<25;i++){int k=ks[i].second;printf("%4d %8lld %8lld %.4f\n",k,seenByK[k],missByK[k],(double)missByK[k]/seenByK[k]);}
  printf("\n# examples with firstHitRank>=3 (-1 = none)\n");
  for(auto&[p,f]:worst) printf("p=%lld rank=%d\n",p,f);
  return 0;
}
