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
p + Q = 4ABT      # 元ノートの `p + k = 4ABT` は誤り（本セッションで訂正）
~~~

である。反例: p=5, (A,B,k,Q,T)=(1,2,1,3,1) は A+B=3=kQ を満たすが p+k=6 は 4ABT=8T の
どの値にもならない。正しくは p+Q=8=4*1*2*1。厳密形は
[Type II exact](../hypotheses/live/typeII-exact.md) を見よ。これにより、Type IIの成功条件を、約数・合同・quadratic residueの条件へ移せる。

## Exact条件の意味

Erdős–Strausの反例候補は、すべてのbranchが失敗することではなく、すべての admissible shift k でType I targetとType II targetの両方を逃れることに相当する。したがって、一方のtargetの失敗だけでは反例にならない。

関連出典: [Turn 010](../会話ログ/010-assistant.md), [Turn 014](../会話ログ/014-assistant.md), [Turn 016](../会話ログ/016-assistant.md), [Turn 022](../会話ログ/022-assistant.md), [Turn 024](../会話ログ/024-assistant.md)

