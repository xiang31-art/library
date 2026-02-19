# 構造体（struct）と共有体（union）の違い

## 概要

| 項目 | 構造体（struct） | 共有体（union） |
|------|-----------------|-----------------|
| **メモリ配置** | 各メンバーが異なるメモリ位置 | すべてのメンバーが同じメモリ位置 |
| **メモリサイズ** | すべてのメンバーのサイズの合計 | 最大メンバーのサイズ |
| **メンバーの独立性** | 独立している | 共有している |
| **同時保持** | すべてのメンバーを同時に保持 | 一度に1つのメンバーのみ有効 |
| **メモリ効率** | 低い | 高い |
| **使用場面** | 複数の異なる情報を扱う | 異なる型のデータを交互に扱う |

---

## 1. メモリ配置の違い

### 構造体（struct）
```c
struct Student {
    int id;           // 4バイト
    char name[50];    // 50バイト
    float gpa;        // 4バイト
};
// 合計: 約58バイト（パディング含む）

メモリ配置:
┌─────────────────────────────────────────┐
│ id (4B) │ name (50B) │ gpa (4B) │ padding │
└─────────────────────────────────────────┘
```

### 共有体（union）
```c
union Data {
    int id;           // 4バイト
    char name[50];    // 50バイト
    float gpa;        // 4バイト
};
// 合計: 50バイト（最大メンバーのサイズ）

メモリ配置:
┌──────────────────────────────────────────┐
│ id / name (50B) / gpa                    │
│ (すべてが同じメモリ位置を共有)           │
└──────────────────────────────────────────┘
```

---

## 2. 値の独立性

### 構造体：各メンバーが独立
```c
struct Student student;
student.id = 12345;
student.gpa = 3.8f;

// 結果：両方の値が保持される
// id = 12345
// gpa = 3.8
```

### 共有体：メンバーが値を上書き
```c
union Data data;
data.id = 12345;        // id に値を設定
printf("%d\n", data.id);  // 12345

data.gpa = 3.8f;        // gpa に値を設定（id を上書き）
printf("%d\n", data.id);  // 不正な値（上書きされた）
printf("%.1f\n", data.gpa); // 3.8
```

---

## 3. 実用例

### 構造体の使用例：学生情報管理
```c
struct Student {
    int id;
    char name[50];
    float gpa;
    int year;
};

struct Student student = {
    .id = 1001,
    .name = "Yamada Taro",
    .gpa = 3.8f,
    .year = 2
};

// すべての情報を同時に保持・処理
printf("ID: %d, Name: %s, GPA: %.1f, Year: %d\n",
       student.id, student.name, student.gpa, student.year);
```

### 共有体の使用例：センサーデータ
```c
union Sensor {
    int temperature;      // 温度（℃）
    int humidity;         // 湿度（%）
    int pressure;         // 気圧（hPa）
};

union Sensor sensor;

// 温度センサーを読み込み
sensor.temperature = 25;
printf("温度: %d℃\n", sensor.temperature);

// 湿度センサーに切り替え（温度データは上書き）
sensor.humidity = 60;
printf("湿度: %d%%\n", sensor.humidity);
// 温度値は失われている
```

---

## 4. 構造体と共有体の組み合わせ

複数の異なる型のデータを効率的に扱う場合：

```c
union Value {
    int intValue;
    float floatValue;
    char charValue;
};

struct DataPacket {
    int type;           // データ型を示す（1=int, 2=float, 3=char）
    union Value value;  // 実際のデータ
};

struct DataPacket packet1, packet2;

// パケット1：整数型
packet1.type = 1;
packet1.value.intValue = 42;

// パケット2：浮動小数点型
packet2.type = 2;
packet2.value.floatValue = 3.14f;

// type に基づいて適切に処理
if (packet1.type == 1) {
    printf("整数: %d\n", packet1.value.intValue);
}
if (packet2.type == 2) {
    printf("浮動小数点: %.2f\n", packet2.value.floatValue);
}
```

---

## 5. メモリ効率の比較

### 構造体
```c
struct Data {
    char a;      // 1バイト + 3バイトパディング
    int b;       // 4バイト
    char c;      // 1バイト + 3バイトパディング
};
// 合計: 12バイト
```

### 共有体
```c
union Data {
    char a;      // 1バイト
    int b;       // 4バイト
    char c;      // 1バイト
};
// 合計: 4バイト（最大メンバーのサイズ）
```

---

## 6. 選択基準

### 構造体を使う場合
- ✓ 複数の異なる情報を同時に保持する必要がある
- ✓ 学生情報、従業員情報、座標など
- ✓ すべてのメンバーが常に有効である
- ✓ メモリ効率より機能性を優先

### 共有体を使う場合
- ✓ 異なる型のデータを交互に扱う
- ✓ センサーデータ、ネットワークパケット、ハードウェアレジスタなど
- ✓ 一度に1つのメンバーのみ有効
- ✓ メモリ効率が重要（組み込みシステムなど）

---

## 7. 実装上の注意点

### 構造体
```c
struct Point {
    int x;
    int y;
};

struct Point p = {10, 20};
printf("x=%d, y=%d\n", p.x, p.y);  // 両方の値が有効
```

### 共有体
```c
union Number {
    int intVal;
    float floatVal;
};

union Number num;
num.intVal = 42;
printf("%d\n", num.intVal);      // 42
printf("%f\n", num.floatVal);    // 不正な値（intVal の内容を float として解釈）
```

---

## 8. 共有体の実践的な使用例

### ハードウェアレジスタのマッピング
```c
union Register {
    unsigned int full;      // 32ビット全体
    struct {
        unsigned int low;   // 下位16ビット
        unsigned int high;  // 上位16ビット
    } half;
    struct {
        unsigned char b0;   // バイト0
        unsigned char b1;   // バイト1
        unsigned char b2;   // バイト2
        unsigned char b3;   // バイト3
    } byte;
};

union Register reg;
reg.full = 0x12345678;

printf("Full: 0x%X\n", reg.full);           // 0x12345678
printf("High: 0x%X\n", reg.half.high);      // 0x1234
printf("Low: 0x%X\n", reg.half.low);        // 0x5678
printf("Byte0: 0x%X\n", reg.byte.b0);       // 0x78
```

---

## 9. まとめ

| 特性 | 構造体 | 共有体 |
|------|-------|-------|
| メモリ共有 | なし | あり |
| メンバーの独立性 | 独立 | 共有 |
| 同時保持 | 可能 | 不可 |
| メモリサイズ | 大きい | 小さい |
| 一般的な用途 | データ構造 | 型変換、ハードウェア |

**選択のポイント：**
- 複数の情報を同時に保持 → **構造体**
- 異なる型のデータを交互に扱う → **共有体**
- メモリ効率が重要 → **共有体**
- 機能性を優先 → **構造体**

