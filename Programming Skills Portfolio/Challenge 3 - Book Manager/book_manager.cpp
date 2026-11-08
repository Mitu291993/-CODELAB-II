
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Represents one book in the library.
class Book {
public:
    string title, author, id;
    int pages;
    bool borrowed;

    // Constructor to initialise book details.
    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), id(i), pages(p), borrowed(b) {}

    // Display all information about this book.
    void display() const {
        cout << "\nID: " << id << "\nTitle: " << title
             << "\nAuthor: " << author << "\nPages: " << pages
             << "\nStatus: " << (borrowed ? "Borrowed" : "Available")
             << "\n--------------------\n";
    }
};

// Loads, searches and updates the book collection.
class Library {
private:
    vector<Book> books;
    const string filename = "bookData.txt";

    // Return a pointer to a matching book, or nullptr if absent.
    Book* findBook(const string& id) {
        for (Book& book : books)
            if (book.id == id) return &book;
        return nullptr;
    }

    // Write the current book list back to the text file.
    bool saveBooks() {
        ofstream file(filename);
        if (!file) return false;
        for (const Book& book : books)
            file << book.title << ',' << book.author << ','
                 << book.pages << ',' << book.id << ','
                 << (book.borrowed ? "true" : "false") << '\n';
        file.close();
        return file.good();
    }

    // Read an ID and locate the requested book.
    Book* selectBook() {
        string id;
        cout << "Enter book ID: ";
        if (!(cin >> id)) return nullptr;
        Book* book = findBook(id);
        if (!book) cout << "Book not found.\n";
        return book;
    }

public:
    // Load comma-separated records from bookData.txt.
    bool loadBooks() {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening " << filename << "\n";
            return false;
        }
        books.clear();
        string line;

        // Read each line and separate the book details.
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, pages, id, status;
            if (getline(ss, title, ',') && getline(ss, author, ',') &&
                getline(ss, pages, ',') && getline(ss, id, ',') &&
                getline(ss, status)) {
                try {
                    size_t used = 0;
                    int count = stoi(pages, &used);

                    // Check page count and borrowed status.
                    if (used != pages.size() || count < 0 ||
                        (status != "true" && status != "false")) {
                        cout << "Skipping invalid book record.\n";
                        continue;
                    }

                    // Create and store a Book object.
                    books.emplace_back(title, author, count, id,
                                       status == "true");
                } catch (const exception&) {
                    cout << "Skipping invalid book record.\n";
                }
            } else if (!line.empty()) {
                cout << "Skipping incomplete book record.\n";
            }
        }
        return true;
    }

    // Display every book in the vector.
    void viewAllBooks() const {
        if (books.empty()) cout << "No books found.\n";
        for (const Book& book : books) book.display();
    }

    // Display a single book selected by its ID.
    void viewBook() {
        Book* book = selectBook();
        if (book) book->display();
    }

    // Change borrowed status and save it to the file.
    void updateBook(bool borrow) {
        Book* book = selectBook();
        if (!book) return;

        // Check if the book already has the requested status.
        if (book->borrowed == borrow) {
            cout << (borrow ? "Book is already borrowed.\n"
                            : "Book is already available.\n");
            return;
        }

        // Update status and attempt to save changes.
        bool previous = book->borrowed;
        book->borrowed = borrow;
        if (saveBooks())
            cout << (borrow ? "Book borrowed!\n" : "Book returned!\n");
        else {
            book->borrowed = previous;
            cout << "Error saving book data.\n";
        }
    }

    // Repeat the menu until the user chooses to exit.
    void menu() {
        int choice = 0;
        do {
            cout << "\n===== BOOK MANAGER =====\n"
                 << "1. View all books\n2. View individual book\n"
                 << "3. Borrow a book\n4. Return a book\n"
                 << "5. Exit\nEnter choice: ";

            // Handle invalid menu input.
            if (!(cin >> choice)) {
                if (cin.eof()) break;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
            }

            // Call the function selected by the user.
            switch (choice) {
                case 1: viewAllBooks(); break;
                case 2: viewBook(); break;
                case 3: updateBook(true); break;
                case 4: updateBook(false); break;
                case 5: cout << "Goodbye!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

// Main function starts the library program.
int main() {
    Library library;
    if (library.loadBooks()) library.menu();
    return 0;
}
