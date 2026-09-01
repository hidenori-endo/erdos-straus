# Adaptive shift and character saturation

- status: live / main candidate
- source: 2026-09-01 会話の追加検証
- confidence: 数値的裏付けと局所補題はあるが、一般定理は未証明

## 仮説

hard prime が全 admissible shift で Type I / Type II の target を逃れ続けることは、
連続列 `C_{4j+3}=N+j` に沿った prime-support と quadratic character の状態遷移を
考えれば排除できる。具体的には

~~~
thin state
→ support alphabet の制限
→ hard class による次 shift の強制因子
→ QR kernel の saturation
→ signed-box target の捕捉
~~~

という adaptive な流れを、shift の大きさに依存しない補題へ圧縮する。

## 根拠

- q=11 の zero-slack miss から `p ≡ 1 (mod 5)`、従って `5|C_19` を導く
  cross-shift 補題。
- class 121 では `7|C_19` も加わり、mod 19 の QR kernel が飽和する。
- q=23 から q=27/31 への固定 route は p<10^9 の探索で反証された。

## 含意

証明対象は「最初の有限個の shift が全て成功する」という roster ではなく、
失敗 state が次の shift へ何を強制するか、そしてその強制がいつ character kernel を
飽和させるかである。

## 次の検証

- `k=15,35,39` の atlas から、mandatory seed と exact center の一般条件を抽出する。
- `C_k` の prime-support alphabet と hard class の合同条件を同時に記述する。
- 各段階で、数値監査と意味論的な補題を分離する。
