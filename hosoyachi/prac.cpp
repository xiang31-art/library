#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Book
{
  string title;
  string author;
  int year;
  double price;
  int avail;
};

class Book_Manager
{
private:
  vector<Book> books;

public:
  // 本の追加
  void add_book(const string &title, const string &author, int year, double price, int avail)
  {
    books.push_back({title, author, year, price, avail});
    sort(books.begin(), books.end(), [](const Book &a, const Book &b)
         { return a.title < b.title; });
  }

  // 本の詳細表示
  vector<Book> books_view()
  {
    return books;
  }

  // 本の貸出
  void borrow_book(int input_num)
  {
    if (input_num > books.size() - 1 || input_num < 0)
    {
      cout << "予期せぬ値が入力されました" << endl;
      return;
    }
    if (books.at(input_num).avail == 0)
    {
      cout << "その本の在庫はありません" << endl;
      return;
    }

    books.at(input_num).avail--;
    cout << books.at(input_num).title << "を借りました。返却期限は2週間です" << endl;
  }

  // 本の返却
  void return_book(int input_num)
  {
    if (input_num > books.size() - 1 || input_num < 0)
    {
      cout << "予期せぬ値が入力されました" << endl;
      return;
    }

    books.at(input_num).avail++;
    cout << books.at(input_num).title << "を返却しました。" << endl;
  }
};

auto BM = Book_Manager();

int main()
{
  while (true)
  {
    int usernum;
    cout << "1.本の追加 2.本の表示 3.本の貸出 4.本の返却 5.終了 ->";
    cin >> usernum;

    switch (usernum)
    {
    case 1:
    {
      string title, author;
      int year, avail;
      double price;

      cout << "\n";
      cout << "本の情報を入力してください(著名):";
      cin >> title;
      cout << "本の情報を入力してください(著者):";
      cin >> author;
      cout << "本の情報を入力してください(出版年):";
      cin >> year;
      cout << "本の情報を入力してください(価格):";
      cin >> price;
      cout << "本の情報を入力してください(在庫数):";
      cin >> avail;
      cout << "\n";
      cout << "本の情報を追加しました" << endl;
      cout << "\n";

      BM.add_book(title, author, year, price, avail);
      break;
    }
    case 2:
    {
      cout << "\n";
      cout << "本の情報一覧" << endl;
      for (const Book &b : BM.books_view())
      {
        cout << "タイトル:" << b.title << " 著者:" << b.author << " 出版年:" << b.year << " 価格:" << b.price << " 在庫:" << ((b.avail != 0) ? "あり" : "なし") << endl;
      }
      cout << "\n";
      break;
    }

    case 3:
    {
      int input_num;
      vector<Book> books = BM.books_view();

      cout << "\n";
      for (int i = 0; i < books.size(); i++)
      {
        cout << i << " タイトル:" << books.at(i).title << " 在庫数:" << books.at(i).avail << endl;
      }
      cout << "借りたい本の番号を入力:";
      cin >> input_num;
      BM.borrow_book(input_num);

      cout << "\n";

      break;
    }

    case 4:
    {
      int input_num;
      vector<Book> books = BM.books_view();

      cout << "\n";
      for (int i = 0; i < books.size(); i++)
      {
        cout << i << " タイトル:" << books.at(i).title << " 在庫数:" << books.at(i).avail << endl;
      }
      cout << "返したい本の番号を入力:";
      cin >> input_num;
      BM.return_book(input_num);

      cout << "\n";

      break;
    }

    case 5:
    {
      return 0;
    }

    default:
    {
      cout << "予期せぬ値が入力されました" << endl;
      break;
    }
    }
  }
}