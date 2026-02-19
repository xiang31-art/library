# OpenGL プロジェクト用 Makefile

# コンパイラ
CC = gcc

# インクルードパスとライブラリパス
INCLUDE = -I"C:/Program Files (x86)/mingw64/include"
LIBDIR = -L"C:/Program Files (x86)/mingw64/lib"

# リンクするライブラリ
LIBS = -lglfw3 -lglew32 -lopengl32 -lgdi32

# コンパイルオプション
CFLAGS = -Wall

# ターゲット
TARGET = main.exe

# ソースファイル
SRC = main.c

# ビルドルール
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(INCLUDE) $(LIBDIR) $(LIBS) $(CFLAGS)

# 実行
run: $(TARGET)
	./$(TARGET)

# クリーンアップ
clean:
	del $(TARGET)

# ヘルプ
help:
	@echo 使い方:
	@echo   make       - コンパイル
	@echo   make run   - コンパイルして実行
	@echo   make clean - 実行ファイルを削除
