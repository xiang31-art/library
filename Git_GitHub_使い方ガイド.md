# Git / GitHub 使い方ガイド
> C言語学習ファイルを仲間と共有・管理するための入門ガイド

---

## Gitとは？ GitHubとは？

- **Git** … ファイルの変更履歴をローカル（自分のPC）で管理するツール
- **GitHub** … Gitで管理したファイルをインターネット上に保存・共有できるサービス

```
自分のPC（Git） ←→ GitHub（クラウド）
```

---

## 1. 最初の準備

### Gitのインストール確認
```bash
git --version
```
> Gitが正しくインストールされているか確認する。バージョン番号が表示されれば OK。

### ユーザー情報の設定（初回のみ）
```bash
git config --global user.name "あなたの名前"
git config --global user.email "your@email.com"
```
> コミット（変更の記録）に紐づく名前とメールアドレスを設定する。GitHubのアカウント情報と合わせると管理しやすい。

---

## 2. リポジトリの作成・取得

### 新しいリポジトリをローカルに作る
```bash
git init
```
> 現在のフォルダをGitで管理できる状態にする。`.git`という隠しフォルダが作られ、ここに履歴が保存される。

### GitHubのリポジトリをローカルにコピーする
```bash
git clone https://github.com/ユーザー名/リポジトリ名.git
```
> GitHub上にあるリポジトリを自分のPCにまるごとダウンロードする。仲間のリポジトリを共有してもらうときに使う。

---

## 3. 変更を記録する（コミット）

### 変更状態を確認する
```bash
git status
```
> どのファイルが変更・追加・削除されたかを一覧表示する。コミット前に必ず確認する習慣をつけると良い。

### ファイルをステージングに追加する
```bash
git add ファイル名
# 例：
git add array_max_detailed.c

# 全ファイルをまとめて追加する場合
git add .
```
> コミットに含めるファイルを選択する操作。「ステージング」とは「次のコミットに含める準備」のこと。

### 変更を記録する（コミット）
```bash
git commit -m "コミットメッセージ"
# 例：
git commit -m "ポインタの練習問題を追加"
```
> ステージングしたファイルの変更をローカルに記録する。メッセージは「何をしたか」が分かるように書く。

### 変更履歴を確認する
```bash
git log --oneline
```
> これまでのコミット履歴を一行ずつ表示する。`--oneline`を付けるとコンパクトに見られる。

---

## 4. GitHubと連携する

### リモートリポジトリを登録する
```bash
git remote add origin https://github.com/ユーザー名/リポジトリ名.git
```
> ローカルのGitにGitHubのURLを「origin」という名前で登録する。`git init`から始めた場合に必要な手順。

### GitHubにアップロードする（プッシュ）
```bash
git push origin main
```
> ローカルのコミット履歴をGitHubに送信する。`main`はブランチ名で、初期設定では`main`または`master`になっている。

### GitHubから最新を取得する（プル）
```bash
git pull origin main
```
> GitHubにある最新の変更を自分のPCに取り込む。仲間が更新したファイルを受け取るときに使う。

---

## 5. ブランチを使う（複数人での作業に重要）

### ブランチの一覧を確認する
```bash
git branch
```
> 現在存在するブランチの一覧を表示する。`*`が付いているのが現在作業中のブランチ。

### 新しいブランチを作って移動する
```bash
git checkout -b ブランチ名
# 例：
git checkout -b feature/pointer-exercises
```
> 新しいブランチを作成し、そこに移動する。メインのコードを壊さずに作業できるため、複数人での開発に必須。

### ブランチを切り替える
```bash
git checkout ブランチ名
# 例：
git checkout main
```
> 指定したブランチに移動する。作業するブランチを間違えないよう、`git status`で確認する習慣をつけると良い。

### ブランチをマージする
```bash
git merge ブランチ名
# 例：mainブランチにいる状態で
git merge feature/pointer-exercises
```
> 指定したブランチの変更を現在のブランチに取り込む。作業が完了したらmainブランチにマージして統合する。

---

## 6. GitHubのWeb操作

### リポジトリの作成（GitHub上）
1. GitHubにログイン
2. 右上の `+` → `New repository` をクリック
3. リポジトリ名・説明を入力し `Create repository` をクリック

### Pull Request（プルリクエスト）
> ブランチで作業した変更をmainブランチに取り込んでほしいと申請する機能。
> 仲間にコードをレビューしてもらってからマージできるため、複数人での学習に最適。

手順：
1. GitHubのリポジトリページを開く
2. `Pull requests` タブ → `New pull request`
3. マージ元のブランチを選択して `Create pull request`
4. 説明を書いて送信 → 仲間がレビュー・承認後にマージ

### Issues（イシュー）
> 「この問題が分からない」「ここを直してほしい」などをメモ・共有できる機能。
> 学習中の疑問点や課題をチームで管理するのに便利。

---

## 7. よくある操作の流れ（複数人での学習）

```
【最初の一回】
1. GitHubでリポジトリを作成
2. git clone でローカルにコピー（メンバー全員）

【毎日の作業】
1. git pull origin main        ← 最新を取得
2. git checkout -b 作業ブランチ ← ブランチを作る
3. ファイルを編集・追加
4. git add .
5. git commit -m "メッセージ"
6. git push origin 作業ブランチ ← GitHubに送る
7. GitHubでPull Requestを作成
8. 仲間にレビューしてもらってマージ
```

---

## 8. よく使うコマンド一覧

| コマンド | 用途 |
|---|---|
| `git init` | リポジトリを新規作成 |
| `git clone <URL>` | リモートをローカルにコピー |
| `git status` | 変更状態を確認 |
| `git add <ファイル>` | ステージングに追加 |
| `git commit -m "msg"` | 変更を記録 |
| `git log --oneline` | 履歴を確認 |
| `git push origin main` | GitHubにアップロード |
| `git pull origin main` | GitHubから取得 |
| `git branch` | ブランチ一覧を表示 |
| `git checkout -b <名前>` | ブランチを作成して移動 |
| `git merge <ブランチ>` | ブランチをマージ |

---

## 9. .gitignore について

コンパイル済みの実行ファイル（`.exe`）など、Gitで管理しなくてよいファイルを除外できる。

```gitignore
# コンパイル済みファイルを除外
*.exe
*.o

# OSが自動生成するファイル
.DS_Store
Thumbs.db
```

> このワークスペースの`.gitignore`に追記することで、`.exe`ファイルが誤ってコミットされるのを防げる。

---

*参考：[Git公式ドキュメント](https://git-scm.com/doc) / [GitHub Docs](https://docs.github.com/ja)*
