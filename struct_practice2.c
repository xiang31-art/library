#include <stdio.h>
#include <string.h>

/*
========================================
構造体 練習問題 レベル2
========================================
配列やループと組み合わせて使ってみよう！
*/

// 商品の情報を管理する構造体
struct Product {
    char name[50];  // 商品名
    int price;      // 価格
    int stock;      // 在庫数
};

int main() {
    printf("=== 構造体 練習問題 レベル2 ===\n\n");
    
    // ========================================
    // 練習1: 構造体の配列を作る
    // ========================================
    printf("--- 練習1: 構造体の配列 ---\n");
    
    // 例: 3つの商品を管理する配列
    struct Product products[3] = {
        {"りんご", 150, 20},
        {"バナナ", 100, 30},
        {"みかん", 120, 25}
    };
    

    // 配列の要素を表示
    printf("商品一覧:\n");
    for(int i = 0; i < 3; i++) {
        printf("%d. %s - %d円 (在庫: %d個)\n", 
               i+1, products[i].name, products[i].price, products[i].stock);
    }
    printf("\n");
    
    // ========================================
    // 練習2: 配列の中から探す
    // ========================================
    printf("--- 練習2: 配列の中から探す ---\n");
    
    // バナナの在庫数を表示してください
    // ヒント: products[1]がバナナです
    // ここにコードを書いてください
    for(int i = 0; i < 3; i++){
        if(strcmp(products[i].name, "バナナ") == 0){
            printf("%sの在庫は%d個です\n", products[i].name, products[i].stock);
        }
    }
    
    
    
    // ========================================
    // 練習3: 在庫を更新する
    // ========================================
    printf("--- 練習3: 在庫を更新する ---\n");
    
    // りんごが5個売れました
    // りんごの在庫を5減らしてください
    // ヒント: products[0]がりんごです
    // ここにコードを書いてください
    products[0].stock -= 5;
    
    
    printf("更新後のりんごの在庫: %d個\n\n", products[0].stock);
    
    // ========================================
    // 練習4: 合計金額を計算する
    // ========================================
    printf("--- 練習4: 合計金額を計算する ---\n");
    
    // すべての商品の在庫の合計金額を計算
    // (価格 × 在庫数) をすべて足す
    // ヒント: forループで回して、total += products[i].price * products[i].stock;
    // ここにコードを書いてください
    int total = 0;
    for(int i = 0; i < 3; i++){
        total += products[i].price * products[i].stock;
    }
    
    
    
    
    printf("在庫の合計金額: %d円\n\n", total);
    
    // ========================================
    // 練習5: 一番高い商品を探す
    // ========================================
    printf("--- 練習5: 一番高い商品を探す ---\n");
    
    // 一番価格が高い商品の名前を表示
    // ヒント: maxPriceとmaxIndexを使って探す
    // ここにコードを書いてください
    int maxPrice = products[0].price;
    int maxIndex = 0;
    for(int i = 1; i < 3; i++){
        if(maxPrice < products[i].price){
            maxPrice = products[i].price;
            maxIndex = i;
        }
    }
    
    
    
    
    
    
    printf("一番高い商品: %s (%d円)\n\n", products[maxIndex].name, maxPrice);
    
    // ========================================
    // 練習6: 新しい商品を追加する
    // ========================================
    printf("--- 練習6: 新しい商品を追加する ---\n");
    
    // 4つの商品を管理できる配列
    struct Product shop[4] = {
        {"ノート", 200, 50},
        {"ペン", 100, 80},
        {"消しゴム", 80, 100}
    };
    
    // 4番目に「定規」を追加してください
    // 価格: 150円、在庫: 40個
    // ヒント: shop[3]に値を設定
    // ここにコードを書いてください
    strcpy(shop[3].name,"定規");
    shop[3].price = 150;
    shop[3].stock = 40;
    
    
    
    // すべて表示
    printf("商品一覧:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d. %s - %d円 (在庫: %d個)\n", 
               i+1, shop[i].name, shop[i].price, shop[i].stock);
    }
    printf("\n");
    
    // ========================================
    // 練習7: 在庫切れをチェック
    // ========================================
    printf("--- 練習7: 在庫切れをチェック ---\n");
    
    struct Product items[3] = {
        {"お茶", 120, 10},
        {"コーヒー", 150, 0},
        {"ジュース", 130, 5}
    };
    
    // 在庫が0の商品を表示してください
    // ヒント: forループでitems[i].stock == 0 をチェック
    // ここにコードを書いてください
    printf("在庫切れの商品:\n");
    for(int i = 0; i < 3; i++){
        if(items[i].stock == 0){
            printf("%s\n",items[i].name);
        }
    }
    
    
    
    
    
    printf("\n完成です！お疲れ様でした！\n");
    
    return 0;
}

/*
========================================
ヒント:
========================================

練習2:
printf("バナナの在庫: %d個\n\n", products[1].stock);

練習3:
products[0].stock -= 5;
// または: products[0].stock = products[0].stock - 5;

練習4:
for(int i = 0; i < 3; i++) {
    total += products[i].price * products[i].stock;
}

練習5:
for(int i = 1; i < 3; i++) {
    if(products[i].price > maxPrice) {
        maxPrice = products[i].price;
        maxIndex = i;
    }
}

練習6:
strcpy(shop[3].name, "定規");
shop[3].price = 150;
shop[3].stock = 40;

練習7:
for(int i = 0; i < 3; i++) {
    if(items[i].stock == 0) {
        printf("- %s\n", items[i].name);
    }
}

========================================
覚えること:
========================================
1. 構造体の配列: struct 名前 配列名[サイズ];
2. 配列の要素にアクセス: 配列名[番号].メンバ名
3. forループで全要素を処理できる
4. 条件分岐(if)と組み合わせて検索できる
*/
