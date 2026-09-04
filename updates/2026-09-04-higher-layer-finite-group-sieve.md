# 2026-09-04: higher layers and a finite-group sieve lemma

The next step after the exponent-two character sieve is to handle `d=4,5,7,8`, where
`(Z/4d Z)^*` has exponent greater than two and the actual prime multiplicities matter.
The result is that multiplicity does not destroy the sieve route: every miss is still a
finite-union condition with only boundedly many prime factors outside a proper subgroup.

Reproduction code: `code/higher_layers.cpp`.

## 1. Exact miss versus subgroup miss

For a layer `(d,e)`, put `m=4d`, `n=p+4e`, and `t=-n (mod m)`.  List the prime factors of
`n` with multiplicity as `g_1,...,g_s in G=(Z/mZ)^*`.  The divisor residues of `n` are the
subset products

~~~
S_0={1},       S_i=S_{i-1} union g_i S_{i-1}.
~~~

Thus there are two kinds of exact miss.

- **subgroup/character obstruction:** `t` is outside `<g_1,...,g_s>`;
- **multiplicity obstruction:** `t` is in that subgroup but outside the actual subset-product set `S_s`.

The second kind is exactly what made the subgroup test fail for `d=4,5,7,8` in the earlier
note.

## 2. Stabilizer escape lemma

> **Lemma 6 (bounded escape from a proper subgroup).**  Let `G` be a finite abelian group,
> let `g_1,...,g_s` be a sequence in `G`, and let `S` be its subset-product set.  If
> `t notin S`, there is a subgroup `H<=G`, with `t notin H`, such that at most `|G|-1`
> terms `g_i` lie outside `H`.

**Proof.**  Set `H=Stab(S)={h in G:hS=S}`.  Since `1 in S`, `H subset S`, hence `t notin H`.
If adding `g_i` does not enlarge the current subset-product set, then `g_i` stabilizes that
current set.  Because `G` is abelian, it continues to stabilize every later set, so
`g_i in H`.  Therefore every term outside `H` causes a strict increase in `|S_i|`.  There
are at most `|S|-1<=|G|-1` such increases.  This proves the lemma.  QED.

Applied to a layer miss, the lemma says

~~~
there is H <= (Z/4dZ)^*,  t notin H,
such that Omega_{q mod 4d notin H}(p+4e) <= phi(4d)-1.
~~~

The subgroup itself may depend on `p`, but there are only finitely many subgroups for fixed
`d`.  A pure character obstruction is the special case with zero escaping factors;
multiplicity obstruction merely permits a bounded number of them.

## 3. Fixed-budget density theorem

Let

~~~
L(D) = sum_{d<=D} 2^omega(d).
~~~

This is exactly the number of Type-II layers with `d(e)<=D`: for each prime power in `d`,
the exponent of `e` is either `2b-1` or `2b`.  Different layers have different shifts
`p+4e` because `d(e)` is uniquely determined by `e`.

Fix `D` and discard the finitely many `p<=D`.  By complementing divisors, a layer hit is
equivalent to `p+4e` having a divisor `-1 (mod 4d)`, so the target is fixed without
splitting `p` modulo an lcm.  For each layer choose one of the finitely many subgroups
supplied by Lemma 6.  A prime `q` outside that subgroup excludes the residue
`p=-4e (mod q)`.  For `q>D^2` these residues are distinct between layers.
Because a proper subgroup has index at least two, each layer excludes at least half of the
prime residue classes modulo `4d`, on average.  Including the residue `p=0 (mod q)` for
primality gives sieve dimension at least

~~~
1 + L(D)/2.
~~~

Lemma 6 permits at most

~~~
B_D = sum_{d<=D} 2^omega(d) (phi(4d)-1)
~~~

escaping prime factors.  The standard upper-bound sieve with at most `B_D` permitted
sifting-prime factors costs only a factor `(log log x)^B_D`.  The Chinese remainder
remainders are the same elementary interval remainders as in Theorem 5.  Hence:

> **Theorem 7 (all fixed Type-II layers).**  For every fixed `D`, the number `E_D(x)` of
> hard primes `p<=x` missed by every Type-II layer with `d(e)<=D` satisfies
>
> ~~~
> E_D(x) <<_D x (log log x)^B_D / (log x)^(1+L(D)/2).
> ~~~

Since `L(D)>=D`, this has an immediate consequence for hypothetical Erdős--Straus
counterexamples `E(x)`:

> **Corollary 7.1.**  For every fixed `A>0`, `E(x) <<_A x/(log x)^A`.

Choose a fixed `D` with `L(D)/2>A`; the fixed power of `log log x` is absorbed by the
remaining power of `log x`.  This is not competitive with the strongest known analytic
exceptional-set estimates, but it is derived directly from the exact layer criterion and
shows rigorously that the layer sieve dimension is unbounded.

## 4. Finite audit for `D<=8`

There are 17 layers through `D=8`: the nine exponent-two layers plus

~~~
(4,8), (4,16), (5,5), (5,25),
(7,7), (7,49), (8,32), (8,64).
~~~

For `10^6<=p<10^8`:

- hard primes: 177,098;
- missed by all nine exponent-two layers: 3,352;
- missed by all 17 layers: 232.

Among those 232 residual primes, the eight higher layers split as follows:

| character-obstructed higher layers | 3 | 4 | 5 | 6 | 7 | 8 |
|---:|---:|---:|---:|---:|---:|---:|
| primes | 1 | 2 | 20 | 56 | 88 | 65 |

The single case with only three character-obstructed layers is `p=98,697,601`; its other
five layers are multiplicity obstructions.  Among these 232 all-layer residual primes,
the minimum number of factors outside a subgroup avoiding the target is at most **2** in
every multiplicity-obstructed layer, far below the general bound `phi(4d)-1` (at most 15
here).  Before imposing all eight higher-layer misses, the observed maximum is 4, attained
in the `d=7` layers.

The all-17 failure counts are 50 in `[10^6,10^7)` and 182 in `[10^7,10^8)`, exactly
matching the previous `fast_layers.cpp` cumulative `D=8` counts.  The new program obtains
them independently through exact divisor-residue dynamic programming and additionally
records the obstruction type.

## 5. Remaining completion bottleneck

The fixed-`D` problem is now closed at the level of logarithmic density bounds.  What is
not controlled is uniformity in growing `D`:

- the residue-class splitting modulus grows like an lcm;
- the number of subgroup assignments grows rapidly;
- the crude escape allowance `B_D` grows rapidly;
- small sifting primes `q<=D^2` cannot use distinct-shift counting.

Therefore Theorem 7 cannot yet take `D=D(x)` and cannot make the exceptional count less
than one.  The next useful target is to replace the subgroup-by-subgroup finite union with
a uniform majorant whose constants are polynomial or singly exponential in `L(D)`, and to
determine how large `D(x)` the sieve level permits.  This is now the precise gap between
arbitrarily strong fixed logarithmic savings and a universal proof.

The size of the current parameters (`code/sieve_budget.cpp`) is:

| `D` | `L(D)` | dimension | `B_D` | `B_D/L(D)` |
|---:|---:|---:|---:|---:|
| 8 | 17 | 9.5 | 121 | 7.1 |
| 16 | 41 | 21.5 | 561 | 13.7 |
| 32 | 93 | 47.5 | 2,493 | 26.8 |
| 64 | 211 | 106.5 | 11,143 | 52.8 |
| 128 | 477 | 239.5 | 49,717 | 104.2 |

Ignoring the already-uncontrolled implied constant, the logarithm of the bound contains

~~~
log x - (L(D)/2) log log x + B_D log log log x.
~~~

Thus the crude stabilizer allowance grows too quickly to make the displayed bound less
than one: increasing `D` strengthens the negative sieve term but makes the permitted-factor
term larger at roughly `D` times the rate per layer.  This is a limitation of the current
majorant, not a no-go theorem for the layer route.  The finite audit's observed escape cost
at most 2 shows exactly where a sharper uniform lemma could change the balance.  The
subsequent [uniform escape audit](2026-09-04-uniform-escape-and-character-majorant.md)
proves an exact character-kernel compression, but also finds both a group-theoretic
unbounded-escape family and an apparent escape-3 case at `p=3361`, `(d,e)=(17,17)`.
Complementing the divisor normalizes the target to `-1` and lowers that case to escape 1;
all normalized simultaneous survivors tested have escape at most 2.  The group-theoretic
family remains, so any proof of a uniform arithmetic bound must still use simultaneous
relations between layers rather than a layer-by-layer finite-group bound.
