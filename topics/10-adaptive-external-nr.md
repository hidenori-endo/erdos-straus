# 10. Adaptive external-NR factor forcing

## Construction

Let `p` be hard, `N=(p+3)/4`, and let `r` be any odd prime with `(r/p)=-1`. Define

`j_r == -N (mod r)`, `k_r=4j_r+3`, `C_r=N+j_r`.

Then `r|C_r`, `3<=k_r<4r`, and transfer through quadratic reciprocity gives `chi_{k_r}(r)=-1`. If `s=gcd(210,C_r)` and `m=C_r/(sr)`, the known-factor box

`Div(s^2){1,r,r^2}{1,m,m^2}`

is contained in the exact `Div(C_r^2)` box. A target hit is therefore a valid Erdős–Straus certificate for `p`, without factoring `C_r`.

## Evidence

For every hard `h=1` prime below `1e8`, trying external-NR primes in order found a hit. The least external-NR prime alone hit 25,548 of 30,061; the worst first hit used the 17th NR prime (`p=62,739,601`, `r=191`). Grouping factors that map to the same shift reduced the maximum rank to 14.

Two random samples of 50,000 hard primes in the ranges `1e8..1e15` and `1e15..9e18` had no failures within the tested NR-prime bounds. This supports a conjecture, not a proof, and cannot imply a universal fixed bound on `r`.

## What it does and does not prove

The construction is stronger than the old fixed external-factor cycle experimentally, but the cycle route itself still has 864 combined-miss cycles below `1e7`. The useful next question is whether repeated adaptive misses force enough external-NR valuation mass to contradict `C_r`'s size, or whether a quotient transport argument rules out persistence across all induced shifts.

See [the detailed update](../updates/2026-09-04-adaptive-nr-factor-forcing.md), the [thin `k=23` state](../updates/2026-09-03-h1-k23-thin-state.md), and the complete scanners in `code/nr_adaptive.cpp`, `code/nr_group_adaptive.cpp`, `code/nr_adaptive_sample.cpp`, and `code/combined_cycle_scan.cpp`.
