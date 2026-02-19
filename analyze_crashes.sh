#!/bin/bash

# WSL環境でのコアダンプ解析スクリプト
# 使用方法: ./analyze_crashes.sh [例番号]

set -e

PROGRAM="crash_test"
SOURCE="core_dump_examples.c"

# 色定義
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# ヘッダー表示
print_header() {
    echo -e "${BLUE}╔════════════════════════════════════════════════════════╗${NC}"
    echo -e "${BLUE}║${NC}$1${BLUE}║${NC}"
    echo -e "${BLUE}╚════════════════════════════════════════════════════════╝${NC}"
}

# セクション表示
print_section() {
    echo -e "${YELLOW}=== $1 ===${NC}"
}

# エラー表示
print_error() {
    echo -e "${RED}ERROR: $1${NC}"
}

# 成功表示
print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

# ステップ1：コンパイル
compile_program() {
    print_section "ステップ1: プログラムのコンパイル"
    
    if [ ! -f "$SOURCE" ]; then
        print_error "$SOURCE が見つかりません"
        exit 1
    fi
    
    if gcc -g -Wall "$SOURCE" -o "$PROGRAM" 2>&1; then
        print_success "コンパイル完了"
    else
        print_error "コンパイル失敗"
        exit 1
    fi
    echo ""
}

# ステップ2：単一の例を解析
analyze_single_example() {
    local example=$1
    
    print_header "例 $example の解析"
    echo ""
    
    print_section "実行情報"
    echo "プログラム: $PROGRAM"
    echo "例番号: $example"
    echo ""
    
    print_section "実行結果"
    
    # gdb コマンドファイルを作成
    cat > /tmp/gdb_cmd.txt << 'EOF'
run
backtrace
info locals
list
quit
EOF
    
    # gdb で実行
    echo "$example" | gdb -batch -x /tmp/gdb_cmd.txt "./$PROGRAM" 2>&1 | grep -A 100 "Program received signal\|Segmentation fault\|#0\|#1\|#2\|#3\|#4\|ptr\|value\|level\|student\|arr\|index" || true
    
    # クリーンアップ
    rm -f /tmp/gdb_cmd.txt
    
    echo ""
}

# ステップ3：詳細解析
analyze_detailed() {
    local example=$1
    
    print_header "例 $example の詳細解析"
    echo ""
    
    print_section "スタックトレース（詳細）"
    
    # gdb コマンドファイルを作成
    cat > /tmp/gdb_detailed.txt << 'EOF'
run
backtrace full
info locals
quit
EOF
    
    # gdb で実行
    echo "$example" | gdb -batch -x /tmp/gdb_detailed.txt "./$PROGRAM" 2>&1 | tail -50
    
    # クリーンアップ
    rm -f /tmp/gdb_detailed.txt
    
    echo ""
}

# ステップ4：すべての例を解析
analyze_all_examples() {
    print_header "すべての例を解析"
    echo ""
    
    for i in 1 2 3 4 5 6; do
        print_section "例 $i"
        
        # gdb コマンドファイルを作成
        cat > /tmp/gdb_cmd_$i.txt << 'EOF'
run
backtrace
info locals
quit
EOF
        
        # gdb で実行
        echo "$i" | gdb -batch -x /tmp/gdb_cmd_$i.txt "./$PROGRAM" 2>&1 | grep -A 5 "Program received signal\|Segmentation fault\|#0\|ptr\|value\|level" || true
        
        # クリーンアップ
        rm -f /tmp/gdb_cmd_$i.txt
        
        echo ""
    done
}

# メイン処理
main() {
    print_header "WSL環境でのコアダンプ解析"
    echo ""
    
    # コンパイル
    compile_program
    
    # 引数がない場合はすべての例を解析
    if [ $# -eq 0 ]; then
        analyze_all_examples
    else
        # 指定された例を解析
        local example=$1
        
        if [ "$example" = "detailed" ]; then
            if [ -z "$2" ]; then
                print_error "詳細解析には例番号を指定してください"
                echo "使用方法: $0 detailed <例番号>"
                exit 1
            fi
            analyze_detailed "$2"
        else
            analyze_single_example "$example"
        fi
    fi
    
    print_success "解析完了"
}

# 使用方法表示
show_usage() {
    echo "使用方法:"
    echo "  $0                    # すべての例を解析"
    echo "  $0 <例番号>           # 指定された例を解析（1-6）"
    echo "  $0 detailed <例番号>  # 指定された例を詳細解析"
    echo ""
    echo "例:"
    echo "  $0              # すべての例を解析"
    echo "  $0 1            # 例1を解析"
    echo "  $0 4            # 例4を解析"
    echo "  $0 detailed 1   # 例1を詳細解析"
}

# ヘルプオプション
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_usage
    exit 0
fi

# メイン処理実行
main "$@"
