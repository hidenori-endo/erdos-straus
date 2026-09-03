# Prime-or-complement factor lemma

- status: live / elementary lemma
- source: 2026-09-03 会話の追加検証
- confidence: exact coprime fab criterion からの直接導出。ES の universal proof ではない。

## 主張

coprime `a,b`、`M=4ab`、`L=a+bp`、`t=-p (mod M)` を固定する。L の prime-power
factor のうち M と共通するものを除き、残りを N、`c=N (mod M)` とする。

N の prime factor r について

- `r≡t (mod M)` なら r 自身が target divisor。
- `r≡ct^{-1} (mod M)` なら `N/r` が target divisor。

従って fab が miss するなら、N の全 prime factor はこの二つの residue を避ける。

## 証明

target t は unit なので、target に一致する divisor は M と共通する prime factor を
持たない。よって target divisor は N の約数である。r≡t なら自明に r が target。
また r≡ct^{-1} なら

~~~
(N/r) ≡ c r^{-1} ≡ c (ct^{-1})^{-1} ≡ t (mod M)。
~~~

いずれも fab の witness を与える。対偶で結論。

## 意義

finite-group closure や character annihilation を経由せず、exact divisor criterion から
linear form の forbidden prime-factor class を直接抽出できる。m=5,6 の小さい pair を
束ねて sieve にする際の共通補題になる。
