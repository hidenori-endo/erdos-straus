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

