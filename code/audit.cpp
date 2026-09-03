// Independent arithmetic audit of the character-annihilation predictions.
//
// Ground truth (no model, pure arithmetic): for a hard prime p and shift
// k = 3 (mod 4), set C = (p+k)/4.  Fixing the denominator x = C (the one not
// divisible by p) and solving 1/y + 1/z = k/(pC) gives
//     Type II (p|y, p|z):  (ky'-C)(kz'-C) = C^2,      D = ky'-C  | C^2,  D = -C   (mod k)
//     Type I  (p|y, p!|z): (ky'-C)(kz-pC) = pC^2,     D = (ky'-C)/p | C^2,  D = -1/4 (mod k)
// so the EXACT box is the residue set mod k of the divisors of C^2 (exponent
// 0..2e per prime), and the shift hits iff that set contains
//    Type I  target  t1 = -1/4 (mod k)   or   Type II target t2 = -C (mod k).
// code/box_check.py verifies this against brute-force ES solutions.
//
// The earlier version of this file used the divisors of C itself (exponent
// 0..e).  That is a proper SUB-box: every sub-box hit is a real hit, but a
// sub-box miss can be a real hit (e.g. p=21121, k=35).  Both boxes are
// reported here so the gap can be measured.
//
// Prediction under test: exact miss  <=>  every prime factor r of C has (p/r) = +1
// ("pure").  Using the verified lemma (p/r) = jacobi(r,k), pure means
// jacobi(r,k) = +1 for all r|C.
//
//   ./audit LIM k1 k2 ...        (no k given: every k = 3 (mod 4), k <= 403)
//
// Output per (k, h = p mod 840): hard p, subMiss (old box), fullMiss (exact box),
// pure, fullMiss&!pure, pure&!fullMiss, subMiss&fullHit, verdict for the exact
// box, and the smallest witness p with fullMiss&!pure together with C's factorisation.
#include <bits/stdc++.h>
using namespace std;
static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
static long long eg(long long a,long long b,long long&x,long long&y){if(!b){x=1;y=0;return a;}long long X,Y,g=eg(b,a%b,X,Y);x=Y;y=X-a/b*Y;return g;}
static int invm(int a,int m){long long x,y;eg(a,m,x,y);x%=m;if(x<0)x+=m;return x;}
struct Row{long long tot=0,subMiss=0,fullMiss=0,pure=0,fmNotPure=0,pureNotFm=0,subMissFullHit=0; long long wit=0; string witC;};
int main(int argc,char**argv){
    long long LIM=argc>1?atoll(argv[1]):2000000LL;
    vector<int> ks; for(int i=2;i<argc;i++) ks.push_back(atoi(argv[i]));
    if(ks.empty()) for(int k=3;k<=403;k+=4) ks.push_back(k);
    // odd sieve up to LIM
    fprintf(stderr,"sieving to %lld ...\n",LIM);
    long long n=LIM; vector<uint64_t> comp((n/2)/64+2,0);
    auto isc=[&](long long i){return (comp[i>>6]>>(i&63))&1ULL;};      // i indexes odd number 2i+1
    for(long long i=1;(2*i+1)*(2*i+1)<=n;i++) if(!isc(i)){long long q=2*i+1; for(long long j=q*q;j<=n;j+=2*q){long long idx=(j-1)/2;comp[idx>>6]|=1ULL<<(idx&63);} }
    vector<int> smallp; smallp.push_back(2); for(long long i=1;2*i+1<=20000;i++) if(!isc(i)) smallp.push_back((int)(2*i+1));
    vector<int> hs={1,121,169,289,361,529};
    vector<long long> hp; for(long long i=2;2*i+1<=n;i++){ if(isc(i))continue; long long p=2*i+1; if(p%4!=1)continue; int h=p%840; if(h==1||h==121||h==169||h==289||h==361||h==529) hp.push_back(p);}
    fprintf(stderr,"hard primes < %lld : %zu\n",LIM,hp.size());
    printf("k,h,hard_p,subMiss,fullMiss,pure,fullMiss_notPure,pure_notFullMiss,subMiss_fullHit,equiv_full,min_witness_p,witness_C\n");
    for(int k:ks){
        int t1=(k-invm(4,k))%k; map<int,Row> tab; for(int h:hs) tab[h]=Row();
        vector<uint64_t> res, base; int W=(k+63)/64;
        for(long long p:hp){
            if(p<=k) continue; long long C=(p+k)/4; int h=(int)(p%840);
            int pe[40]; long long pf[40]; int nf=0; long long c=C;
            for(int q:smallp){ if(1LL*q*q>c) break; if(c%q==0){pf[nf]=q;pe[nf]=0;while(c%q==0){c/=q;pe[nf]++;}nf++;} }
            if(c>1){pf[nf]=c;pe[nf]=1;nf++;}
            bool pure=true; for(int f=0;f<nf;f++) if(jacobi(pf[f]%k,k)!=1){pure=false;break;}
            int t2=(int)((k-C%k)%k);
            bool miss[3];
            for(int mult=1;mult<=2;mult++){          // mult=1: divisors of C (old sub-box), mult=2: divisors of C^2 (exact)
                res.assign(W,0); auto setb=[&](int x){res[x>>6]|=1ULL<<(x&63);}; auto getb=[&](int x){return (res[x>>6]>>(x&63))&1ULL;};
                setb(1%k);
                for(int f=0;f<nf;f++){
                    int r=(int)(pf[f]%k); base=res; int rr=1;
                    for(int e=1;e<=mult*pe[f];e++){ rr=(int)(1LL*rr*r%k); for(int a=0;a<k;a++) if((base[a>>6]>>(a&63))&1ULL) setb((int)(1LL*a*rr%k)); }
                }
                miss[mult]=!getb(t1)&&!getb(t2);
            }
            Row&T=tab[h]; T.tot++; if(miss[1])T.subMiss++; if(miss[2])T.fullMiss++; if(pure)T.pure++;
            if(miss[2]&&!pure){T.fmNotPure++; if(!T.wit){T.wit=p; string s; for(int f=0;f<nf;f++){ if(f)s+="*"; s+=to_string(pf[f]); if(pe[f]>1) s+="^"+to_string(pe[f]); } T.witC=s;}}
            if(pure&&!miss[2])T.pureNotFm++;
            if(miss[1]&&!miss[2])T.subMissFullHit++;
        }
        for(int h:hs){Row&T=tab[h];
            printf("%d,%d,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%s,%lld,%s\n",k,h,T.tot,T.subMiss,T.fullMiss,T.pure,T.fmNotPure,T.pureNotFm,T.subMissFullHit,(T.fmNotPure==0&&T.pureNotFm==0)?"YES":"no",T.wit,T.witC.c_str());}
        fflush(stdout);
    }
}
