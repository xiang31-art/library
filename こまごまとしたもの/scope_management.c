#include <stdio.h>

// グローバル変数（どこからでもアクセス可能）
int global_var = 100;

int main() {
    printf("=== 変数のスコープ管理 ===\n\n");
    
    // ローカル変数（main関数内でのみ有効）
    int local_var = 10;
    
    printf("1. 異なるスコープレベル\n");
    printf("グローバル変数: %d\n", global_var);
    printf("ローカル変数: %d\n", local_var);
    
    // ブロックスコープ
    {
        int block_var = 20;  // このブロック内でのみ有効
        printf("ブロック変数: %d\n", block_var);
        printf("ブロック内からローカル変数: %d\n", local_var);  // アクセス可能
    }
    // printf("ブロック変数: %d\n", block_var);  // エラー！スコープ外
    
    printf("\n2. 同じ名前の変数（シャドウイング）\n");
    int x = 1;
    printf("外側のx: %d\n", x);
    
    {
        int x = 2;  // 外側のxを隠す（シャドウイング）
        printf("内側のx: %d\n", x);
    }
    printf("再び外側のx: %d\n", x);  // 元のxが復活
    
    printf("\n3. for文での実践例\n");
    
    // 方法1: 各for文で個別に宣言
    for (int i = 0; i < 3; i++) {
        printf("1つ目: i=%d ", i);
    }
    printf("\n");
    
    for (int i = 10; i < 13; i++) {  // 上のiとは別物
        printf("2つ目: i=%d ", i);
    }
    printf("\n");
    
    // 方法2: 事前に宣言して共有
    int j;
    for (j = 0; j < 3; j++) {
        printf("共有変数1: j=%d ", j);
    }
    printf("(終了後j=%d)\n", j);
    
    for (j = 20; j < 23; j++) {
        printf("共有変数2: j=%d ", j);
    }
    printf("(終了後j=%d)\n", j);
    
    return 0;
}