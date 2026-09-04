# 2026-09-03: seed-kernel necessity for all k

Let `k == 3 (mod 4)`, `h in {1,121,169,289,361,529}`,
`G=(Z/kZ)^x`, `chi(x)=jacobi(x,k)`, `Q=ker chi`,
`seed=gcd(210,(h+k)/4)`, and `H=<seed prime divisors mod k>`.

## Theorem

`character annihilation => H = Q` for every admissible `k` and hard class.

The implication is a construction of a reachable non-pure miss state in the closure model. It does not claim that every abstract support state is realized by an actual prime. The positive 30-pair classification is separate and uses boxes contained in the true `Div(C_k^2)` box.

## 1. H is contained in Q

Every seed prime is one of `2,3,5,7`.

- If `2|seed`, then the hard class condition gives `k == 7 (mod 8)`, so `(2/k)=+1`.
- If `q in {3,5,7}` divides the seed, then `h == -k (mod q)`. Since hard `h` is a square modulo `q`, quadratic reciprocity with `k == 3 (mod 4)` gives `(q/k)=+1`.

Thus all seed generators lie in `Q`, so `H subset Q`.

## 2. Quotient construction

Because `chi(-1)=-1`, write

`G/H ~= A x <epsilon>`, where `A=Q/H` and `epsilon=-H`.

Put `a=4H`. Since `a=(2H)^2`, it is a square in `A`.

For `g=gcd(k,210)`, the exact center fiber is a coset of the reduction kernel. Every hard class is an integer square (`1,121,169,289,361,529`), so its image in the quotient is a square coset. In particular the fiber image contains a QR point.

## 3. Three reachable miss constructions

Type I uses one NR factor `r` with quotient coordinate `epsilon*x`. If the fiber contains such a point and

`x not in {1,a^-1}`,

then `H{1,r,r^2}` is a non-pure miss.

Type II-internal uses `1` in the fiber and a quotient coordinate

`x not in {1,a^-1,a}`.

For two NR factors `r1 H=epsilon*x`, `r2 H=epsilon*y`, the center coordinate is `xy`. The NR coordinates in the box are

`{x,y,xy^2,x^2y}`.

Type II misses whenever `x!=1` and `y!=1`; Type I additionally requires `a^-1` to be outside this set. Fixing `z=xy`, the bad choices of `x` are among

`1, z, a^-1, az, az^2, a^-1 z^-1`.

Therefore if `|A|>6`, the quotient two-factor construction always gives a non-pure miss.

## 4. The finite cases

Only `2 <= |A| <= 6` remain. Exhausting the finite abelian groups

`C2, C3, C4, C2 x C2, C5, C6`

with the square constraints on `a` and the center coset gives 187 configurations. All failures of the three constructions have one of these shapes:

1. `A=C3`, trivial center-kernel image;
2. `A=C5`, trivial center-kernel image;
3. `A=C3`, center-kernel image `{H,-H}`.

They are arithmetically impossible. Since `g=gcd(k,210)|105`, `phi(g)` is one of `1,2,4,6,8,12,24,48`; the allowed seed generators modulo `g` give no required subgroup size. The only formal survivor is `g=7`, seed `1`, `|A|=3`, which would force `phi(k)=6` and hence `k=7`; but then the hard-class congruence forces `2|seed`, a contradiction.

Hence `H<Q` always yields a reachable non-pure miss, proving `annihilation => H=Q` without a range restriction.

## 5. Cross-checks

The original exact-residue implementation and the quotient implementation agree:

```text
k<=403:  H=Q 389, E1 181, E2i 25, E2g 11, uncovered 0
k<=10000: H=Q 7187, E1 7506, E2i 263, E2g 44, uncovered 0
```

The remaining global problem is no longer the local character classification, but the interaction of multiple shifts and the actual prime support of consecutive cofactors.
