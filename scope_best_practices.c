#include <stdio.h>

int main() {
    printf("=== スコープ管理のベストプラクティス ===\n\n");
    
    // ✅ 良い例1: 意味のある変数名を使う
    printf("1. 意味のある変数名\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            printf("(%d,%d) ", row, col);
        }
        printf("\n");
    }
    printf("\n");
    
    // ✅ 良い例2: スコープを最小限に保つ
    printf("2. 必要な場所でのみ変数を宣言\n");
    for (int i = 0; i < 3; i++) {
        int temp = i * 2;  // このループ内でのみ必要
        printf("i=%d, temp=%d\n", i, temp);
    }
    // tempはここでは使えない（メモリ効率が良い）
    
    // ✅ 良い例3: 複数のループで使う場合は事前宣言
    printf("\n3. 複数ループでの変数共有\n");
    int counter;
    
    printf("カウントアップ: ");
    for (counter = 1; counter <= 5; counter++) {
        printf("%d ", counter);
    }
    printf("\n");
    
    printf("カウントダウン: ");
    for (counter = 5; counter >= 1; counter--) {
        printf("%d ", counter);
    }
    printf("\n");
    
    // ❌ 避けるべき例: グローバル変数の乱用
    // int global_i;  // どこからでもアクセス可能だが、管理が困難
    
    // ✅ 良い例4: ネストループでの適切な変数名
    printf("\n4. ネストループでの変数名\n");
    for (int outer_loop = 1; outer_loop <= 3; outer_loop++) {
        printf("外側 %d: ", outer_loop);
        for (int inner_loop = 1; inner_loop <= outer_loop; inner_loop++) {
            printf("*");
        }
        printf("\n");
    }
    
    return 0;
}