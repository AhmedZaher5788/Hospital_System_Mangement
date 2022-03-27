#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct book {
    int book_id;
    string book_name;
    int total_quantity;
    int total_borrowed;

    book() {
        book_id = -1;
        book_name = "";
        total_quantity = total_borrowed = 0;
    }

    void read_input() {
        cout << "Enter book info: book_id & book_name & total quantity: ";
        cin >> book_id >> book_name >> total_quantity;
        total_borrowed = 0;
    }


    bool borrow_book(int user_id) {
        if (total_quantity - total_borrowed == 0)
            return false;
        ++total_borrowed;
        return true;
    }

    void return_copy() {
        assert(total_borrowed > 0);
        --total_borrowed;
    }

    bool has_prefix(string pre) {
        if (book_name.size() < pre.size())
            return false;

        for (int i = 0; i < (int) pre.size(); ++i) {
            if (pre[i] != book_name[i])
                return false;
        }
        return true;
    }
    void print_book() {
        cout << "book_id = " << book_id << " book_name = " << book_name << " total_quantity "
             << total_quantity << " total_borrowed " << total_borrowed << endl;
    }
};

bool cmp_book_by_name(book &a, book& b) {
    return a.book_name < b.book_name;
}

bool cmp_book_by_id(book &a, book& b) {
    return a.book_id < b.book_id;
}

struct user {
    int user_id;
    string user_name;
    int borrowed_books_ids_lst[MAX_BOOKS];
    int len;

    user() {
        user_id = -1;
        user_name = "";
        len = 0;
    }

    void read() {
        cout << "Enter user book_name and national book_id: ";
        cin >> user_name >> user_id;
    }

    void user_borrow_book(int book_id) {
        borrowed_books_ids_lst[len++] = book_id;
    }
    void return_copy(int book_id) {
        bool is_removed = false;
        for (int i = 0; i < len; ++i) {
            if (borrowed_books_ids_lst[i] == book_id) {
                // Let's shift the array to the right to remove this entry
                for (int j = i + 1; j < len; ++j)
                    borrowed_books_ids_lst[j - 1] = borrowed_books_ids_lst[j];
                is_removed = true;
                --len;
                break;
            }
        }
        if (!is_removed)
            cout << "User " << user_name << " never borrowed book book_id " << book_id
                 << "\n";
    }

    bool is_borrowed(int book_id) {
        for (int i = 0; i < len; ++i) {
            if (book_id == borrowed_books_ids_lst[i])
                return true;
        }
        return false;
    }

    void print() {
        sort(borrowed_books_ids_lst, borrowed_books_ids_lst + len);

        cout << "user " << user_name << " book_id " << user_id << " borrowed books ids: ";
        for (int i = 0; i < len; ++i)
            cout << borrowed_books_ids_lst[i] << " ";
        cout << endl;
    }
};

struct library_System {
    int total_books;
    book books[MAX_BOOKS];
    int total_users;
    user users[MAX_USERS];

    library_System() {
        total_books = total_users = 0;
    }

    void main() {
        while (true) {
            int choice = menu();

            if (choice == 1)
                add_book();
            else if (choice == 2)
                search_books_by_prefix();
            else if (choice == 3)
                print_who_borrowed_book_by_name();
            else if (choice == 4)
                print_library_by_id();
            else if (choice == 5)
                print_library_by_name();
            else if (choice == 6)
                add_user();
            else if (choice == 7)
                user_borrow_book();
            else if (choice == 8)
                user_return_book();
            else if (choice == 9)
                print_users();
            else
                break;
        }
    }

    int menu() {
        int choice = -1;
        while (choice == -1) {
            if (false) {
                cout << "\nLibrary Menu;\n";
                cout << "1) add_book\n";
                cout << "2) search_books_by_prefix\n";
                cout << "3) print_who_borrowed_book_by_name\n";
                cout << "4) print_library_by_id\n";
                cout << "5) print_library_by_name\n";
                cout << "6) add_user\n";
                cout << "7) user_borrow_book\n";
                cout << "8) user_return_book\n";
                cout << "9) print_users\n";
                cout << "10) Exit\n";
            }

            cout << endl << "Enter your menu choice [1 - 10]: ";
            cin >> choice;

            if ( choice  < 1 || choice > 10) {
                cout << "Invalid choice. Try again\n";
                choice = -1;
            }
        }
        return choice;
    }

    void add_book() {
        books[total_books++].read_input();
    }

    void search_books_by_prefix() {
        string prefix;
        cout << "Enter book book_name prefix: ";
        cin >> prefix;

        bool has_pre = 0;
        for (int i = 0; i < total_books; ++i) {
            if (books[i].has_prefix(prefix)){
                cout << books[i].book_name << "\n";
                has_pre = true;
            }
        }

        if(!has_pre)
            cout<<"No books with such prefix\n";
    }

    void add_user() {
        users[total_users++].read();
    }

    int find_book_idx_by_name(string name) {
        for (int i = 0; i < total_books; ++i) {
            if (name == books[i].book_name)
                return i;
        }
        return -1;
    }

    int find_user_idx_by_name(string name) {
        for (int i = 0; i < total_users; ++i) {
            if (name == users[i].user_name)
                return i;
        }
        return -1;
    }

    bool read_user_name_and_book_name(int &user_idx, int &book_idx, int tries = 4) {
        string user_name;
        string book_name;

        while (tries--) {
            cout << "Enter user book_name and book book_name: ";
            cin >> user_name >> book_name;

            user_idx = find_user_idx_by_name(user_name);

            if (user_idx == -1) {
                cout << "Invalid user book_name. Try again\n";
                continue;
            }
            book_idx = find_book_idx_by_name(book_name);

            if (book_idx == -1) {
                cout << "Invalid book book_name. Try again\n";
                continue;
            }
            return true;
        }
        cout << "You did several tries! Please Try again.";
        return false;
    }

    void user_borrow_book() {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int user_id = users[user_idx].user_id;
        int book_id = books[book_idx].book_id;

        if (!books[book_idx].borrow_book(user_id))
            cout << "No more copies available now, Please come Later" << endl;
        else
            users[user_idx].user_borrow_book(book_id);
    }

    void user_return_book() {
        int user_idx, book_idx;

        if (!read_user_name_and_book_name(user_idx, book_idx))
            return;

        int book_id = books[book_idx].book_id;
        books[book_idx].return_copy();
        users[user_idx].return_copy(book_id);
    }

    void print_library_by_id() {
        sort(books, books + total_books, cmp_book_by_id);

        cout << endl;
        for (int i = 0; i < total_books; ++i)
            books[i].print_book();
    }

    void print_library_by_name() {
        sort(books, books + total_books, cmp_book_by_name);

        cout << endl;
        for (int i = 0; i < total_books; ++i)
            books[i].print_book();
    }

    void print_users() {
        cout << endl;
        for (int i = 0; i < total_users; ++i)
            users[i].print();
    }

    void print_who_borrowed_book_by_name() {
        string book_name;
        cout << "Enter book book_name: " << endl;
        cin >> book_name;

        int book_idx = find_book_idx_by_name(book_name);

        if (book_idx == -1) {
            cout << "Invalid book book_name." << endl;
            return;
        }
        int book_id = books[book_idx].book_id;

        if (books[book_idx].total_borrowed == 0) {
            cout << "No borrowed copies "<<endl;
            return;
        }

        for (int i = 0; i < total_users; ++i) {
            if (users[i].is_borrowed(book_id))
                cout << users[i].user_name <<endl;
        }
    }
};

int main() {

    library_System library;
    library.main();
    return 0;
}