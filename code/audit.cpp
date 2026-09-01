// Independent arithmetic audit of the character-annihilation predictions.
//
// Ground truth (no model, pure arithmetic): for a hard prime p and shift
// k = 3 (mod 4), set C = (p+k)/4 and enumerate the residues mod k of ALL
// divisors of C.  The shift misses iff that residue set avoids both
//    Type I  target  t1 = -1/4 (mod k)
//    Type II target  t2 = -C   (mod k)
//
// Prediction under test: miss  <=>  every prime factor r of C has (p/r) = +1.
// Using the verified lemma (p/r) = jacobi(r,k), that is jacobi(r,k) = +1 for all r|C.
//
// Reports, per hard class h = p mod 840:
//   exact miss, predicted (pure) miss, and the two mismatch directions.
#include <bits/stdc++.h>
using namespace std;

static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
static long long eg(long long a,long long b,long long&x,long long&y){if(!b){x=1;y=0;return a;}long long X,Y,g=eg(b,a%b,X,Y);x=Y;y=X-a/b*Y;return g;}
static int invm(int a,int m){long long x,y;eg(a,m,x,y);x%=m;if(x<0)x+=m;return x;}

int main(int argc,char**argv){
    long long LIM = argc>1?atoll(argv[1]):100000000LL;
    vector<int> ks; for(int i=2;i<argc;i++) ks.push_back(atoi(argv[i]));
    if(ks.empty()) ks={15,35};

    // odd sieve up to LIM
    fprintf(stderr,"sieving to %lld ...\n",LIM);
    long long n=LIM; vector<uint64_t> comp((n/2)/64+2,0);
    auto isc=[&](long long i){return (comp[i>>6]>>(i&63))&1ULL;};      // i indexes odd number 2i+1
    for(long long i=1;(2*i+1)*(2*i+1)<=n;i++) if(!isc(i)){long long q=2*i+1; for(long long j=q*q;j<=n;j+=2*q){long long idx=(j-1)/2;comp[idx>>6]|=1ULL<<(idx&63);} }
    vector<int> smallp; for(long long i=1;2*i+1<=5000;i++) if(!isc(i)) smallp.push_back((int)(2*i+1));
    smallp.insert(smallp.begin(),2);

    vector<int> hs={1,121,169,289,361,529};
    for(int k:ks){
        int t1=(k-invm(4,k))%k;
        map<int,array<long long,5>> tab;   // h -> {total, exactMiss, pureMiss, missNotPure, pureNotMiss}
        vector<pair<long long,long long>> ex1, ex2;   // counterexample samples
        for(int h:hs) tab[h]={0,0,0,0,0};
        for(long long i=2;2*i+1<=n;i++){
            if(isc(i)) continue;
            long long p=2*i+1;
            if(p%4!=1) continue;
            int h=(int)(p%840);
            if(!tab.count(h)) continue;
            if(p<=k) continue;
            long long C=(p+k)/4;
            // factor C
            int pe[24]; long long pf[24]; int nf=0; long long c=C;
            for(int q:smallp){ if(1LL*q*q>c) break; if(c%q==0){pf[nf]=q;pe[nf]=0;while(c%q==0){c/=q;pe[nf]++;}nf++; } }
            if(c>1){pf[nf]=c;pe[nf]=1;nf++;}
            // divisor residues mod k
            uint64_t res[8]={0}; int W=(k+63)/64;
            auto setb=[&](int x){res[x>>6]|=1ULL<<(x&63);};
            auto getb=[&](int x){return (res[x>>6]>>(x&63))&1ULL;};
            setb(1%k);
            bool pure=true;
            for(int f=0;f<nf;f++){
                int r=(int)(pf[f]%k);
                if(jacobi(pf[f]%k,k)!=1) pure=false;
                // multiply existing residue set by r^1..r^e
                uint64_t base[8]; for(int w=0;w<W;w++) base[w]=res[w];
                int rr=1;
                for(int e=1;e<=pe[f];e++){
                    rr=(int)(1LL*rr*r%k);
                    for(int a=0;a<k;a++) if((base[a>>6]>>(a&63))&1ULL) setb((int)(1LL*a*rr%k));
                }
            }
            int t2=(int)((k-C%k)%k);
            bool miss = !getb(t1) && !getb(t2);
            auto&T=tab[h];
            T[0]++; if(miss)T[1]++; if(pure)T[2]++;
            if(miss&&!pure){T[3]++; if(ex1.size()<5)ex1.push_back({p,h});}
            if(pure&&!miss){T[4]++; if(ex2.size()<5)ex2.push_back({p,h});}
        }
        printf("\n=== k=%d , p < %lld , targets t1=%d ===\n",k,LIM,t1);
        printf("%6s %10s %10s %10s %12s %12s %8s\n","h","hard p","exact miss","pure miss","miss&!pure","pure&!miss","verdict");
        long long g[5]={0,0,0,0,0};
        for(int h:hs){auto&T=tab[h];for(int j=0;j<5;j++)g[j]+=T[j];
            printf("%6d %10lld %10lld %10lld %12lld %12lld %8s\n",h,T[0],T[1],T[2],T[3],T[4],(T[3]==0&&T[4]==0)?"OK":"FALSE");}
        printf("%6s %10lld %10lld %10lld %12lld %12lld\n","all",g[0],g[1],g[2],g[3],g[4]);
        if(!ex1.empty()){printf("  sample miss&!pure : ");for(auto&e:ex1)printf("p=%lld(h=%lld) ",e.first,e.second);printf("\n");}
        if(!ex2.empty()){printf("  sample pure&!miss : ");for(auto&e:ex2)printf("p=%lld(h=%lld) ",e.first,e.second);printf("\n");}
        fflush(stdout);
    }
}
