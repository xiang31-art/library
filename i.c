#include <stdio.h>

int main() {
    // 表の作成
    printf("┌──────────┬─────┬──────────┐\n");
    printf("│ 商品名   │ 数量│   価格   │\n");
    printf("├──────────┼─────┼──────────┤\n");
    printf("│ %-8s │ %3d │ %8.2f │\n", "りんご", 10, 1500.50);
    printf("│ %-8s │ %3d │ %8.2f │\n", "みかん", 5, 2999.99);
    printf("│ %-8s │ %3d │ %8.2f │\n", "バナナ", 20, 500.00);
    printf("└──────────┴─────┴──────────┘\n");
    
    // 進捗バー
    int progress = 75;
    printf("進捗: [");
    for(int i = 0; i < 50; i++) {
        if(i < progress / 2) printf("=");
        else printf(" ");
    }
    printf("] %3d%%\n", progress);
    
    // デバッグ情報
    int *ptr = &progress;
    printf("変数のアドレス: %p\n", (void*)ptr);
    printf("変数の値: %d (0x%X)\n", *ptr, *ptr);
    
    return 0;
}
