// Exact character-annihilation closure for shifts k = 3 (mod 4).
//
// Model:
//   p is a hard prime, h = p mod 840 in {1,121,169,289,361,529}, C_k = (p+k)/4.
//   A state is (S, c, neg): S = set of residues mod k of the divisors of C_k
//   built so far, c = C_k mod k, neg = "some prime factor used is a p-NR".
//   Consuming one more copy of a prime factor r sends
//       S -> S u rS,     c -> c*r,     neg -> neg or [chi(r) = -1].
//   Repeated application builds every exponent, so every real divisor set of
//   every admissible C_k is reachable: the closure over-approximates reality.
//   Type I target  : D = -1/4 (mod k)
//   Type II target : D = -C_k (mod k)
//   A "miss" is a state whose S avoids both targets while c lies in the exact
//   centre fibre {(h + 840t)/4 mod k}.  Annihilation = no miss has neg = 1.
//
// Lemma (verified by --selftest): for k = 3 (mod 4) and r | C_k we have
//   p = -k (mod r), hence (p/r) = (-k/r) = (-1/r)(k/r) = (-1/r)^2 (r/k)
//   = jacobi(r,k) -- the character depends only on r mod k.  For r = 2 the
//   same identity holds as Kronecker symbols since 2 | C_k forces p = -k (mod 8).
//
// NOTE.  The transition MUST be S -> S u rS.  An earlier version used
// S -> S u rS u r^2 S, which injects divisors r^2 that need not exist when r
// has exponent 1.  That over-full state hits a target where the real divisor
// set misses, producing FALSE annihilation -- it is what made k=35 look like
// it annihilated in classes 121 and 361.  See code/README.md.
//
// Env flags: NOPRUNE=1 disable the (sound) Type-I prune and report the full
//            reachable-state count;  FAST=1 stop at the first non-pure miss;
//            ALLK=1  include prime k as well as composite k.
#include <bits/stdc++.h>
using namespace std;

static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
static long long eg(long long a,long long b,long long&x,long long&y){if(!b){x=1;y=0;return a;}long long X,Y,g=eg(b,a%b,X,Y);x=Y;y=X-a/b*Y;return g;}
static int invm(int a,int m){long long x,y;eg(a,m,x,y);x%=m;if(x<0)x+=m;return x;}
static vector<int> facs(int g){vector<int>v;for(int p=2;1LL*p*p<=g;p++)if(g%p==0){v.push_back(p);while(g%p==0)g/=p;}if(g>1)v.push_back(g);return v;}
static bool isprime(int n){if(n<2)return 0;for(int p=2;1LL*p*p<=n;p++)if(n%p==0)return 0;return 1;}

// every center c = p/4 mod k compatible with p = h (mod 840)
static vector<int> centers(int k,int h){
    int d=(int)gcd(840,(long long)k),per=k/d,iv=invm(4,k);
    vector<int>v;vector<char>s(k,0);
    for(int t=0;t<per;t++){int p=(int)((h+1LL*(840%k)*t)%k);if(gcd(p,(long long)k)>1)continue;int c=(int)(1LL*p*iv%k);if(!s[c]){s[c]=1;v.push_back(c);}}
    return v;
}

struct State{vector<uint64_t>m;int c;int neg;
    bool operator==(const State&o)const{return c==o.c&&neg==o.neg&&m==o.m;}};
struct SH{size_t operator()(const State&s)const{size_t h=1469598103934665603ULL;for(uint64_t w:s.m){h^=w;h*=1099511628211ULL;}h^=(size_t)s.c*1000003+s.neg;return h;}};

struct Res{long long states=0,missTotal=0,missPure=0,missNonPure=0,pureHit=0;bool capped=false;
           int wc=-1,wneg=0;vector<int> wpath;};

static Res closure(int k,int h,const vector<int>&U,const vector<int>&seedPrimes,long long CAP){
    int W=(k+63)/64;
    auto get=[&](const vector<uint64_t>&m,int i){return (m[i>>6]>>(i&63))&1ULL;};
    auto tr=[&](const vector<uint64_t>&m,int r,vector<uint64_t>&out){
        out=m;
        for(int a:U) if(get(m,a)){int x=(int)(1LL*a*r%k);out[x>>6]|=1ULL<<(x&63);}
    };
    int tI=(k-invm(4,k))%k;
    vector<char>allow(k,0);for(int c:centers(k,h))allow[c]=1;

    State s0;s0.m.assign(W,0);s0.m[1>>6]|=1ULL<<(1&63);s0.c=1;s0.neg=0;   // divisor set {1}
    for(int r:seedPrimes){vector<uint64_t>t;tr(s0.m,r%k,t);s0.m=t;s0.c=(int)(1LL*s0.c*(r%k)%k);s0.neg|=jacobi(r,k)==-1;}

    Res R;
    unordered_map<State,vector<int>,SH> seen;seen.reserve(1<<12);
    deque<State> q;
    seen.emplace(s0,vector<int>{});q.push_back(s0);
    while(!q.empty()){
        State s=q.front();q.pop_front();
        vector<int> path=seen[s];
        R.states++;
        if(allow[s.c]&&!get(s.m,tI)&&!get(s.m,(k-s.c)%k)){
            R.missTotal++;
            if(s.neg){R.missNonPure++;if(R.wc<0){R.wc=s.c;R.wneg=1;R.wpath=path;}}
            else R.missPure++;
        } else if(allow[s.c]&&!s.neg){ R.pureHit++;
        }
        if(getenv("NOPRUNE")==nullptr&&get(s.m,tI)) continue;   // sound: mask only grows, Type I already hit
        if(R.states>CAP){R.capped=true;break;}
        for(int r:U){
            State n;tr(s.m,r,n.m);n.c=(int)(1LL*s.c*r%k);n.neg=s.neg|(jacobi(r,k)==-1);
            if(seen.count(n))continue;
            vector<int> np=path;np.push_back(r);
            seen.emplace(n,np);q.push_back(n);
        }
    }
    return R;
}

int main(int argc,char**argv){
    if(argc>1&&string(argv[1])=="--selftest"){
        // chi(r) = (p/r) = jacobi(r,k) for r | C_k, k = 3 mod 4.
        // r odd : (p/r) = (-k/r) = (-1/r)(k/r) = (-1/r)^2 (r/k) = (r/k).
        // r = 2 : 2 | C_k means p = -k (mod 8), so (2/p) = (2/k) as Kronecker symbols.
        long long bad=0,tot=0;
        for(int k=3;k<=203;k+=4)for(long long p=5;p<200000;p++){
            if(!isprime((int)p))continue;if(p%4!=1)continue;if(p<=k)continue;if((p+k)%4)continue;
            long long C=(p+k)/4;if(C<2)continue;
            vector<long long> pf;{long long c=C;for(long long r=2;r*r<=c;r++)if(c%r==0){pf.push_back(r);while(c%r==0)c/=r;}if(c>1)pf.push_back(c);}
            for(long long r:pf){
                if(gcd(r,(long long)k)>1){printf("gcd violation k=%d p=%lld r=%lld\n",k,p,r);bad++;continue;}
                tot++;
                int lhs = (r==2) ? jacobi(2,p) : jacobi(p%r,r);
                if(lhs!=jacobi(r%k,k))
                    {if(bad<5)printf("mismatch k=%d p=%lld r=%lld  (p/r)=%d (r/k)=%d\n",k,p,r,lhs,jacobi(r%k,k));bad++;}
            }
        }
        printf("selftest: %lld pairs, %lld mismatches\n",tot,bad);return bad?1:0;
    }
    int M=argc>1?atoi(argv[1]):300;long long CAP=argc>2?atoll(argv[2]):2000000;
    vector<int>hs={1,121,169,289,361,529};
    printf("k,h,seed,states,miss,pure,nonpure,pureHIT,annihilates,capped,witness\n");
    for(int k=3;k<=M;k+=4){
        if(!getenv("ALLK")&&isprime(k))continue;
        vector<int>U;for(int x=1;x<k;x++)if(gcd((long long)x,(long long)k)==1)U.push_back(x);
        for(int h:hs){
            long long Ck=(h+k)/4;                    // C_k mod 210 is class-determined
            int seed=(int)gcd(210LL,Ck);
            vector<int> sp=facs(seed);
            bool clash=false;for(int r:sp)if(gcd((long long)r,(long long)k)>1)clash=true;
            if(clash){printf("%d,%d,%d,,,,,SKIP-seed-shares-factor,,\n",k,h,seed);continue;}
            Res R=closure(k,h,U,sp,CAP);
            string w;for(size_t i=0;i<R.wpath.size();i++){if(i)w+="|";w+=to_string(R.wpath[i]);}
            printf("%d,%d,%d,%lld,%lld,%lld,%lld,%lld,%s,%s,%s\n",k,h,seed,R.states,R.missTotal,R.missPure,
                   R.missNonPure,R.pureHit,(R.missNonPure==0?"YES":"no"),(R.capped?"CAPPED":""),w.c_str());
            fflush(stdout);
        }
    }
}
