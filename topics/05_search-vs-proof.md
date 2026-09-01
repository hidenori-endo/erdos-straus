# 05. 探索とセマンティックな証明

## 合意した方法論

総当たり・計算探索は、可能性の範囲を狭めたり、反例候補を発見したりするために使う。一方、最終的な解決には、探索結果を再現するだけでなく、なぜ全branchの少なくとも一つがterminal certificateへ到達するのかを説明する意味論的な証明が必要である。

## 探索で得られた主な整理

- finite fab pairで全primeを覆うという期待は、Dickson予想のもとで不可能になる。
- affine-target descentは、最終的にdivisor enumerationの再符号化になり、単独ではproof engineにならない。
- primitive cycle / index defectを膨らませる案は、Type IとType IIを同時に見ると救済されるため、単独の反例生成原理にならない。
- factor-rich injectionは、局所的なmissが多く、単独の証明routeにならない。
- 固定割合 k/p > theta の領域を有限個のHへ落とす期待は一般に偽であり、有限化が強く出るのはp-k = O(sqrt(p))のtop stripである。

## 追加検証での更新

- q=11 → q=19 の cross-shift は、thin state、hard class の強制因子、QR saturation
  が接続した局所的な補題になった。
- q=23 → q=27/31 の固定 route は `p<10^9` の探索で反証された。
- k=15 と k=35 の一部 class では character annihilation が起きるが、k=39 では
  negative-character miss が残る。個別 shift の列挙ではなく、これが起きる条件の
  群論的分類が必要である。

## 現在の本命

Type IIは上端から除外されるため、主戦場は

~~~
(p + 36)/11 < k <= p - 2*sqrt(22*(p+1)/23) + 2
~~~

のType-I-only corridorである。追加検証後は、これに consecutive shift の座標
`C_{4j+3}=N+j` と adaptive な character-saturation route を接続し、固定 roster では
ない forcing lemma を作れるかが次の課題である。

関連出典: [Turn 012](../会話ログ/012-assistant.md), [Turn 018](../会話ログ/018-assistant.md), [Turn 020](../会話ログ/020-assistant.md), [Turn 021](../会話ログ/021-user.md), [Turn 026](../会話ログ/026-assistant.md), [Turn 028](../会話ログ/028-assistant.md), [Turn 032](../会話ログ/032-assistant.md), [Turn 034](../会話ログ/034-assistant.md)
