#include <stdio.h>

int main() {
    printf("=== ループ文の解答例 ===\n\n");
    
    // 課題1の解答: for文で九九の表
    printf("課題1解答: for文で九九の表\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            printf("%2d ", i * j);  // %2dで右寄せ2桁表示
        }
        printf("\n");
    }
    printf("\n");
    
    // 課題2の解答: while文で数値入力
    printf("課題2解答: while文で数値入力\n");
    int num;
    int sum = 0;
    printf("数値を入力してください（0で終了）: ");
    scanf("%d", &num);
    
    while (num != 0) {
        sum += num;
        printf("現在の合計: %d\n", sum);
        printf("次の数値を入力してください（0で終了）: ");
        scanf("%d", &num);
    }
    printf("最終合計: %d\n\n", sum);
    
    // 課題3の解答: do-while文でメニュー
    printf("課題3解答: do-while文でメニューシステム\n");
    int choice;
    
    do {
        printf("\n--- メニュー ---\n");
        printf("1. 挨拶\n");
        printf("2. 計算\n");
        printf("3. 終了\n");
        printf("選択してください (1-3): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("こんにちは！\n");
                break;
            case 2:
                printf("2 + 3 = %d\n", 2 + 3);
                break;
            case 3:
                printf("プログラムを終了します。\n");
                break;
            default:
                printf("無効な選択です。1-3を選んでください。\n");
        }
    } while (choice != 3);  // 3が選ばれるまで繰り返す
    
    return 0;
}