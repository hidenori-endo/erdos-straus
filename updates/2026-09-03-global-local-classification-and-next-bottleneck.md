# 2026-09-03: global local-classification and the next bottleneck

## Closed result

With `H=<seed>` and `Q=ker chi`, the quotient argument removes the previous `k<=403` restriction from

`annihilation => H=Q`.

The exact center fiber is a square coset. If `[Q:H]>6`, the quotient two-NR construction has at most six forbidden choices and produces a miss. The remaining finite groups of order 2 through 6 give 187 configurations; the only abstract exceptions are the three shapes recorded in [the global proof](2026-09-03-seed-kernel-global-proof.md), and all are arithmetically impossible.

Combining this with the `H=Q` classification gives:

| center fiber | successful pairs |
|---|---:|
| fixed | 20 |
| full | 10 |
| intermediate | 0 |

Thus the local parity-aware minimal-box / closure mechanism has exactly 30 successful `(k,h)` pairs for all `k`.

## Cross-shift check

The 30 unconditional shifts do not by themselves prove Erdős–Straus. For `p<1e8`, 179,468 hard primes were factored and tested against all class-specific pure-support constraints; 7,452 primes still satisfy all of them.

| h | hard p | all local-pure survivors |
|---:|---:|---:|
| 1 | 30,061 | 4,810 |
| 121 | 29,900 | 316 |
| 169 | 29,898 | 447 |
| 289 | 29,907 | 130 |
| 361 | 29,828 | 1,223 |
| 529 | 29,874 | 526 |
| total | 179,468 | 7,452 |

An adaptive greedy scan eliminates the finite sample, for example for `h=1` with

`23 -> 47 -> 167 -> 71 -> 119 -> 19 -> 11 -> 59 -> 91`,

but this is not a proof. A fixed finite route is unsafe because large-prime support can vary independently.

## Next bottleneck

The next problem is to combine consecutive cofactors such as `R` and `R+1` after a thin miss state has restricted the support of `C_23=6R`. The useful approaches are:

- adaptive or conditional annihilation, where a miss at one shift restricts the next support;
- a sieve plus a genuinely non-sieve final argument, because a finite sieve alone encounters the parity barrier.

The external-NR factor-forcing construction in the 2026-09-04 note is a new route toward this bottleneck.
