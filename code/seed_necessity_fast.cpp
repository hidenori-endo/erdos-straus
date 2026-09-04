#include <bits/stdc++.h>
using namespace std;
static int jacobi(long long a,long long n){a%=n;if(a<0)a+=n;int s=1;while(a){while(!(a&1)){a>>=1;int r=n&7;if(r==3||r==5)s=-s;}swap(a,n);if((a&3)==3&&(n&3)==3)s=-s;a%=n;}return n==1?s:0;}
static long long eg(long long a,long long b,long long&x,long long&y){if(!b){x=1;y=0;return a;}long long X,Y,g=eg(b,a%b,X,Y);x=Y;y=X-a/b*Y;return g;}
static int invm(int a,int m){long long x,y;assert(eg(a,m,x,y)==1);x%=m;if(x<0)x+=m;return x;}
static vector<int> spr(int s){vector<int>v;for(int q:{2,3,5,7})if(s%q==0)v.push_back(q);return v;}
static vector<int> subgroup(int k,const vector<int>&gs){vector<int>H={1};vector<char>seen(k);seen[1]=1;deque<int>q;q.push_back(1);while(!q.empty()){int a=q.front();q.pop_front();for(int g:gs){int x=1LL*a*g%k;if(!seen[x])seen[x]=1,H.push_back(x),q.push_back(x);}}return H;}
int main(int argc,char**argv){int M=argc>1?atoi(argv[1]):5000;int hs[]={1,121,169,289,361,529};long long ge=0,e1=0,e2i=0,e2g=0,none=0;vector<pair<int,int>> unc;int maxE2gk=0;
 for(int k=3;k<=M;k+=4){vector<int>U,Q,NR;vector<char>qmark(k);for(int x=1;x<k;x++)if(gcd(x,k)==1){U.push_back(x);if(jacobi(x,k)==1)Q.push_back(x),qmark[x]=1;else NR.push_back(x);}int iv4=invm(4,k),t1=(k-iv4)%k;
  for(int h:hs){int s=gcd(210,(h+k)/4);auto H=subgroup(k,spr(s));vector<char>hm(k);for(int x:H)hm[x]=1;bool contains=true;for(int q:Q)if(!hm[q]){contains=false;break;}if(contains){ge++;continue;}
   int g=gcd(210,k),c0=((h+k)/4)%g;vector<int>F;vector<char>fm(k);for(int x:U)if(x%g==c0)F.push_back(x),fm[x]=1;
   vector<char>forb1(k),HF(k);for(int a:H){forb1[(k-a)%k]=1;forb1[(k-(int)(1LL*iv4*a%k))%k]=1;for(int b:F)HF[1LL*a*b%k]=1;}
   bool ok=false;for(int r:NR)if(!forb1[r]&&HF[r]){ok=true;break;}if(ok){e1++;continue;}
   vector<char>forb2=forb1;for(int a:H)forb2[(k-(int)(4LL*a%k))%k]=1;bool FH=false;for(int x:F)if(hm[x]){FH=true;break;}if(FH){for(int r:NR)if(!forb2[r]){ok=true;break;}}if(ok){e2i++;continue;}
   bool found=false;vector<char>S(k);
   for(size_t i=0;i<NR.size()&&!found;i++){int r1=NR[i];int p1[3]={1,r1,(int)(1LL*r1*r1%k)};
    for(size_t j=i;j<NR.size()&&!found;j++){int r2=NR[j];int p2[3]={1,r2,(int)(1LL*r2*r2%k)};fill(S.begin(),S.end(),0);
     for(int a:H)for(int b:p1)for(int d2:p2)S[1LL*a*b%k*d2%k]=1;if(S[t1])continue;int rr=1LL*r1*r2%k;
     for(int h0:H){int c=1LL*h0*rr%k;if(fm[c]&&!S[(k-c)%k]){found=true;break;}}
    }
   }
   if(found){e2g++;maxE2gk=max(maxE2gk,k);}else{none++;unc.push_back({k,h});if(unc.size()<=20)cerr<<"UNC "<<k<<","<<h<<"\n";}
  }
 }
 cout<<"M="<<M<<" H>=Q="<<ge<<" E1="<<e1<<" E2i="<<e2i<<" E2g="<<e2g<<" none="<<none<<" maxE2gk="<<maxE2gk<<"\n";
 if(!unc.empty()){cout<<"uncovered:";for(auto [k,h]:unc)cout<<" ("<<k<<","<<h<<")";cout<<"\n";}
}
