# Class-specific detector 後の external shift `q ≲ (log p)^2`

- status: live / conjecture
- source: 2026-09-03 会話の追加検証
- confidence: 有限全数監査と large-p 標本では支持。証明なし。

## 仮説

hard class-specific exact detector を全て miss した hard prime p には、external prime
shift `q≡3 (mod 4)` が存在し、

~~~
q ≲ (log p)^2
~~~

の範囲で full signed box が Type I または Type II target を hit する。

## 根拠

- `p<10^8` の hard prime 179,468 個で detector 全 miss は 7,452 個。その全てが
  external shift で hitし、最大 q は 251。
- 上記 7,452 個では全件 `q*(p)<(log p)^2`。最大比は p=10,028,209、q*=251 で約0.966。
- `10^8<p<10^12` の標本 30,000、`10^12<p<10^15` の標本 5,000 でも detector
  survivor は全て external shift で hitした。

## 理論上の壁

least quadratic nonresidue の存在だけなら解析的数論の問題だが、ここではさらにその
q の full divisor box が prescribed target を踏む必要がある。したがって Burgess 型の
無条件評価だけでこの conjecture を直ちに証明できるとは限らず、GRH 風の scale と
exact placement を同時に扱う必要がある。
