# 2026-09-04: adaptive external-NR factor forcing

## 1. Construction

Let `p` be a Mordell-hard prime and set `N=(p+3)/4`. For an odd prime `r<p` with `(r/p)=-1`, choose

`j_r == -N (mod r)`, `0 <= j_r < r`,

and define

`k_r=4j_r+3`, `C_r=N+j_r=(p+k_r)/4`.

Then `k_r == 3 (mod 4)`, `3 <= k_r < 4r`, `r|C_r`, and fixed-shift transfer plus reciprocity gives

`chi_{k_r}(r)=Jacobi(r,k_r)=(p/r)=(r/p)=-1`.

Thus every external quadratic-nonresidue prime canonically supplies both an admissible shift and a known NR factor in its exact box. With

`s=gcd(210,C_r)`, `m=C_r/(s r)`,

the explicit box

`B_r=Div(s^2){1,r,r^2}{1,m,m^2}`

is contained in `Div(C_r^2)`. A hit of either target `-1/4` or `-C_r` proves the desired representation for `p`; no factorization of `C_r` is needed.

## 2. Finite and large-prime experiments

For all 30,061 `h=1` hard primes below `1e8`, the least external-NR prime gives a hit for 25,548. Trying successive external-NR primes hits all 30,061; the largest first-hit prime is `r=191`, at the 17th external-NR rank, for `p=62,739,601`.

Grouping several external-NR primes that induce the same `k` still hits all 30,061 and reduces the maximum rank from 17 to 14.

Random tests in all six hard classes found no failures:

- 50,000 primes in `1e8 < p < 1e15`, testing `r <= 10,000`;
- 50,000 primes in `1e15 < p < 9e18`, testing `r <= 20,000`.

The largest observed first-hit prime was around 463. These are finite computational observations, not a universal bound on `r`; CRT and Dirichlet permit prescribed small primes to be QR.

## 3. Least-NR parity/mass lemma

Let `r` be the least prime with `(r/p)=-1` and suppose the induced `k=k_r` satisfies `k<r`. Every prime divisor `q|k` is then smaller than `r`, so `(q/p)=+1` and `Jacobi(p,k)=+1`. Since `p == 4C (mod k)`, this gives `chi_k(C)=+1`. The known factor `r|C` has `chi_k(r)=-1`, so another NR factor `q|C` must exist. Transfer gives `(q/p)=-1`, hence `q>=r`. Therefore

`C>=r^2`, and from `4C=p+k` with `k<r`,

`p>4r^2-r`.

More generally, a defect theorem forcing `E` external-NR valuation units gives `C>=r^E`. Combining this with a least-NR upper bound is a possible analytic route.

## 4. External cycle cross-check

The external-NR factor-cycle route remains insufficient even with the exact two-target `Div(C^2)` box. The Type-I-only counterexample `p=5569` is hit by Type II at its first vertex `k=39`, `C=1402`, but a scan below `1e7` still reports

```text
hard primes:              20,513
combined hit before cycle:19,649
combined-miss cycle:         864
```

The adaptive factor-forcing route is therefore a distinct, empirically stronger route rather than a proof of the cycle conjecture.

## 5. Current conjecture and next questions

The finite evidence supports:

`For every hard prime p, some external NR prime r has B_r hitting one of the two exact targets.`

This remains unproved. The next precise questions are whether repeated misses force enough external-NR mass to contradict the size of `C_{k_r}`, or whether miss states can be transported between induced shifts in a quotient where persistence is impossible.
