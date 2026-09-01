# 04. Divisor roster とUnique Peak候補

## 未検証の Unique Peak 候補

[Unique Peak candidate](../hypotheses/live/unique-peak-candidate.md) は、q = 4Q - 1 に対して約数ペアの剰余値の重複度

~~~
mu_q(t) = # { (s1,s2) :
              s1 divides Q, s2 divides Q,
              -4*s1*s2 = t (mod q) }
~~~

を定義し、

~~~
mu_q(t) <= tau(Q)
~~~

かつ等号は t = -1 (mod q) のときだけ、という一意最大性を提案している。

## なぜ関係するか

会話内でもType II targetの-1が特別扱いされ、divisor-boxの重複やJacobi条件が障害の中心になっている。この候補が正しければ、個別のmodulus探索を「一意ピーク」という一般補題に圧縮できる可能性がある。

## 注意点

これは既存のType II変数と記号が同じとは限らない。さらに、s1,s2がQの約数でもs1*s2がQの約数とは限らないため、積の衝突をq moduloで扱う必要がある。q < 4000の計算確認は、一般証明ではない。

状態: external / unverified candidate
