# k=35 の pure-support 定理候補

- status: **rejected**（明示的反例あり）
- source: 2026-09-01 会話の追加検証で提出、2026-09-01 closure 訂正で反証

## 主張（棄却対象）

~~~
p ≡ 121 (mod 840)  ⇒  k=35 が miss ⇔ C_35 の全素因子が p-QR
~~~

および `h=361` での同じ主張。根拠は `(Z/35Z)^× ≃ C_12 × C_2` 上の exact closure で
reachable state 394、class 121 の center に一致する combined miss が 2 状態だけで
いずれも pure Jacobi `+1` support、というものだった。

## 反証

### 実素数の反例

`p = 21121`（`= 840·25 + 121` なので `h = 121`、素数）。
`C_35 = (21121+35)/4 = 5289 = 3·41·43`。

- `41 ≡ 6 (mod 35)` で `jacobi(6,35) = -1`、すなわち 41 は p-NR。よって非 pure。
- 約数の `mod 35` 剰余は `{1,3,4,6,8,13,18,24}`。target は `t₁ = 26`、`t₂ = 31` で
  どちらも含まれない。よって miss。

miss かつ非 pure なので同値は破れる。各 hard class の最小反例:

| `h` | `p` | `C_35` |
|---:|---:|---|
| 1 | 26,041 | 3·41·53 |
| 121 | 21,121 | 3·41·43 |
| 169 | 66,529 | 3²·43² |
| 289 | 12,049 | 3·19·53 |
| 361 | 19,681 | 3·31·53 |
| 529 | 9,769 | 3·19·43 |

### 監査

`p < 10^8`、class 121 の hard prime 29,900 件で exact miss 20,298、pure miss 18,080。
差の 2,218 件が「miss だが p-NR 因子を持つ」。先行報告は hard prime 数 29,900 と
pure miss 18,080 は正しく、exact miss を同じ 18,080 としていた点だけが誤り。

## 原因

closure の状態遷移が `S → S ∪ rS ∪ r²S` になっていた。これは素因子 `r` の指数が
2 であることを前提にしており、指数 1 のとき**実在しない約数 `r²` を混ぜる**。
状態が過大になると本当は target を外している配置が hit と判定されるため、
`-1` character の miss が実際より少なく数えられ、偽の annihilation が出る。
正しい遷移は `S → S ∪ rS` の 1 段（指数は反復適用で伸ばす）。

## 残る教訓

- 有限モデルの reachable state を数えるときは、**モデルが現実の
  over-approximation になっているか**を先に確かめる。over でなく「ずれ」だと、
  存在しない annihilation が生まれる。
- 監査で 2 つの量を突き合わせるときは、両方を独立に計算する。片方をモデルから
  取ると mismatch 0 は自動的に出る。
- `k=15` の同じ主張は生きており、`p<10^8` の 179,468 件で独立に再現された
  ([QR-support 十分性](../live/qr-support-sufficiency.md)、
  [07. atlas](../../topics/07-character-annihilation-atlas.md))。
