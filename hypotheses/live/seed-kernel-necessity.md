# ⟨seed⟩ ⊇ ker χ は character annihilation の必要条件

- status: **proved for `k ≤ 403`**（閉包の到達状態として構成、実素数 witness も全組にある）。
  一般 `k` は `gcd(k,210)=1` かつ `[ker χ : ⟨seed⟩] ≥ 3` で証明済み
- source: 2026-09-03 seed 必要条件の検証

## 主張

`k ≡ 3 (mod 4)`、hard class `h`、seed `= gcd(210, (h+k)/4)`、`H = ⟨seed の素因子 mod k⟩`、
`Q = ker χ` とする。

~~~
(k,h) で「miss ⇒ pure」が成立する  ⇒  H ⊇ Q
~~~

## 証明の骨子

`H ⊉ Q` のとき、NR 剰余 `r` を 1 個（E1）または 2 個（E2）足した状態
`S = H·{1,r,r²}(·{1,r',r'²})` は閉包で到達可能で、miss 条件は `r` が `H` の
高々 2〜3 個の剰余類（`-H`, `-(1/4)H`, `-4H`）を避けることに落ちる。
`gcd(k,210)=1` なら fiber は全体なので、`[Q:H] ≥ 3` で直ちに非 pure miss がある。
`gcd(k,210) > 1` では fiber 制約が入り、`k ≤ 403` の 134 組は計算で cover した。
詳細は [2026-09-03 seed 必要条件](../../updates/2026-09-03-seed-necessity-and-even-e.md) §3。

## 十分ではない

`H ⊇ Q` を満たす 389 組のうち成立は 30 組だけ。`k=35` の `h=1,169,289,529` が
最小の反例で、その miss 組は `(r₁,r₂,m)` の有限表として書き下されている
（同 §2）。

## 経緯

2026-09-01 に「`k=35` が反例」として必要性が棄却されたが、それは部分箱の誤りで、
正しい箱では必要条件に戻った（[箱の訂正](../../updates/2026-09-03-box-correction.md) §6）。

関連: [Character annihilation criterion](character-annihilation-criterion.md)、
[k=35 pure-support 定理](k35-pure-support-theorem.md)
