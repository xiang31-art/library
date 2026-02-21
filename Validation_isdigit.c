#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    VALIDATE_INTEGER,      // 整数のみ
    VALIDATE_POSITIVE,     // 正の整数のみ
    VALIDATE_DECIMAL,      // 小数も許可
    VALIDATE_POSITIVE_DECIMAL  // 正の小数
} ValidationType;

int validate_input(const char* str, ValidationType type) {
    int len = strlen(str);
    if(len == 0) return 0;
    
    int start = 0;
    int has_dot = 0;
    int has_digit = 0;
    
    // 符号のチェック
    if(str[0] == '-') {
        if(type == VALIDATE_POSITIVE || type == VALIDATE_POSITIVE_DECIMAL) {
            return 0;  // 負の数は許可しない
        }
        start = 1;
    } else if(str[0] == '+') {
        start = 1;
    }
    
    if(start >= len) return 0;
    
    // 各文字をチェック
    for(int i = start; i < len; i++) {
        if(isdigit(str[i])) {
            has_digit = 1;
        } else if(str[i] == '.') {
            if(type == VALIDATE_INTEGER || type == VALIDATE_POSITIVE) {
                return 0;  // 整数のみの場合、小数点は不可
            }
            if(has_dot) return 0;  // 小数点が2つ以上
            has_dot = 1;
        } else {
            return 0;  // 無効な文字
        }
    }
    
    return has_digit;
}

int main() {
    char input[100];
    
    // 整数のみ
    do {
        printf("整数を入力: ");
        scanf("%s", input);
        while(getchar() != '\n');
        
        if(!validate_input(input, VALIDATE_INTEGER)) {
            printf("エラー: 整数を入力してください\n");
        }
    } while(!validate_input(input, VALIDATE_INTEGER));
    printf("OK: %s\n\n", input);
    
    // 正の整数のみ
    do {
        printf("正の整数を入力: ");
        scanf("%s", input);
        while(getchar() != '\n');
        
        if(!validate_input(input, VALIDATE_POSITIVE)) {
            printf("エラー: 正の整数を入力してください\n");
        }
    } while(!validate_input(input, VALIDATE_POSITIVE));
    printf("OK: %s\n\n", input);
    
    // 小数も許可
    do {
        printf("数値を入力（小数可）: ");
        scanf("%s", input);
        while(getchar() != '\n');
        
        if(!validate_input(input, VALIDATE_DECIMAL)) {
            printf("エラー: 有効な数値を入力してください\n");
        }
    } while(!validate_input(input, VALIDATE_DECIMAL));
    printf("OK: %s\n", input);
    
    return 0;
}
