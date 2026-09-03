# Small-fab sieve dimension

- status: live / proof program
- source: 2026-09-03 会話の追加検証
- confidence: forbidden residue の局所計算は確認。Selberg sieve の正式な全証明は未完。

## 構想

各 coprime pair `(a,b)` の prime-or-complement lemma から、fab miss が避ける prime
residue classes を取り出す。q=3,7 と m=5,6 の小さい pair を束ねると、例外集合へ
適用する sieve dimension が増える。

報告された候補は

~~~
κ(M)=1+2 Σ_{m≤M} 1/φ(4m)。
~~~

これは `Σ 1/φ(m) ≍ C log M` により増大する。

## 現在の具体例

- q=3,7 の既存 filter: κ=2。
- m=6 の `(1,6),(6,1)` pair を追加: κ=2.5 の候補。
- m=5 pair も追加: κ=3 の候補。

## 限界

固定 M ごとの Selberg upper-bound sieve を形式化しても、得られるのは任意の固定
logarithmic saving であり、例外集合が空になることではない。sieve parity barrier を
越える最後の非 sieve 的 argument が必要。
