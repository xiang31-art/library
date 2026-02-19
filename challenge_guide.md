# チャレンジ機能の実装ガイド

## チャレンジ内容
1. 商品の検索（名前で検索）
2. 商品の削除
3. 価格の変更

---

## 1. 商品の検索（名前で検索）

### 必要なヘッダファイル
```c
#include <stdio.h>
#include <string.h>  // strcmp を使うため
```

### 使う関数
- `strcmp(文字列1, 文字列2)` - 文字列を比較
  - 戻り値が0なら同じ
  - 0以外なら違う

### 実装例
```c
void searchProduct() {
    char searchName[50];
    printf("検索する商品名: ");
    scanf("%s", searchName);
    
    int found = 0;  // 見つかったかどうかのフラグ
    
    for(int i = 0; i < productCount; i++) {
        if(strcmp(products[i].name, searchName) == 0) {
            // 見つかった！
            printf("見つかりました！\n");
            printf("%d. %s - %d円 (在庫: %d個)\n", 
                   i+1, products[i].name, products[i].price, products[i].stock);
            found = 1;
            break;
        }
    }
    
    if(found == 0) {
        printf("商品が見つかりませんでした。\n");
    }
}
```

### ポイント
- `strcmp` で文字列を比較
- 見つかったかどうかのフラグを使う
- ループで全商品を調べる

---

## 2. 商品の削除

### 必要なヘッダファイル
```c
#include <stdio.h>
// 特別なヘッダファイルは不要
```

### 考え方
配列から要素を削除するには、後ろの要素を前に詰める

```
削除前: [A, B, C, D, E]
Bを削除したい（インデックス1）

手順:
1. C を B の位置に移動
2. D を C の位置に移動
3. E を D の位置に移動
4. 要素数を1減らす

削除後: [A, C, D, E]
```

### 実装例
```c
void deleteProduct() {
    int num;
    printf("削除する商品番号: ");
    scanf("%d", &num);
    
    if(num < 1 || num > productCount) {
        printf("無効な商品番号です。\n");
        return;
    }
    
    // 削除する商品の情報を表示
    printf("%s を削除しますか？ (1: はい, 0: いいえ): ", 
           products[num-1].name);
    int confirm;
    scanf("%d", &confirm);
    
    if(confirm != 1) {
        printf("削除をキャンセルしました。\n");
        return;
    }
    
    // 後ろの要素を前に詰める
    for(int i = num - 1; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    
    productCount--;  // 要素数を減らす
    printf("削除しました！\n");
}
```

### ポイント
- 削除する位置から後ろの要素を前に詰める
- `products[i] = products[i + 1]` で構造体全体をコピー
- `productCount` を減らす
- 確認メッセージを出すと安全

---

## 3. 価格の変更

### 必要なヘッダファイル
```c
#include <stdio.h>
// 特別なヘッダファイルは不要
```

### 実装例（ポインタを使う）
```c
void changePrice(struct Product *p, int newPrice) {
    int oldPrice = (*p).price;
    (*p).price = newPrice;
    printf("%s の価格を変更しました。\n", (*p).name);
    printf("%d円 → %d円\n", oldPrice, newPrice);
}

// main関数のswitch文で呼び出す
case 8: {  // 新しいメニュー番号
    int num, newPrice;
    printf("商品番号: ");
    scanf("%d", &num);
    
    if(num < 1 || num > productCount) {
        printf("無効な商品番号です。\n");
        break;
    }
    
    printf("新しい価格: ");
    scanf("%d", &newPrice);
    
    changePrice(&products[num - 1], newPrice);
    break;
}
```

### ポイント
- ポインタを使って元の変数を変更
- `(*p).price` で価格にアクセス
- 変更前の価格を表示すると親切

---

## メニューの追加

main関数のメニューに追加：

```c
printf("1. 商品を登録\n");
printf("2. 全商品を表示\n");
printf("3. 商品を販売 (在庫を減らす)\n");
printf("4. 商品を入荷 (在庫を増やす)\n");
printf("5. 在庫切れ商品を表示\n");
printf("6. 在庫の合計金額を表示\n");
printf("7. 商品を検索\n");        // 追加
printf("8. 商品を削除\n");        // 追加
printf("9. 価格を変更\n");        // 追加
printf("10. 終了\n");             // 変更
```

switch文にも追加：

```c
case 7:
    searchProduct();
    break;

case 8:
    deleteProduct();
    break;

case 9: {
    int num, newPrice;
    printf("商品番号: ");
    scanf("%d", &num);
    printf("新しい価格: ");
    scanf("%d", &newPrice);
    changePrice(&products[num - 1], newPrice);
    break;
}

case 10:  // 終了
    return 0;
```

---

## 関数プロトタイプの追加

ファイルの最初に追加：

```c
void searchProduct();
void deleteProduct();
void changePrice(struct Product *p, int newPrice);
```

---

## まとめ

### 必要なヘッダファイル
```c
#include <stdio.h>
#include <string.h>  // strcmp を使うため（検索機能）
```

### 新しく使う関数
- `strcmp(str1, str2)` - 文字列比較（検索で使用）

### 実装のポイント
1. **検索**: strcmp で文字列を比較
2. **削除**: 配列の要素を前に詰める
3. **価格変更**: ポインタを使って変更

頑張ってください！わからないことがあれば質問してください。
