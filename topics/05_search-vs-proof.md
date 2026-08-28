# 05. 探索とセマンティックな証明

## 合意した方法論

総当たり・計算探索は、可能性の範囲を狭めたり、反例候補を発見したりするために使う。一方、最終的な解決には、探索結果を再現するだけでなく、なぜ全branchの少なくとも一つがterminal certificateへ到達するのかを説明する意味論的な証明が必要である。

## 探索で得られた主な整理

- finite fab pairで全primeを覆うという期待は、Dickson予想のもとで不可能になる。
- affine-target descentは、最終的にdivisor enumerationの再符号化になり、単独ではproof engineにならない。
- primitive cycle / index defectを膨らませる案は、Type IとType IIを同時に見ると救済されるため、単独の反例生成原理にならない。
- factor-rich injectionは、局所的なmissが多く、単独の証明routeにならない。
- 固定割合 k/p > theta の領域を有限個のHへ落とす期待は一般に偽であり、有限化が強く出るのはp-k = O(sqrt(p))のtop stripである。

## 現在の本命

Type IIは上端から除外されるため、主戦場は

~~~
(p + 36)/11 < k <= p - 2*sqrt(22*(p+1)/23) + 2
~~~

のType-I-only corridorである。ここでHの離散構造と、外部のUnique Peak候補を接続できるかが次の課題である。

関連出典: [Turn 012](../会話ログ/012-assistant.md), [Turn 018](../会話ログ/018-assistant.md), [Turn 020](../会話ログ/020-assistant.md), [Turn 021](../会話ログ/021-user.md), [Turn 026](../会話ログ/026-assistant.md), [Turn 028](../会話ログ/028-assistant.md), [Turn 032](../会話ログ/032-assistant.md), [Turn 034](../会話ログ/034-assistant.md)

