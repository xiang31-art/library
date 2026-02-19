#include <stdio.h>

// ========================================
// 1. 構造体（struct）の例
// ========================================
struct Student {
    int id;           // 4バイト
    char name[50];    // 50バイト
    float gpa;        // 4バイト
};
// 合計: 58バイト（パディング含む）

// ========================================
// 2. 共有体（union）の例
// ========================================
union Data {
    int id;           // 4バイト
    char name[50];    // 50バイト
    float gpa;        // 4バイト
};
// 合計: 50バイト（最大メンバーのサイズ）

// ========================================
// 3. メモリ配置の比較
// ========================================
void demonstrate_memory_layout() {
    printf("=== メモリ配置の比較 ===\n\n");
    
    // 構造体のメモリ配置
    struct Student student;
    printf("【構造体（struct）】\n");
    printf("サイズ: %zu バイト\n", sizeof(struct Student));
    printf("id のアドレス:   %p\n", (void*)&student.id);
    printf("name のアドレス: %p\n", (void*)&student.name);
    printf("gpa のアドレス:  %p\n", (void*)&student.gpa);
    printf("→ 各メンバーが異なるメモリ位置に配置される\n\n");
    
    // 共有体のメモリ配置
    union Data data;
    printf("【共有体（union）】\n");
    printf("サイズ: %zu バイト\n", sizeof(union Data));
    printf("id のアドレス:   %p\n", (void*)&data.id);
    printf("name のアドレス: %p\n", (void*)&data.name);
    printf("gpa のアドレス:  %p\n", (void*)&data.gpa);
    printf("→ すべてのメンバーが同じメモリ位置を共有する\n\n");
}

// ========================================
// 4. 値の独立性の比較
// ========================================
void demonstrate_independence() {
    printf("=== 値の独立性の比較 ===\n\n");
    
    // 構造体：各メンバーが独立
    struct Student student;
    student.id = 12345;
    student.gpa = 3.8f;
    
    printf("【構造体（struct）】\n");
    printf("id を 12345 に設定\n");
    printf("gpa を 3.8 に設定\n");
    printf("id = %d, gpa = %.1f\n", student.id, student.gpa);
    printf("→ 両方の値が独立して保持される\n\n");
    
    // 共有体：メンバーが値を上書き
    union Data data;
    data.id = 12345;
    printf("【共有体（union）】\n");
    printf("id を 12345 に設定\n");
    printf("id = %d\n", data.id);
    
    data.gpa = 3.8f;
    printf("gpa を 3.8 に設定\n");
    printf("id = %d (上書きされた)\n", data.id);
    printf("gpa = %.1f\n", data.gpa);
    printf("→ 新しい値が前の値を上書きする\n\n");
}

// ========================================
// 5. 実用例：構造体
// ========================================
struct PersonInfo {
    int age;
    char name[30];
    float height;
};

void struct_example() {
    printf("=== 構造体の実用例 ===\n\n");
    
    struct PersonInfo person;
    person.age = 25;
    person.height = 175.5f;
    
    printf("年齢: %d\n", person.age);
    printf("身長: %.1f cm\n", person.height);
    printf("→ 複数の異なる情報を同時に保持できる\n\n");
}

// ========================================
// 6. 実用例：共有体
// ========================================
union Sensor {
    int temperature;      // 温度センサー
    int humidity;         // 湿度センサー
    int pressure;         // 気圧センサー
};

void union_example() {
    printf("=== 共有体の実用例 ===\n\n");
    
    union Sensor sensor;
    
    printf("温度センサーを読み込み: ");
    sensor.temperature = 25;
    printf("%d℃\n", sensor.temperature);
    
    printf("湿度センサーに切り替え: ");
    sensor.humidity = 60;
    printf("%d%%\n", sensor.humidity);
    printf("(温度値は上書きされた: %d)\n", sensor.temperature);
    
    printf("→ 一度に1つのセンサーデータのみ保持\n\n");
}

// ========================================
// 7. 構造体と共有体の組み合わせ
// ========================================
union Value {
    int intValue;
    float floatValue;
    char charValue;
};

struct DataPacket {
    int type;           // データ型を示す
    union Value value;  // 実際のデータ
};

void combined_example() {
    printf("=== 構造体と共有体の組み合わせ ===\n\n");
    
    struct DataPacket packet1, packet2;
    
    // パケット1：整数型
    packet1.type = 1;  // 1 = int
    packet1.value.intValue = 42;
    printf("パケット1 (int型): %d\n", packet1.value.intValue);
    
    // パケット2：浮動小数点型
    packet2.type = 2;  // 2 = float
    packet2.value.floatValue = 3.14f;
    printf("パケット2 (float型): %.2f\n", packet2.value.floatValue);
    
    printf("→ 異なる型のデータを効率的に処理\n\n");
}

// ========================================
// 8. メモリ効率の比較
// ========================================
void memory_efficiency() {
    printf("=== メモリ効率の比較 ===\n\n");
    
    struct {
        char a;
        int b;
        char c;
    } s;
    
    union {
        char a;
        int b;
        char c;
    } u;
    
    printf("構造体のサイズ: %zu バイト\n", sizeof(s));
    printf("共有体のサイズ: %zu バイト\n", sizeof(u));
    printf("→ 共有体の方がメモリ効率が良い\n\n");
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║     構造体（struct）と共有体（union）の違い            ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    demonstrate_memory_layout();
    demonstrate_independence();
    struct_example();
    union_example();
    combined_example();
    memory_efficiency();
    
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                    まとめ                              ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    printf("【構造体（struct）】\n");
    printf("  • 各メンバーが独立したメモリ領域を持つ\n");
    printf("  • すべてのメンバーを同時に保持できる\n");
    printf("  • メモリ使用量が多い\n");
    printf("  • 複数の異なる情報を扱う場合に使用\n\n");
    
    printf("【共有体（union）】\n");
    printf("  • すべてのメンバーが同じメモリ領域を共有\n");
    printf("  • 一度に1つのメンバーのみ有効\n");
    printf("  • メモリ効率が良い\n");
    printf("  • 異なる型のデータを交互に扱う場合に使用\n\n");
    
    return 0;
}
