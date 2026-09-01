# Mandatory seed + exact center による character annihilation

- status: live / classification problem
- source: 2026-09-01 会話の追加検証
- confidence: k=15 と k=35 の一部は強い監査付き。一般 criterion は未確立。

## 問い

composite shift `k` と hard class `h` を固定したとき、class-conditioned mandatory seed
を先に消費し、`p=h+840t (mod k)` が許す exact center fiber 上で signed-box の
reachable state を閉じる。このとき、character `-1` の miss state が全て消える条件を
特徴づける。

## 現在の atlas

- `k=15`: 全 hard classで pure p-QR support 以外の miss が消える。
- `k=35`: `h=121,361` で同じ消去。残り4 classでは non-pure miss が残る。
- `k=39`: seed 2 または 10 だけでは `-1` miss が残る。

## 暫定的な必要条件

mandatory seed は単に一つの因子を与えるだけでは不十分であり、少なくとも

1. exact center fiber と整合すること。
2. 残りの QR support が character kernel の必要な部分を生成すること。
3. non-pure miss を残す complement が center 条件と両立しないこと。

が必要である。十分性を一般の `k` に対して証明するのが次の課題。
