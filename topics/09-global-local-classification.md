# 09. Global local classification of character annihilation

## Definitions

For `k == 3 (mod 4)` and a hard class `h`, let

`G=(Z/kZ)^x`, `chi=jacobi(.,k)`, `Q=ker chi`,
`s=gcd(210,(h+k)/4)`, and `H=<prime divisors of s mod k>`.

The exact center set is a fiber of `G_k -> G_g`, where `g=gcd(k,840)`. Its image is a square coset because every hard class is an integer square.

## The global local result

Every seed prime is QR, so `H subset Q`. If `H<Q`, set `A=Q/H`. The quotient satisfies:

- `4H` is a square in `A`;
- the center image is a square coset;
- the NR H-cosets are `(-H)x`, `x in A`.

The one-NR, internal two-NR, and quotient two-NR constructions give a reachable non-pure miss unless `|A|<=6`. The finite abelian groups of orders 2 through 6 yield 187 configurations; the three residual abstract shapes are all ruled out by the arithmetic restrictions `g|105` and the allowed seed primes `{2,3,5,7}`.

Therefore

`character annihilation => H=Q`

for every admissible `k` and hard class. This is a range-free local theorem. The exact quotient proof is in [the update note](../updates/2026-09-03-seed-kernel-global-proof.md). The attached finite checker `quotient_necessity_proof.py` was truncated in the source conversation and is not committed as runnable code.

## Combining with the H=Q classification

Under `H=Q`, the exact center fiber has three regimes:

| center fiber | successful pairs |
|---|---:|
| fixed | 20 |
| full | 10: `k=11,19,31,47,59` |
| intermediate | 0 |

Thus the parity-aware minimal-box / finite-closure mechanism has exactly 30 successful `(k,h)` pairs for all `k`.

This is a local character classification, not an Erdős–Straus proof. The negative side constructs abstract closure miss states; it does not assert that a prime realizes each such state. The remaining problem is to use multiple shifts and actual prime support, especially consecutive cofactors.
