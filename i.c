#include <stdio.h>
#include<string.h>

// 区切り線を出力
void print_separator(int width, char ch) {
    for(int i = 0; i < width; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

// 中央揃えで出力
void print_centered(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    printf("%*s%s%*s\n", padding, "", text, padding, "");
}

// 表のヘッダー
void print_table_header(const char* col1, const char* col2, const char* col3) {
    print_separator(40, '=');
    printf("| %-10s | %-10s | %-10s |\n", col1, col2, col3);
    print_separator(40, '=');
}

int main() {
    print_centered("タイトル", 40);
    print_table_header("名前", "年齢", "点数");
    printf("| %-10s | %10d | %10d |\n", "Taro", 25, 85);
    printf("| %-10s | %10d | %10d |\n", "Hanako", 23, 92);
    print_separator(40, '=');
    
    return 0;
}
