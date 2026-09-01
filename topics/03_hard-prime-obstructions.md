# 03. Hard-prime obstruction と探索領域

## Type II側の無条件 bound

会話で得られた無条件の整理は、hard primeのType II solutionについて

~~~
p >= 11k - 36
~~~

したがって

~~~
k <= (p + 36) / 11
~~~

である。これはType IIをk/pのおよそ9.1%以内へ閉じ込め、上側のcorridorではType Iだけを追えばよいことを意味する。

## Type I側の構造

Type Iの正規化では

~~~
4dab = pe + 1
e divides a + b
H = d(b-a)^2
e divides H + 1
e = 3 (mod 4)
~~~

が現れる。hard条件だけから

~~~
H >= 22
~~~

が得られた。

さらに、s = (p-k)/2、u = ceil(s^2/k) と置くと

~~~
H = (s+u)^2 / (u*k - s^2)
~~~

であり、Type Iの上端について

~~~
k <= p - 2*sqrt(22*(p+1)/23) + 2
~~~

というboundが得られる。H=22の例がsharp caseとして記録されている。

関連出典: [Turn 030](../会話ログ/030-assistant.md), [Turn 032](../会話ログ/032-assistant.md), [Turn 034](../会話ログ/034-assistant.md)

