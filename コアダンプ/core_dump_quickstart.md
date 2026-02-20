# コアダンプ クイックスタートガイド

## 5分でわかるコアダンプ解析

### ステップ1：準備（1分）

```bash
# コアダンプを有効化
ulimit -c unlimited

# 確認
ulimit -c
# "unlimited" と表示されればOK
```

### ステップ2：プログラムのコンパイル（1分）

```bash
# デバッグ情報付きでコンパイル
gcc -g -Wall core_dump_examples.c -o crash_test

# または、より詳細な情報を含める
gcc -g3 -O0 -Wall core_dump_examples.c -o crash_test
```

### ステップ3：プログラムを実行してクラッシュさせる（1分）

```bash
./crash_test

# 例を選択（例：1を選択）
# 選択: 1

# 出力例
# === 例1: NULL ポインタアクセス ===
# ptr = (nil)
# value = 42
# NULL ポインタにアクセスします...
# Segmentation fault (core dumped)

# コアダンプファイルを確認
ls -lh core*
# -rw------- 1 user user 352K Jan 1 12:00 core
```

### ステップ4：gdb で解析（2分）

```bash
# gdb でコアダンプを開く
gdb ./crash_test core
```

#### 基本的な解析コマンド

```gdb
# 1. クラッシュ箇所を確認
(gdb) backtrace
# または短縮形
(gdb) bt

# 出力例
#0  0x00005555555551a9 in example1_null_pointer () at core_dump_examples.c:20
#1  0x0000555555555500 in main () at core_dump_examples.c:150

# 2. ソースコードを表示
(gdb) list

# 出力例
15      printf("ptr = %p\n", (void*)ptr);
16      printf("value = %d\n", value);
17      printf("NULL ポインタにアクセスします...\n");
18      
19      *ptr = 100;  // ← ここでクラッシュ
20  }

# 3. 変数の値を確認
(gdb) info locals

# 出力例
ptr = 0x0
value = 42

# 4. 特定の変数を表示
(gdb) print ptr
# $1 = (int *) 0x0

(gdb) print value
# $2 = 42

# 5. 終了
(gdb) quit
```

---

## よく使う gdb コマンド一覧

### 基本コマンド

| コマンド | 短縮形 | 説明 |
|---------|-------|------|
| `backtrace` | `bt` | スタックトレース表示 |
| `frame N` | `f N` | フレームN に移動 |
| `list` | `l` | ソースコード表示 |
| `print 変数` | `p 変数` | 変数の値を表示 |
| `info locals` | - | ローカル変数を表示 |
| `info args` | - | 関数の引数を表示 |
| `quit` | `q` | gdb を終了 |

### 高度なコマンド

```gdb
# すべてのフレームの変数を表示
(gdb) bt full

# メモリの内容を表示
(gdb) x/4xw アドレス

# レジスタを表示
(gdb) info registers

# 構造体の内容を表示
(gdb) print *構造体ポインタ

# 配列の内容を表示
(gdb) print 配列名[0]@配列サイズ
```

---

## 実践例：スタックトレースの読み方

### プログラム実行

```bash
./crash_test
# 選択: 4（スタックトレースの確認）
```

### gdb での解析

```gdb
(gdb) bt

# 出力
#0  0x00005555555552a9 in level3 () at core_dump_examples.c:85
#1  0x00005555555552d5 in level2 () at core_dump_examples.c:91
#2  0x0000555555555301 in level1 () at core_dump_examples.c:97
#3  0x000055555555532d in example4_stack_trace () at core_dump_examples.c:104
#4  0x0000555555555500 in main () at core_dump_examples.c:155
```

### 解釈

```
main()
  ↓ 呼び出し
example4_stack_trace()
  ↓ 呼び出し
level1()
  ↓ 呼び出し
level2()
  ↓ 呼び出し
level3()  ← ここでクラッシュ
```

### 各フレームの変数を確認

```gdb
# フレーム0（level3）
(gdb) frame 0
(gdb) info locals
# level3_var = 300
# ptr = 0x0

# フレーム1（level2）
(gdb) frame 1
(gdb) info locals
# level2_var = 200

# フレーム2（level1）
(gdb) frame 2
(gdb) info locals
# level1_var = 100

# フレーム3（example4_stack_trace）
(gdb) frame 3
(gdb) info locals
# main_var = 10
```

---

## トラブルシューティング

### Q1: コアダンプが生成されない

**確認事項：**

```bash
# 1. ulimit の設定を確認
ulimit -c
# 0 の場合は無効

# 2. 有効化
ulimit -c unlimited

# 3. 再度プログラムを実行
./crash_test
```

### Q2: "No debugging symbols found"

**原因：** `-g` オプションなしでコンパイルされている

**対処：**

```bash
# -g オプションを付けて再コンパイル
gcc -g core_dump_examples.c -o crash_test
```

### Q3: コアファイルが見つからない

**確認：**

```bash
# カレントディレクトリを確認
ls -la core*

# systemd がコアダンプを管理している場合
coredumpctl list

# 最新のコアダンプを取得
coredumpctl dump > core
```

### Q4: gdb で "core file may not match"

**原因：** プログラムを再コンパイルした後、古いコアファイルを使用している

**対処：**

```bash
# 古いコアファイルを削除
rm core*

# プログラムを再実行してコアダンプを生成
./crash_test
```

---

## 実践的な使用シナリオ

### シナリオ1：本番環境でのクラッシュ調査

```bash
# 1. 本番サーバーでコアダンプを有効化
ulimit -c unlimited

# 2. プログラムがクラッシュしてコアダンプ生成
# /var/crash/core.program.12345

# 3. コアダンプを開発環境にコピー
scp server:/var/crash/core.program.12345 ./

# 4. 同じバージョンの実行ファイルで解析
gdb ./program core.program.12345

# 5. 原因を特定
(gdb) bt
(gdb) info locals
```

### シナリオ2：再現が難しいバグの調査

```bash
# 1. プログラムを長時間実行
./program &

# 2. クラッシュしたらコアダンプを確認
ls -lt core* | head -1

# 3. 解析
gdb ./program core

# 4. 状態を詳しく調査
(gdb) bt full
(gdb) info registers
(gdb) x/100xw $rsp  # スタックの内容を確認
```

### シナリオ3：マルチスレッドプログラムのデバッグ

```gdb
# すべてのスレッドを表示
(gdb) info threads

# 特定のスレッドに切り替え
(gdb) thread 2

# そのスレッドのスタックトレース
(gdb) bt

# すべてのスレッドのスタックトレース
(gdb) thread apply all bt
```

---

## 自動化スクリプト

### コアダンプ自動解析スクリプト

```bash
#!/bin/bash
# quick_analyze.sh

PROGRAM=$1
CORE=$2

if [ ! -f "$PROGRAM" ] || [ ! -f "$CORE" ]; then
    echo "使用方法: $0 <program> <core>"
    exit 1
fi

echo "╔════════════════════════════════════════════════════════╗"
echo "║           コアダンプ自動解析                          ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""
echo "プログラム: $PROGRAM"
echo "コアファイル: $CORE"
echo ""

echo "=== スタックトレース ==="
gdb -batch -ex "bt" -ex "quit" "$PROGRAM" "$CORE"

echo ""
echo "=== ローカル変数 ==="
gdb -batch -ex "bt" -ex "info locals" -ex "quit" "$PROGRAM" "$CORE"

echo ""
echo "=== 詳細なスタックトレース ==="
gdb -batch -ex "bt full" -ex "quit" "$PROGRAM" "$CORE"
```

### 使用方法

```bash
# スクリプトに実行権限を付与
chmod +x quick_analyze.sh

# 実行
./quick_analyze.sh crash_test core

# 出力をファイルに保存
./quick_analyze.sh crash_test core > analysis.txt
```

---

## まとめ

### コアダンプ解析の基本フロー

1. **有効化**: `ulimit -c unlimited`
2. **コンパイル**: `gcc -g program.c -o program`
3. **実行**: プログラムがクラッシュ
4. **解析**: `gdb program core`
5. **調査**: `bt`, `info locals`, `print`

### 最も重要な3つのコマンド

```gdb
(gdb) bt              # どこでクラッシュしたか
(gdb) info locals     # 変数の値は何か
(gdb) list            # そのコードは何か
```

### 覚えておくべきポイント

- 必ず `-g` オプションでコンパイル
- `ulimit -c unlimited` を忘れずに
- `bt` でクラッシュ箇所を特定
- `info locals` で変数の状態を確認
- 各フレームを `frame N` で移動して調査

これだけで、ほとんどのクラッシュの原因を特定できます！
