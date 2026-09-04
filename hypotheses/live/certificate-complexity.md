# 証拠複雑度 `cert(p)` は小さい

- status: live / conjecture（`D=1` 層のみ証明済み）
- source: 2026-09-04 の測定（[certificate complexity](../../updates/2026-09-04-certificate-complexity.md)）
- confidence: `p < 10^9` の hard prime 全数で `cert ≤ 395`。証明なし。

## 定義

`e | C_k²` が `t₁ = -1/4` または `t₂ = -C_k` を `mod k` で踏むとき、
`e | d²` かつ `d | C_k` を満たす最小の約数は `d(e) = ∏ q^⌈a_q/2⌉`。

~~~
cert(p) = min over k ≡ 3 (mod 4), over hitting e | C_k²,  max(k, d(e))
~~~

`(k, d, e)` を固定すると条件は `p ≡ -k (mod 4d)` と `p mod k` の合同式になり、解は
`p` の多項式。よって `cert(p) ≤ B` は「パラメータ `≤ B` の古典的恒等式族で覆われる」
ことと同値である。

## 測定

`p < 10^9` の hard prime 1,587,581 個（`code/cert_complexity.cpp`）:

- 幾何平均 `cert = 17.2`、`cert ≤ 32` が 91.7%、`cert ≤ 128` が 99.94%。
- decade 別最大 34 / 155 / 111 / 173 / 251 / **395**。`(log 10^9)^2 ≈ 430`。
- 最適点では常に `cert = k`、`d(e)` は小さい（最大級の 4 例で 11, 19, 4, 35）。

約数予算 `D` を固定したときの必要 shift（`code/tradeoff.cpp`、`p<10^8`）:
`D = 64` で全 hard prime が `k ≤ 1191`、`D = 256` で `k ≤ 251`。

## 有界にならない理由

`cert` が有界なら有限の covering system で ES が証明できる。Mordell の 840 の議論は
その最小の場合で、hard class（平方剰余類）が残ることが既知。よって `cert` は非有界で、
問題はその増大率。測定は `(log p)^2` 以下を支持する。

## 証明済みの層: `D = 1`

`p + 4 = k·j`（`k ≡ j ≡ 3 mod 4`）、`m=(j+1)/4`、`C=(p+k)/4` のとき

~~~
4/p = 1/C + 1/(pm) + 1/(pCm)
~~~

が恒等的に成り立つ（[補題 2](../../updates/2026-09-04-certificate-complexity.md#4-d--1-の恒等式とその失敗集合証明済み)）。
`p ≡ 1 (mod 4)` なので、`p+4` が `3 (mod 4)` の素因子を持てば適用できる。失敗するのは
`p+4` の全素因子が `1 (mod 4)` の場合のみで、これは密度 `≍ 1/√(log p)` の
Landau–Ramanujan 型集合。したがってこの 1 層だけで hard prime の密度 1 が処理できる。

`p<2·10^7` の hard prime で成功 44.5% / 失敗 55.5%。hard class は
`h+4 ∈ {5,125,173,293,365,533}` の素因子が全て `1 (mod 4)` なので、一般の
`n ≡ 1 (mod 4)` での失敗密度 ~30% より高くなる。

## 次

`D = 2, 4, 8` の各層の失敗集合を `D=1` と同様に同定できるか。層ごとの失敗集合が
独立に近ければ、共通部分の密度は層数 `t` に対して `(log p)^{-t/2}` 程度まで落ちる。
