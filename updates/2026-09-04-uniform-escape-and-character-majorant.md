# 2026-09-04: uniform escape audit and character-compressed majorant

This update tests the next proposed step after the fixed-budget finite-group sieve: make
the subgroup escape bound uniform while allowing the layer budget `D` to grow.  The
outcome has three parts.

1. Complementing a divisor normalizes the target from `-(p+4e)` to `-1`.  The union over
   arbitrary subgroups can then be compressed **exactly** to a union over odd characters.
2. A uniform constant escape bound is false at the finite-group level, even when the
   target is the normalized layer target `-1`.
3. The normalized escape is at most two on every actual simultaneous survivor tested.
   The previously recorded escape three for `p=3361` used the unnormalized target
   `-(p+4e)`; after taking the complementary divisor its minimum is one.

Reproduction code: `code/progressive_escape.cpp`, `code/escape_counterexample.cpp`, and
the extended `code/sieve_budget.cpp`.

## 1. Character compression is exact

For a finite abelian group `G`, a sequence `g_1,...,g_s`, and `t in G`, define

~~~
b_H(g,t) = #{i : g_i notin H},
~~~

where multiplicity is retained.  The stabilizer lemma in the preceding update produces
a subgroup `H<=G` such that `t notin H` and `b_H(g,t)<=|G|-1` whenever the subset products
miss `t`.

> **Lemma 8 (character-kernel compression).**
>
> ~~~
> min_{H<=G, t notin H} b_H(g,t)
>   = min_{chi in dual(G), chi(t) != 1} #{i : chi(g_i) != 1}.
> ~~~

**Proof.**  Character kernels are subgroups, so the left side is at most the right side.
Conversely, given `H` avoiding `t`, the nonidentity element `tH` of `G/H` is separated
from the identity by some character of `G/H`.  Pull it back to a character `chi` of `G`.
Then `H subset ker(chi)` and `chi(t)!=1`, so every term outside `ker(chi)` is also outside
`H`.  The character cost is therefore at most `b_H(g,t)`.  Taking minima gives the reverse
inequality.  QED.

For a layer `(d,e)`, with `n=p+4e`, `m=4d`, and `p` not dividing `d`, complementing a
divisor gives

~~~
some k|n has k == -n (mod m)
  iff some l|n has l == -1 (mod m).
~~~

Indeed `l=n/k`, and `n/k == -1` is equivalent to `k == -n` because `d|e` and hence
`gcd(n,m)=gcd(p,4d)=1`.
Consequently a missed layer gives the exact cover

~~~
there is an odd character chi modulo 4d with
Omega_{chi(q) != 1}(n) <= phi(4d)-1.
~~~

There are exactly `phi(4d)/2` odd characters.  Thus arbitrary subgroup assignments and
the old residue-class split used to fix the target are unnecessary.  Through budget `D`,
the number of character assignments is at most

~~~
C_D = product_{d<=D} (phi(4d)/2)^(2^omega(d)),
log C_D <= L(D) log(2D).
~~~

This is a rigorous explicit `exp(O(L(D) log D))` combinatorial bound.  Its exponential
base still grows with `D`, so it does not yet meet a fixed-base `exp(O(L(D)))` target.  Nor
does it by itself give a uniform analytic sieve estimate: the permitted-factor tail and
uniform prime distribution in the changing character moduli still have to be controlled.

## 2. A group-only constant escape bound is impossible

Let `G=C_(2m)=<g>`, let `j=g^m` be its element `-1`, and take `m-1` copies of `g`.  The
normalized layer target is

~~~
t = j = g^m.
~~~

The available subset products are exactly `1,g,...,g^(m-1)`, so they miss `t`.  If a
subgroup `H` contained `g`, it would also contain `g^m=t`.  Consequently every subgroup
avoiding `t` excludes all `m-1` sequence terms, and the minimum escape is `m-1`.  It is
unbounded.

This pattern also lives in the same unit groups as the layers.  For a prime `q=3 mod 4`,
put `m=(q-1)/2` and choose a primitive root `a mod q`.  The CRT element
`g=(3 mod 4, a mod q)` in `(Z/4qZ)^*` has order `2m` and satisfies `g^m=-1`.  Dirichlet's
theorem supplies arbitrarily many rational primes in the residue class `g mod 4q`, so an
integer made from `m-1` such prime factors realizes the sequence above.

What this construction **does not** prove is that `p=n-4e` can simultaneously be prime
and hard for `e=q` or `q^2`.  That extra shifted-prime condition is unverified.  The result
is therefore a no-go theorem for a purely finite-group constant bound, not a counterexample
to a possible arithmetic theorem about actual common layer survivors.

`escape_counterexample.cpp` enumerates all subgroups of `C_(2m)` and asserts
`minimum_escape=m-1`; it passes for every tested `2<=m<=31`.

## 3. Progressive audit on actual hard primes

`progressive_escape.cpp` (run here with `D=32`) uses exact divisor-residue dynamic programming and independently
enumerates every subgroup of `(Z/4dZ)^*`.  For each prime surviving all layers through a
checkpoint `D`, it computes the exact minimum in Lemma 8 for every missed layer.

For all hard primes `11<=p<10^8`:

| `D` | survivors | character misses | multiplicity misses | maximum escape |
|---:|---:|---:|---:|---:|
| 1 | 95,458 | 95,458 | 0 | 0 |
| 2 | 33,385 | 100,155 | 0 | 0 |
| 3 | 11,745 | 58,725 | 0 | 0 |
| 4 | 4,771 | 32,101 | 1,296 | 2 |
| 6 | 561 | 7,024 | 269 | 2 |
| 8 | 247 | 3,903 | 296 | 2 |
| 10 | 50 | 1,036 | 114 | 2 |
| 12 | 16 | 427 | 37 | 2 |
| 16 | 3 | 109 | 14 | 2 |
| 18 | 2 | 84 | 10 | 2 |
| 24 | 1 | 59 | 8 | 2 |
| 25 | 0 | 0 | 0 | 0 |
| 32 | 0 | 0 | 0 | 0 |

The obstruction counts are totals over all missed layers for all survivors in the row,
not counts of primes.  In the subrange `10^6<=p<10^8`, the survivor counts are 232 at
`D=8`, 2 at `D=16`, 1 at `D=18`, and 0 at `D=24`; every observed multiplicity escape is
at most two there.

The apparent exception to the tentative bound two under the old target was

~~~
p=3361, (d,e)=(17,17), p+4e=3429=3^3*127.
~~~

Its minimum escape is three when separating `-(p+4e)`, but only **one** when separating
the equivalent target `-1`.  Thus it is not a counterexample to normalized escape two.
This prime survives all Type-II layers through `D=24`, then hits `(d,e)=(25,125)` because
`p+4e=3861` has divisor `39 == -3861 (mod 100)`.  The other two primes surviving `D=16`
below `10^8` are caught by `(18,108)` and `(24,96)`:

| `p` | first later hit |
|---:|---:|
| 3,361 | `(25,125)` |
| 4,722,169 | `(24,96)` |
| 24,887,641 | `(18,108)` |

These are finite computations, not a proof of any bound beyond the stated range.

## 4. What the improved majorant does and does not fix

The character assignment budget is much smaller and more explicit than an arbitrary
subgroup union:

| `D` | `L(D)` | `B_D` | `log C_D` | `C_D^(1/L(D))` |
|---:|---:|---:|---:|---:|
| 8 | 17 | 121 | 21.6 | 3.56 |
| 16 | 41 | 561 | 75.2 | 6.26 |
| 24 | 67 | 1,367 | 146.8 | 8.94 |
| 32 | 93 | 2,493 | 226.5 | 11.42 |
| 64 | 211 | 11,143 | 647.8 | 21.55 |
| 128 | 477 | 49,717 | 1,777.2 | 41.50 |

For a character whose kernel has index `r`, the excluded primes have density
`delta=1-1/r>=1/2`.  The permitted-factor part of the sieve has the Poisson-tail shape

~~~
exp(-lambda) sum_{j<=b} lambda^j/j!,
lambda approximately delta log log x.
~~~

This factorial refinement is better than simply writing `(log log x)^b`, but it exposes
the same obstruction: once the guaranteed allowance `b=phi(4d)-1` is much larger than
`log log x`, the tail is close to one and that layer gives no forced saving.  The cyclic
family above proves that `b` cannot be replaced by an absolute constant using group
structure alone.

Therefore character compression makes the **subgroup-counting** part of the proposed
uniform majorant explicit and smaller, but does not fully remove its cost and does not fix
the dominant **escape-tail** part.  The current independent-layer majorant still cannot
make the exceptional count less than one.

## 5. Best next target

The data point to a narrower statement than uniform escape for every layer.  For a missed
layer define

~~~
b_(d,e)(p) = min_{chi odd modulo 4d} Omega_{chi(q) != 1}(p+4e).
~~~

A useful completion lemma would only need to show that, for a prime missing all layers
through `D`, a positive proportion of those layers have `b_(d,e)(p)<=B` for one absolute
`B`, or an averaged analogue strong enough to keep the product of the Poisson tails small.
The finite audit supports this on its tested range (`B=2`), while Lemma 8 makes the
corresponding character sieve explicit.  The cyclic counterexample shows that such a
lemma must use the shared prime `p`, the relations between the shifts `p+4e`, or primality;
it cannot follow from the subset-product state of each layer separately.

Accordingly, the most direct remaining route is now:

1. classify high-escape (`b>=3`) factorizations of `p+4e` by a character kernel;
2. use the fixed differences `4(e'-e)` to show that many such classifications cannot
   coexist across layers;
3. insert that simultaneous low-escape proportion into the character-summed sieve.

This replaces the earlier vague goal “make the finite subgroup union uniform” with a
specific arithmetic cross-layer lemma.

The subsequent [complement-normalization audit](2026-09-04-complement-normalization-and-cross-layer-audit.md)
proves that complementary divisors replace the moving target by `-1`, so only odd
characters are needed.  It verifies normalized escape at most two on every common
survivor through `p<10^8`, but does not prove the resulting cross-layer conjecture.
