# Adaptive external-NR factor forcing

- status: **live conjecture / verified finite samples**
- source: 2026-09-04 adaptive external-NR factor-forcing note

## Claim under investigation

For every hard prime `p`, some external quadratic-nonresidue prime `r` produces an induced shift `k_r` whose known-factor box

`Div(s^2){1,r,r^2}{1,m,m^2}`

hits Type I or Type II, where `s=gcd(210,C_r)` and `m=C_r/(sr)`.

The construction itself is proved. The universal existence of a hitting `r` is not proved.

## Evidence

- all 30,061 `h=1` hard primes below `1e8` are hit by successive external-NR primes;
- two random 50,000-prime samples up to `9e18` had no failure within the tested bounds;
- grouping multiple NR factors mapping to one shift improves the observed maximum rank.

## Possible proof routes

1. Repeated miss states force external-NR valuation mass `E`, giving `C_r >= r^E`, then contradict a least-NR upper bound.
2. Transport the miss state between induced shifts in a quotient and prove it cannot persist for every external-NR prime.

The external-NR cycle alone is rejected as a complete proof route; exact Type I + Type II testing still leaves counterexample cycles.
