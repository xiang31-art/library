# WSL環境でのコアダンプ実践ガイド

## WSLでのコアダンプの課題と解決方法

WSL環境では、標準的なコアダンプ生成に制限があります。ここでは、実際に動作する方法を紹介します。

---

## 方法1：gdb を使ったコアダンプ生成と解析（推奨）

### ステップ1：プログラムをコンパイル

```bash
cd /mnt/c/Users/xiang/source/kiro
gcc -g -Wall core_dump_examples.c -o crash_test
```

### ステップ2：gdb でプログラムを実行

```bash
gdb ./crash_test
```

### ステップ3：gdb 内でプログラムを実行

```gdb
(gdb) run
# プログラムが起動し、メニューが表示される

# 選択肢を入力（例：1）
1

# プログラムがクラッシュ
# Program received signal SIGSEGV, Segmentation fault.
# 0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20
# 20      *ptr = 100;  // ここでクラッシュ
```

### ステップ4：クラッシュ時の情報を確認

```gdb
# スタックトレース
(gdb) backtrace
#0  0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20
#1  0x0000555555555500 in main () at core_dump_examples.c:150

# ローカル変数
(gdb) info locals
ptr = 0x0
value = 42

# ソースコード
(gdb) list
15      printf("ptr = %p\n", (void*)ptr);
16      printf("value = %d\n", value);
17      printf("NULL ポインタにアクセスします...\n");
18      
19      *ptr = 100;  // ← ここでクラッシュ
20  }

# 終了
(gdb) quit
```

---

## 方法2：gdb バッチモードでの自動解析

### ステップ1：gdb コマンドファイルを作成

```bash
cat > gdb_commands.txt << 'EOF'
run
backtrace
info locals
list
quit
EOF
```

### ステップ2：gdb をバッチモードで実行

```bash
# 例1：NULL ポインタアクセス
echo "1" | gdb -batch -x gdb_commands.txt ./crash_test
```

**出力例：**
```
Reading symbols from ./crash_test...
Starting program: /mnt/c/Users/xiang/source/kiro/crash_test 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

╔════════════════════════════════════════════════════════╗
║         コアダンプ解析用サンプルプログラム            ║
╚════════════════════════════════════════════════════════╝

このプログラムは意図的にクラッシュします
コアダンプを生成して gdb で解析してください

実行する例を選択してください:
1: NULL ポインタアクセス
2: 配列の境界外アクセス
3: ダングリングポインタ
4: スタックトレースの確認
5: 構造体とコアダンプ
6: リンクリストとコアダンプ
0: 終了
選択: === 例1: NULL ポインタアクセス ===
ptr = (nil)
value = 42
NULL ポインタにアクセスします...

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20
20      *ptr = 100;  // ここでクラッシュ

#0  0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20
#1  0x0000555555555500 in main () at core_dump_examples.c:150

ptr = 0x0
value = 42

15      printf("ptr = %p\n", (void*)ptr);
16      printf("value = %d\n", value);
17      printf("NULL ポインタにアクセスします...\n");
18      
19      *ptr = 100;  // ← ここでクラッシュ
20  }
```

---

## 方法3：複数の例を自動解析するスクリプト

### スクリプト作成

```bash
cat > analyze_all_crashes.sh << 'EOF'
#!/bin/bash

# コンパイル
echo "=== コンパイル中 ==="
gcc -g -Wall core_dump_examples.c -o crash_test
echo "完了"
echo ""

# 各例を実行
for i in 1 2 3 4 5 6; do
    echo "╔════════════════════════════════════════════════════════╗"
    echo "║              例 $i の解析                              ║"
    echo "╚════════════════════════════════════════════════════════╝"
    echo ""
    
    # gdb コマンドファイルを作成
    cat > gdb_cmd_$i.txt << GDBEOF
run
backtrace
info locals
quit
GDBEOF
    
    # gdb で実行
    echo "$i" | gdb -batch -x gdb_cmd_$i.txt ./crash_test 2>&1 | tail -30
    
    echo ""
    echo "---"
    echo ""
    
    # クリーンアップ
    rm gdb_cmd_$i.txt
done
EOF

chmod +x analyze_all_crashes.sh
```

### スクリプト実行

```bash
./analyze_all_crashes.sh
```

---

## 方法4：詳細な解析用スクリプト

### スクリプト作成

```bash
cat > detailed_analysis.sh << 'EOF'
#!/bin/bash

EXAMPLE=$1

if [ -z "$EXAMPLE" ]; then
    echo "使用方法: $0 <例番号>"
    echo "例: $0 1"
    exit 1
fi

echo "╔════════════════════════════════════════════════════════╗"
echo "║         例 $EXAMPLE の詳細解析                        ║"
echo "╚════════════════════════════════════════════════════════╝"
echo ""

# gdb コマンドファイルを作成
cat > gdb_detailed.txt << 'GDBEOF'
run
backtrace full
info locals
info args
info registers
quit
GDBEOF

# gdb で実行
echo "$EXAMPLE" | gdb -batch -x gdb_detailed.txt ./crash_test

# クリーンアップ
rm gdb_detailed.txt
EOF

chmod +x detailed_analysis.sh
```

### 使用方法

```bash
# 例1の詳細解析
./detailed_analysis.sh 1

# 例4（スタックトレース）の詳細解析
./detailed_analysis.sh 4
```

---

## 実践例：各クラッシュパターンの解析

### 例1：NULL ポインタアクセス

```bash
echo "1" | gdb -batch -ex "run" -ex "backtrace" -ex "info locals" -ex "quit" ./crash_test
```

**期待される出力：**
```
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20

#0  0x0000555555555209 in example1_null_pointer () at core_dump_examples.c:20
#1  0x0000555555555500 in main () at core_dump_examples.c:150

ptr = 0x0
value = 42
```

### 例4：スタックトレースの確認

```bash
echo "4" | gdb -batch -ex "run" -ex "backtrace full" -ex "quit" ./crash_test
```

**期待される出力：**
```
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555209 in level3 () at core_dump_examples.c:85

#0  0x0000555555555209 in level3 () at core_dump_examples.c:85
        level3_var = 300
        ptr = 0x0
#1  0x0000555555555235 in level2 () at core_dump_examples.c:91
        level2_var = 200
#2  0x0000555555555261 in level1 () at core_dump_examples.c:97
        level1_var = 100
#3  0x0000555555555287 in example4_stack_trace () at core_dump_examples.c:104
        main_var = 10
#4  0x0000555555555500 in main () at core_dump_examples.c:150
```

---

## WSL環境での gdb コマンド一覧

### 基本的な使用方法

```bash
# インタラクティブモード
gdb ./crash_test

# バッチモード（自動実行）
gdb -batch -ex "run" -ex "backtrace" -ex "quit" ./crash_test

# コマンドファイルを使用
gdb -batch -x commands.txt ./crash_test

# 標準入力からコマンドを入力
echo "1" | gdb -batch -ex "run" -ex "backtrace" -ex "quit" ./crash_test
```

### よく使う gdb コマンド

| コマンド | 説明 |
|---------|------|
| `run` | プログラムを実行 |
| `backtrace` (bt) | スタックトレース表示 |
| `backtrace full` | 詳細なスタックトレース |
| `info locals` | ローカル変数表示 |
| `info args` | 関数の引数表示 |
| `info registers` | レジスタ表示 |
| `list` | ソースコード表示 |
| `print 変数` | 変数の値表示 |
| `frame N` | フレームN に移動 |
| `quit` | gdb を終了 |

---

## WSL環境での制限と対策

### 制限事項

1. **コアダンプファイルの自動生成が限定的**
   - WSLのカーネル設定により、通常のコアダンプ生成が制限される
   - 対策：gdb を使用した直接解析

2. **coredumpctl が使えない**
   - systemd のコアダンプ管理ツールが利用できない
   - 対策：gdb バッチモードで代替

3. **sudo が必要な設定変更**
   - kernel.core_pattern の変更にはsudo権限が必要
   - 対策：gdb を使用すれば権限不要

### 推奨アプローチ

**WSL環境では gdb を使った直接解析が最も効果的です：**

```bash
# 1. コンパイル
gcc -g -Wall program.c -o program

# 2. gdb で実行
echo "入力値" | gdb -batch -ex "run" -ex "backtrace" -ex "info locals" -ex "quit" ./program

# 3. 詳細な解析が必要な場合
gdb ./program
(gdb) run
(gdb) backtrace full
(gdb) info locals
(gdb) quit
```

---

## まとめ

### WSL環境でのコアダンプ解析方法

1. **最も簡単**: gdb インタラクティブモード
   ```bash
   gdb ./crash_test
   (gdb) run
   ```

2. **自動化**: gdb バッチモード
   ```bash
   echo "1" | gdb -batch -ex "run" -ex "backtrace" -ex "quit" ./crash_test
   ```

3. **スクリプト化**: 複数の例を自動解析
   ```bash
   ./analyze_all_crashes.sh
   ```

### 得られる情報

- ✓ クラッシュ箇所（ファイル名と行番号）
- ✓ スタックトレース（関数呼び出しの履歴）
- ✓ ローカル変数の値
- ✓ 関数の引数
- ✓ レジスタの内容

これらの情報があれば、ほとんどのクラッシュの原因を特定できます！
