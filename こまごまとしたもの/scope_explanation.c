#include <stdio.h>

int main() {
    printf("=== 変数のスコープ（有効範囲）の解説 ===\n\n");
    
    // 1. for文内で宣言した変数のスコープ
    printf("1. for文内で宣言した変数のスコープ\n");
    
    for (int i = 0; i < 3; i++) {  // iはこのfor文内でのみ有効
        printf("1つ目のfor文: i = %d\n", i);
    }
    // ここでiは使えない！（スコープ外）
    
    for (int i = 10; i < 13; i++) {  // 新しいi（上のiとは別物）
        printf("2つ目のfor文: i = %d\n", i);
    }
    // ここでもiは使えない！
    
    printf("\n");
    
    // 2. 変数を事前に宣言する方法
    printf("2. 変数を事前に宣言して複数のfor文で使用\n");
    
    int j;  // 事前に宣言
    
    for (j = 0; j < 3; j++) {
        printf("1つ目のfor文: j = %d\n", j);
    }
    printf("for文終了後のj = %d\n", j);  // jは使える！
    
    for (j = 20; j < 23; j++) {
        printf("2つ目のfor文: j = %d\n", j);
    }
    printf("2つ目のfor文終了後のj = %d\n", j);
    
    printf("\n");
    
    // 3. ネストしたfor文での変数スコープ
    printf("3. ネストしたfor文での変数スコープ\n");
    
    for (int outer = 1; outer <= 2; outer++) {
        printf("外側ループ: outer = %d\n", outer);
        
        for (int inner = 1; inner <= 3; inner++) {
            printf("  内側ループ: inner = %d, outer = %d\n", inner, outer);
            // ここではouterもinnerも使える
        }
        // ここではouterは使えるが、innerは使えない
        printf("  内側ループ終了後: outer = %d\n", outer);
    }
    // ここではouterもinnerも使えない
    
    return 0;
}