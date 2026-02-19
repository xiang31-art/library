# WSL環境でのコアダンプ解析 - 実行結果

## 実行環境

- **OS**: Windows + WSL (Windows Subsystem for Linux)
- **コンパイラ**: gcc
- **デバッガ**: gdb
- **テストプログラム**: core_dump_examples.c

---

## 実行結果

### 例1：NULL ポインタアクセス

#### 実行コマンド
```bash
bash analyze_crashes.sh 1
```

#### 解析結果

```
Program received signal SIGSEGV, Segmentation fault.
0x000055555555527a in example1_null_pointer () at core_dump_examples.c:18
18          *ptr = 100;  // ここでクラッシュ

#0  0x000055555555527a in example1_null_pointer () at core_dump_examples.c:18
#1  0x0000555555555a33 in main () at core_dump_examples.c:226

ptr = 0x0
value = 42
```

#### 解釈

- **クラッシュ箇所**: `example1_null_pointer()` 関数の18行目
- **原因**: `ptr` が NULL（0x0）のため、`*ptr = 100` でアクセス違反
- **変数の状態**:
  - `ptr = 0x0` (NULL)
  - `value = 42`

#### 修正方法

```c
// 修正前
int *ptr = NULL;
*ptr = 100;  // クラッシュ

// 修正後
int *ptr = NULL;
if (ptr != NULL) {
    *ptr = 100;
} else {
    printf("ERROR: ポインタが NULL です\n");
}
```

---

### 例4：スタックトレースの確認

#### 実行コマンド
```bash
bash analyze_crashes.sh detailed 4
```

#### 解析結果

```
Program received signal SIGSEGV, Segmentation fault.
0x00005555555554ec in level3 () at core_dump_examples.c:84
84          *ptr = 10;  // ここでクラッシュ

#0  0x00005555555554ec in level3 () at core_dump_examples.c:84
        level3_var = 300
        ptr = 0x0

#1  0x000055555555552b in level2 () at core_dump_examples.c:90
        level2_var = 200

#2  0x0000555555555564 in level1 () at core_dump_examples.c:96
        level1_var = 100

#3  0x00005555555555ac in example4_stack_trace () at core_dump_examples.c:104
        main_var = 10

#4  0x0000555555555a57 in main () at core_dump_examples.c:235
        choice = 4
```

#### 解釈

**関数呼び出しの履歴（スタックトレース）：**

```
main()
  ↓ choice = 4
example4_stack_trace()
  ↓ main_var = 10
level1()
  ↓ level1_var = 100
level2()
  ↓ level2_var = 200
level3()  ← ここでクラッシュ
  ↓ level3_var = 300, ptr = 0x0
```

**各フレームの変数：**

| フレーム | 関数 | 行番号 | ローカル変数 |
|---------|------|--------|------------|
| #0 | level3 | 84 | level3_var = 300, ptr = 0x0 |
| #1 | level2 | 90 | level2_var = 200 |
| #2 | level1 | 96 | level1_var = 100 |
| #3 | example4_stack_trace | 104 | main_var = 10 |
| #4 | main | 235 | choice = 4 |

#### 重要な情報

- **クラッシュ箇所**: level3 の84行目
- **原因**: NULL ポインタへのアクセス
- **呼び出し経路**: main → example4_stack_trace → level1 → level2 → level3

---

## WSL環境での gdb 解析の利点

### 1. 詳細なスタックトレース

```gdb
(gdb) backtrace full
```

で、各フレームのすべてのローカル変数を表示できます。

### 2. ソースコード表示

```gdb
(gdb) list
```

で、クラッシュ箇所の前後のコードを確認できます。

### 3. 変数の値確認

```gdb
(gdb) info locals
```

で、クラッシュ時のすべてのローカル変数の値を確認できます。

### 4. 自動化が容易

バッチモードで複数の例を自動解析できます：

```bash
bash analyze_crashes.sh 1
bash analyze_crashes.sh 4
bash analyze_crashes.sh detailed 1
```

---

## 実践的な使用例

### シナリオ1：本番環境でのクラッシュ調査

```bash
# 1. WSL環境でプログラムをコンパイル
gcc -g -Wall program.c -o program

# 2. gdb で実行
gdb ./program

# 3. クラッシュ時の情報を確認
(gdb) run
(gdb) backtrace
(gdb) info locals
```

### シナリオ2：複数のバグを一度に調査

```bash
# すべての例を自動解析
bash analyze_crashes.sh

# または特定の例を詳細解析
bash analyze_crashes.sh detailed 1
bash analyze_crashes.sh detailed 2
bash analyze_crashes.sh detailed 3
```

### シナリオ3：スタックトレースの詳細分析

```bash
# 詳細なスタックトレースを表示
bash analyze_crashes.sh detailed 4

# 出力から以下の情報を抽出：
# - クラッシュ箇所
# - 関数呼び出しの履歴
# - 各フレームのローカル変数
# - 変数の値
```

---

## gdb コマンドリファレンス

### 基本コマンド

```gdb
(gdb) run                    # プログラムを実行
(gdb) backtrace              # スタックトレース表示
(gdb) backtrace full         # 詳細なスタックトレース
(gdb) info locals            # ローカル変数表示
(gdb) info args              # 関数の引数表示
(gdb) list                   # ソースコード表示
(gdb) print 変数             # 変数の値表示
(gdb) frame N                # フレームN に移動
(gdb) quit                   # gdb を終了
```

### バッチモード

```bash
# 単一コマンド
gdb -batch -ex "run" -ex "backtrace" -ex "quit" ./program

# コマンドファイル
gdb -batch -x commands.txt ./program

# 標準入力から入力
echo "1" | gdb -batch -ex "run" -ex "backtrace" -ex "quit" ./program
```

---

## トラブルシューティング

### Q: "No debugging symbols found"

**原因**: `-g` オプションなしでコンパイル

**対処**:
```bash
gcc -g -Wall program.c -o program
```

### Q: gdb が起動しない

**原因**: gdb がインストールされていない

**対処**:
```bash
sudo apt-get install gdb
```

### Q: コマンドが実行されない

**原因**: スクリプトに実行権限がない

**対処**:
```bash
chmod +x analyze_crashes.sh
```

---

## まとめ

### WSL環境でのコアダンプ解析の流れ

1. **コンパイル**: `gcc -g program.c -o program`
2. **実行**: `gdb ./program`
3. **解析**: `backtrace`, `info locals`, `list`
4. **修正**: 原因を特定してコードを修正

### 得られる情報

- ✓ クラッシュ箇所（ファイル名と行番号）
- ✓ スタックトレース（関数呼び出しの履歴）
- ✓ ローカル変数の値
- ✓ 関数の引数
- ✓ ソースコード

### 推奨される使用方法

```bash
# 1. プログラムをコンパイル
gcc -g -Wall core_dump_examples.c -o crash_test

# 2. 例1を解析
bash analyze_crashes.sh 1

# 3. 例4を詳細解析
bash analyze_crashes.sh detailed 4

# 4. すべての例を解析
bash analyze_crashes.sh
```

これで、WSL環境でも効果的にコアダンプを解析できます！
