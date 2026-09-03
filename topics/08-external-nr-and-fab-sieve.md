# 08. External-NR、full box、fab sieve

## 問題の分離

external quadratic-nonresidue prime を使う route には少なくとも三つのレベルがある。

1. squarefree aligned-shield の forced seed だけを使う限定 rule。
2. `C_q` の全 cofactor を含む full signed box。
3. full box を coprime `fab(p,a,b)` の linear-form sieve として見る座標。

今回、1 の bounded-rank と cycle descent は no-go になったが、2 と 3 はまだ開いている。

## External-NR cycle

`p=3361` の `53→31→1103→1051→281→11→53` cycle は各頂点で aligned-shield
miss を保つ。したがって factor cycle に沿う単調な defect 減少は存在しない。
ただしこれは full `C_q` box の universal failureを意味しない。

## E_q=1 と exact placement

`C_q=rS`、r だけが NR、S が QR の場合、box は

~~~
Q_q ∪ rQ_q ∪ r^{-1}Q_q
~~~

という三つの coset になる。典型的な miss は stabilizer 不足ではなく、QR subgroup
全体を生成していても prescribed inverse orbit を避ける exact placement である。

この normal form は、character obstruction と subgroup-generation obstruction を
切り離して、残る問題を有限群内の配置問題として表す。

## Class-specific detector 後の conjecture

hard class に応じた exact detector を全て miss した p について、

~~~
∃ external prime q≡3 (mod 4),  q ≲ (log p)^2
~~~

で full signed box が Type I または Type II target を hit する、という conjecture が
現在の有限 signal を最も簡潔に表す。ただし least quadratic nonresidue の解析的限界と
target placement を同時に扱う必要があり、未証明である。

## fab への翻訳

coprime `a,b` に対する `M=4ab`、`L=a+bp`、M-unit part `N`、`c=N (mod M)`、
target `t=-p (mod M)` を使う。prime-or-complement lemma により、fab miss なら N の
各 prime factor は `t` と `ct^{-1}` を避ける。この forbidden residue condition は
小さい `(a,b)` ごとに有限の sieve condition になる。

`(1,6),(6,1)` は mod 24 の 17,23 を、m=5 pair は mod 20 の 11,13,17,19 を
forbid する。これを q=3,7 と組み合わせると、有限-M の sieve dimension が上がる。

## 限界

有限 sieve は例外集合を薄くできるが、thin-but-nonempty 集合を空にする parity barrier
を自動的には越えない。従って small-fab sieve は ES 本証明の代替ではなく、最後に
非 sieve 的議論を適用する residual を明示するための前処理である。

状態: external-NR の限定 rule は棄却、full-box conjecture と fab sieve は live。
