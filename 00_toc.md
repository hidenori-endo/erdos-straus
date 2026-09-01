# 論点別目次

まず論点別の整理を読み、必要な場合だけ末尾のターン別資料へ降りる。

## 論点

- [01. 問題設定と既存研究](topics/01_problem-and-prior-work.md)
- [02. Exact reformulation とType I / Type II](topics/02_exact-reformulation.md)
- [03. Hard-prime obstruction と探索領域](topics/03_hard-prime-obstructions.md)
- [04. Divisor roster とUnique Peak候補](topics/04_divisor-roster.md)
- [05. 探索とセマンティックな証明](topics/05_search-vs-proof.md)
- [06. Consecutive integers とcross-shift](topics/06_cross-shift-and-consecutive-integers.md)
- [07. Character annihilation atlas](topics/07-character-annihilation-atlas.md)

## 追加更新

- [2026-09-01 追加検証ダイジェスト](updates/2026-09-01-addendum.md)

## 数学的仮説

- [仮説一覧](hypotheses/index.md)
- [生きている結果・研究候補](hypotheses/live/index.md)
- [棄却・反証された仮説](hypotheses/rejected/index.md)
- [外部候補：Unique Peak Theorem](補足資料/x-minato-2080305426172948725.md)

## ターン別出典

会話は時系列順に34ターンあります。以下は出典確認用の索引です。

- [Turn 001 — user](会話ログ/001-user.md) — https://github.com/hidenori-endo/science-researcher/pull/129 これは未解決問題の証明なの？
- [Turn 002 — assistant](会話ログ/002-assistant.md) — いいえ。PR #129 は Erdős–Straus 予想そのものの証明ではありません。 むしろ「元の未解決問題を、より具体的な別の存在命題へ帰着した」という内容です。
- [Turn 003 — user](会話ログ/003-user.md) — このやり方は他の論文とかで試されているものではないの？
- [Turn 004 — assistant](会話ログ/004-assistant.md) — はい。調べると、PR #129 の「基本戦略」はかなり既存研究と重なっています。特に「素数へ帰着 → p が分母のどこに入るかで分類 → 2項の Egyptian fraction を因数・約数条件へ変換 → 残った合同類を約数条件で攻める」という流れ自体は、かなり以前から研究されています。
- [Turn 005 — user](会話ログ/005-user.md) — https://github.com/hidenori-endo/science-researcher/pull/133 なんか追加のPR出てるけど、これで解決されてるの？
- [Turn 006 — assistant](会話ログ/006-assistant.md) — いいえ。むしろ逆です。PR #133 は「#129 では解決していなかったし、評価も過大だった」と正式に訂正するPRです。
- [Turn 007 — user](会話ログ/007-user.md) — https://github.com/hidenori-endo/science-researcher/pull/134 また出ましたが、これはつまり、このパーツがあれば解けそうだったものの否定はできたけど、問題そのものの否定にはならなかったということ？あなただったら次にどこを攻めるとかある？
- [Turn 008 — assistant](会話ログ/008-assistant.md) — はい、ほぼその理解で合っています。ただし「このパーツがあれば問題そのものが解けた」というより、
- [Turn 009 — user](会話ログ/009-user.md) — うん、じゃああなたがそれやってみて
- [Turn 010 — assistant](会話ログ/010-assistant.md) — やってみた結果、かなりはっきりしました。当初私が候補にした2方向のうち、どちらもそのまま「新しい攻略ルート」にはなりませんでした。 ただし、次に攻めるべき場所は以前より絞れています。
- [Turn 011 — user](会話ログ/011-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 012 — assistant](会話ログ/012-assistant.md) — かなり進みました。結論からいうと、単純な補題候補をいくつか潰した結果、現在の本当の攻撃点がかなり狭くなりました。
- [Turn 013 — user](会話ログ/013-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 014 — assistant](会話ログ/014-assistant.md) — かなり進みました。今回、「Branch B を矛盾で消す」方向は反証できました。その代わり、Branch B にかなり強い新しい構造制約が見つかり、次の攻撃点が明確になりました。
- [Turn 015 — user](会話ログ/015-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 016 — assistant](会話ログ/016-assistant.md) — かなり重要なところまで進みました。結論として、「primitive index-6 defect は閉路を作れない」という次の攻略仮説は反証されました。
- [Turn 017 — user](会話ログ/017-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 018 — assistant](会話ログ/018-assistant.md) — かなり進みました。結論からいうと、前回の「primitive cycle + k=3 miss」だけでなく、最初の4 shift を全部 miss するところまで構成できました。
- [Turn 019 — user](会話ログ/019-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 020 — assistant](会話ログ/020-assistant.md) — 進みました。今回はかなり明確な成果があります。
- [Turn 021 — user](会話ログ/021-user.md) — うん、じゃあ次それ検証頑張ってやろう！総当たり的な作業は探索の可能性範囲を狭めるのにやっていいけど、証明はセマンティックな論理的解決ができるようにね
- [Turn 022 — assistant](会話ログ/022-assistant.md) — かなり重要なところまで進みました。今回の「総当たりは探索補助、証明はセマンティックに」という方針から、個別の k=39,43,47,… を追うより強い一般命題が出ています。
- [Turn 023 — user](会話ログ/023-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 024 — assistant](会話ログ/024-assistant.md) — 進めました。今回はかなり大きな方向修正があります。「無限に大きな shift で defect を膨らませる」方向は、解決のための invariant としてはほぼ使えないことが分かりました。代わりに、攻めるべき範囲を O(p 2 ) に切り詰められます。
- [Turn 025 — user](会話ログ/025-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 026 — assistant](会話ログ/026-assistant.md) — 進めました。今回の検証では、狙っていた 「private factor / Kneser defect を global resource として足し上げる」案は、そのままでは閉じないことがかなり明確になりました。一方で、より正確な次の攻撃対象まで絞れています。
- [Turn 027 — user](会話ログ/027-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 028 — assistant](会話ログ/028-assistant.md) — 検証を進めた結果、かなり意味のあるところまで絞れました。今回は「証明に使える構造」と「探索で棄却した候補」を明確に分けます。
- [Turn 029 — user](会話ログ/029-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 030 — assistant](会話ログ/030-assistant.md) — 進みました。今回はかなり重要な negative theorem を一段強化できました。そのうえで、次の positive route 候補も1つ反証できています。
- [Turn 031 — user](会話ログ/031-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 032 — assistant](会話ログ/032-assistant.md) — 進めました。今回はかなり収穫があります。affine-target descent は本質的には tautology だったので棄却しましたが、その過程から Type I / Type II の成功可能領域を意味論的にかなり狭められました。
- [Turn 033 — user](会話ログ/033-user.md) — うん、じゃあ次それ検証頑張ってやろう！
- [Turn 034 — assistant](会話ログ/034-assistant.md) — 次は狙いを明確にします。**「Type-I の上側 k/p>θ は、有限個の H=d(b−a) 2 に落ちるか」**をまず一般式で判定します。これが真なら upper corridor 全体を有限個の quadratic forms に還元できますし、偽ならその期待を早めに捨てます。

## 外部参照

- [X投稿：Unique Peak Theorem候補](補足資料/x-minato-2080305426172948725.md) — Type II rosterにおける `−1` の一意最大性を主張する未検証候補。
