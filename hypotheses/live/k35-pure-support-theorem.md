# k=35 の pure-support 定理（class 121, 361）

- status: **live / range-free に成立**（閉包 + `p<10^8` 監査）。2026-09-01 に一度
  rejected とされたが、2026-09-03 の箱の訂正で復活
- source: 2026-09-01 会話の追加検証で提出、2026-09-01 closure 訂正で「反証」、
  2026-09-03 box 訂正で復活

## 主張

~~~
p ≡ 121 (mod 840)  ⇒  k=35 が miss ⇔ C_35 の全素因子が p-QR
p ≡ 361 (mod 840)  ⇒  同上
~~~

ここで miss は正しい箱 `Div(C_35²) mod 35` が `t₁ = 26`、`t₂ = -C_35` のどちらも
含まないこと。他の 4 class（`h = 1, 169, 289, 529`）では偽。

## 根拠

- `r²` 遷移の閉包（[`code/closure.cpp`](../../code/README.md)）: reachable 394 状態
  （NOPRUNE）。class 121 の center に一致する miss は 2 状態、class 361 は 3 状態で、
  いずれも pure。`pureHIT = 0`。これは 09-01 addendum §3 の元の atlas 表
  （12/4/8, 2/2/0, 6/3/3, 3/2/1, 3/3/0, 6/4/2）と一致する。
- 実素数監査 `p<10^8`: class 121 は hard prime 29,900、exact miss 18,080、pure 18,080、
  食い違い 0。class 361 は 29,828 / 18,069 / 18,069 / 0。

## 09-01 の「反例」について

09-01 は `p = 21121`（`C_35 = 3·41·43`、41 は p-NR）を「miss かつ非 pure」とした。
`C_35` の約数の剰余は `S = {1,3,4,6,8,13,18,24}` で確かに `26, 31` を含まないが、
真の箱は `S·S` であり `4·24 = 96 ≡ 26 = t₁`。対応する約数は
`D = 3²·41·43² = 682,281 ≡ 26 (mod 35)` で、Type I の解

~~~
x = 5289,  y = p·(pD + C)/35,  z = (C²/D + pC)/35
~~~

を与える。他 class の「反例」（`p = 26041, 66529, 12049, 19681, 9769`）のうち
`h = 121, 361` 以外のものは正しい箱でも miss で、`h=1`: 26041、`169`: 66529、
`289`: 12049、`529`: 18169 が最小 witness。`h=361` の 19681 は真の箱では hit。

## なぜ 121, 361 だけか（未解決）

seed は 6 class 全てで `3`、`⟨3⟩ = ker χ`（位数 12）、center は class ごとに 1 点。
違いは center `c = C_35 mod 35` と target `t₂ = -c` の位置だけである。

| `h` | `c` | `t₂` | miss state | non-pure |
|---:|---:|---:|---:|---:|
| 1 | 9 | 26 (= `t₁`) | 12 | 8 |
| 121 | 4 | 31 | 2 | 0 |
| 169 | 16 | 19 | 6 | 3 |
| 289 | 11 | 24 | 3 | 1 |
| 361 | 29 | 6 | 3 | 0 |
| 529 | 1 | 34 | 6 | 2 |

`h=1` は `t₂ = t₁` で target が 1 本になる。残る 3 class の non-pure miss state
（合計 6 状態）を書き下して、[k=11 補題](k11-seed15-lemma.md)と同じ形の初等証明に
することが次の一手。

関連: [2026-09-03 箱の訂正](../../updates/2026-09-03-box-correction.md)、
[07. atlas](../../topics/07-character-annihilation-atlas.md)、
[Character annihilation criterion](character-annihilation-criterion.md)
