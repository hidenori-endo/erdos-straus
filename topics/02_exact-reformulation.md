# 02. Exact reformulation とType I / Type II

## 基本的な見方

会話では、解の存在を divisor-square box / signed-box が特定のtargetを踏む条件として表す枠組みを使っている。分母のp倍の個数によって、解をType IとType IIに分類する。

- Type I: pの倍数になる分母が1個。
- Type II: pの倍数になる分母が2個。

この分類自体は、PRで使われたD/G型の二分と実質的に同じ構造であり、新しい分類定理として扱うのは危険である。

## Type IIの正規化

会話で使われた一つの正規化は

~~~
A + B = kQ
p + k = 4ABT
~~~

である。これにより、Type IIの成功条件を、約数・合同・quadratic residueの条件へ移せる。

## Exact条件の意味

Erdős–Strausの反例候補は、すべてのbranchが失敗することではなく、すべての admissible shift k でType I targetとType II targetの両方を逃れることに相当する。したがって、一方のtargetの失敗だけでは反例にならない。

## Shift 座標での exact 判定（2026-09-03、証明済み）

解 `4/p = 1/x+1/y+1/z` には `p` で割れない分母 `x` が必ずあり、`k := 4x - p` は
`k ≡ 3 (mod 4)`、`x = C_k = (p+k)/4`。残り 2 項を解くと

~~~
Type II: ∃ D | C_k²,  D ≡ -C_k  (mod k)
Type I : ∃ D | C_k²,  D ≡ -1/4  (mod k)
~~~

で、逆に `D` から解が復元できる。従って

~~~
ES(p)  ⇔  ∃ k ≡ 3 (mod 4):  Div(C_k²) mod k ∋ -1/4 または -C_k.
~~~

箱は **`C_k²` の約数**であって `C_k` の約数ではない（後者は部分箱で、hit を取りこぼす）。
`code/box_check.py` で総当たり解と突き合わせて確認。導出は
[2026-09-03 箱の訂正](../updates/2026-09-03-box-correction.md) §2。
