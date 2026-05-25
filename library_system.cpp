#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>

// ==========================================================================
// DATA STRUCTURES
// ==========================================================================

struct Book {
    int id;
    std::string title;
    std::string author;
    std::string genre;
    std::string status; // "Available" or "Issued"

    Book(int i, std::string t, std::string a, std::string g) 
        : id(i), title(t), author(a), genre(g), status("Available") {}
};

struct Transaction {
    std::string action; // "Issue" or "Return"
    int bookId;
    std::string title;
    std::string timestamp;

    Transaction(std::string act, int id, std::string t, std::string ts)
        : action(act), bookId(id), title(t), timestamp(ts) {}
};

// Node structure for Custom Linked-List Stack
struct StackNode {
    Transaction data;
    StackNode* next;

    StackNode(Transaction tx, StackNode* n = nullptr) 
        : data(tx), next(n) {}
};

// Custom Stack Implementation (LIFO)
class TransactionStack {
private:
    StackNode* topNode;
    int stackSize;

public:
    TransactionStack() : topNode(nullptr), stackSize(0) {}

    ~TransactionStack() {
        clear();
    }

    void push(Transaction tx) {
        topNode = new StackNode(tx, topNode);
        stackSize++;
    }

    Transaction pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow: Cannot pop from empty stack.");
        }
        StackNode* temp = topNode;
        Transaction tx = temp->data;
        topNode = topNode->next;
        delete temp;
        stackSize--;
        return tx;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int size() const {
        return stackSize;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Helper to get transaction history from top to bottom (for display)
    std::vector<Transaction> getHistory() const {
        std::vector<Transaction> history;
        StackNode* curr = topNode;
        while (curr != nullptr) {
            history.push_back(curr->data);
            curr = curr->next;
        }
        return history;
    }
};

// ==========================================================================
// UTILITY FUNCTIONS
// ==========================================================================

// Helper to convert string to lowercase for case-insensitive matching
std::string toLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return str;
}

// Get current timestamp
std::string getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// Trim whitespace from string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// ==========================================================================
// ALGORITHMS
// ==========================================================================

// Bubble Sort Implementation
// Sorts the books in-place
void bubbleSort(std::vector<Book>& books, std::string sortBy = "title") {
    int n = books.size();
    std::cout << "\n[Bubble Sort] Starting sort by: " << (sortBy == "id" ? "ID" : "TITLE") << "\n";
    
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            bool condition = false;
            if (sortBy == "id") {
                condition = (books[j].id > books[j + 1].id);
            } else {
                condition = (toLowerCase(books[j].title) > toLowerCase(books[j + 1].title));
            }

            std::cout << "  Comparing: '" << books[j].title << "' vs '" << books[j + 1].title << "'\n";

            if (condition) {
                // Swap elements
                std::swap(books[j], books[j + 1]);
                swapped = true;
                std::cout << "    --> SWAPPED: '" << books[j].title << "' <--> '" << books[j + 1].title << "'\n";
            }
        }
        
        // If no two elements were swapped in inner loop, then list is sorted
        if (!swapped) {
            break;
        }
    }
    std::cout << "[Bubble Sort] Sorting completed successfully.\n";
}

// Binary Search Implementation
// Assumes books list is sorted by title
int binarySearch(const std::vector<Book>& books, std::string targetTitle) {
    int low = 0;
    int high = books.size() - 1;
    std::string target = toLowerCase(trim(targetTitle));

    std::cout << "\n[Binary Search] Searching for title: '" << targetTitle << "'\n";

    while (low <= high) {
        int mid = low + (high - low) / 2;
        std::string midVal = toLowerCase(books[mid].title);

        std::cout << "  Checking midpoint index " << mid << ": '" << books[mid].title 
                  << "' (Bounds: Low=" << low << ", High=" << high << ")\n";

        if (midVal == target) {
            std::cout << "[Binary Search] Target found at index " << mid << "!\n";
            return mid;
        }
        else if (midVal < target) {
            std::cout << "    '" << books[mid].title << "' < '" << targetTitle << "' (Looking in the RIGHT half)\n";
            low = mid + 1;
        }
        else {
            std::cout << "    '" << books[mid].title << "' > '" << targetTitle << "' (Looking in the LEFT half)\n";
            high = mid - 1;
        }
    }

    std::cout << "[Binary Search] Target book not found.\n";
    return -1;
}

// ==========================================================================
// PRESET SEEDER
// ==========================================================================

void loadPresets(std::vector<Book>& booksList) {
    booksList.clear();
    booksList.push_back(Book(320, "Java Programming", "Herbert Schildt", "Programming"));
    booksList.push_back(Book(110, "C Language", "Dennis Ritchie", "Programming"));
    booksList.push_back(Book(215, "Python Basics", "Dusty Phillips", "Programming"));
    booksList.push_back(Book(410, "Data Structures", "Mark Allen Weiss", "Algorithms"));
    booksList.push_back(Book(150, "Computer Networks", "Andrew S. Tanenbaum", "Networking"));
    booksList.push_back(Book(180, "Database Systems", "Abraham Silberschatz", "Database"));
    booksList.push_back(Book(520, "Artificial Intelligence", "Stuart Russell", "AI / ML"));
    std::cout << "\n[System] Successfully loaded 7 preset books (Unsorted).\n";
}

// ==========================================================================
// MAIN CLI LOOP
// ==========================================================================

void displayMenu() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "      SMART LIBRARY MANAGEMENT SYSTEM (C++ DSA)\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << "1. Add Book (Admin)\n";
    std::cout << "2. Sort Books using Bubble Sort\n";
    std::cout << "3. Search Book using Binary Search\n";
    std::cout << "4. Issue a Book\n";
    std::cout << "5. Return a Book\n";
    std::cout << "6. Undo Last Transaction (Pop Stack)\n";
    std::cout << "7. Display Inventory & Status\n";
    std::cout << "8. Display Transaction Stack History\n";
    std::cout << "9. Load Pre-configured Mock Data\n";
    std::cout << "0. Exit\n";
    std::cout << std::string(50, '=') << "\n";
}

int main() {
    std::vector<Book> libraryBooks;
    TransactionStack transactionStack;
    std::string sortedStatus = "UNSORTED"; // "UNSORTED", "TITLE", "ID"

    // Seed preset books
    loadPresets(libraryBooks);

    while (true) {
        displayMenu();
        std::cout << "Enter choice (0-9): ";
        std::string inputChoice;
        if (!std::getline(std::cin, inputChoice)) {
            break;
        }

        inputChoice = trim(inputChoice);
        if (inputChoice.empty()) continue;

        if (inputChoice == "1") {
            std::cout << "\n--- ADMIN: ADD NEW BOOK ---\n";
            std::cout << "Enter Book ID (Numeric): ";
            std::string idStr;
            std::getline(std::cin, idStr);
            int bookId = 0;
            try {
                bookId = std::stoi(trim(idStr));
            } catch (...) {
                std::cout << "[Error] Invalid ID format. Must be an integer.\n";
                continue;
            }

            // Check if ID already exists
            bool exists = false;
            for (const auto& b : libraryBooks) {
                if (b.id == bookId) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                std::cout << "[Error] A book with this ID already exists.\n";
                continue;
            }

            std::cout << "Enter Book Title: ";
            std::string title;
            std::getline(std::cin, title);
            title = trim(title);

            std::cout << "Enter Book Author: ";
            std::string author;
            std::getline(std::cin, author);
            author = trim(author);

            std::cout << "Enter Book Genre: ";
            std::string genre;
            std::getline(std::cin, genre);
            genre = trim(genre);

            libraryBooks.push_back(Book(bookId, title, author, genre));
            sortedStatus = "UNSORTED"; // Reset sorting status
            std::cout << "[Success] Added Book ID: " << bookId << ", Title: '" << title << "'\n";
        }
        else if (inputChoice == "2") {
            if (libraryBooks.empty()) {
                std::cout << "[Warning] No books in library to sort.\n";
                continue;
            }

            std::cout << "\n--- BUBBLE SORT OPTION ---\n";
            std::cout << "a. Sort alphabetically by Title\n";
            std::cout << "b. Sort numerically by Book ID\n";
            std::cout << "Select sort attribute (a/b): ";
            std::string sortAttr;
            std::getline(std::cin, sortAttr);
            sortAttr = toLowerCase(trim(sortAttr));

            if (sortAttr == "a") {
                bubbleSort(libraryBooks, "title");
                sortedStatus = "TITLE";
            } else if (sortAttr == "b") {
                bubbleSort(libraryBooks, "id");
                sortedStatus = "ID";
            } else {
                std::cout << "[Error] Invalid selection. Sorting aborted.\n";
            }
        }
        else if (inputChoice == "3") {
            if (libraryBooks.empty()) {
                std::cout << "[Warning] Library is empty.\n";
                continue;
            }

            if (sortedStatus != "TITLE") {
                std::cout << "[Warning] Binary Search requires books to be sorted alphabetically by Title first!\n";
                std::cout << "Please sort books (Option 2 -> Title) before searching.\n";
                continue;
            }

            std::cout << "\n--- BINARY SEARCH ---\n";
            std::cout << "Enter exact book title to search: ";
            std::string query;
            std::getline(std::cin, query);
            query = trim(query);

            int index = binarySearch(libraryBooks, query);
            if (index != -1) {
                const Book& b = libraryBooks[index];
                std::cout << "[Result] Book found! Details:\n"
                          << "  ID: " << b.id << "\n"
                          << "  Title: '" << b.title << "'\n"
                          << "  Author: '" << b.author << "'\n"
                          << "  Genre: '" << b.genre << "'\n"
                          << "  Status: " << b.status << "\n";
            } else {
                std::cout << "[Result] Book not found.\n";
            }
        }
        else if (inputChoice == "4") {
            if (libraryBooks.empty()) {
                std::cout << "[Warning] Library is empty.\n";
                continue;
            }

            std::cout << "\n--- ISSUE BOOK ---\n";
            std::cout << "Enter Book ID to issue: ";
            std::string idStr;
            std::getline(std::cin, idStr);
            int bId = 0;
            try {
                bId = std::stoi(trim(idStr));
            } catch (...) {
                std::cout << "[Error] Invalid ID format.\n";
                continue;
            }

            Book* targetBook = nullptr;
            for (auto& b : libraryBooks) {
                if (b.id == bId) {
                    targetBook = &b;
                    break;
                }
            }

            if (!targetBook) {
                std::cout << "[Error] Book not found.\n";
            } else if (targetBook->status == "Issued") {
                std::cout << "[Error] Book is already checked out.\n";
            } else {
                targetBook->status = "Issued";
                Transaction tx("Issue", targetBook->id, targetBook->title, getTimestamp());
                transactionStack.push(tx);
                std::cout << "[Success] PUSHED TO STACK: Issued '" << targetBook->title << "'\n";
            }
        }
        else if (inputChoice == "5") {
            if (libraryBooks.empty()) {
                std::cout << "[Warning] Library is empty.\n";
                continue;
            }

            std::cout << "\n--- RETURN BOOK ---\n";
            std::cout << "Enter Book ID to return: ";
            std::string idStr;
            std::getline(std::cin, idStr);
            int bId = 0;
            try {
                bId = std::stoi(trim(idStr));
            } catch (...) {
                std::cout << "[Error] Invalid ID format.\n";
                continue;
            }

            Book* targetBook = nullptr;
            for (auto& b : libraryBooks) {
                if (b.id == bId) {
                    targetBook = &b;
                    break;
                }
            }

            if (!targetBook) {
                std::cout << "[Error] Book not found.\n";
            } else if (targetBook->status == "Available") {
                std::cout << "[Error] Book is already available in library.\n";
            } else {
                targetBook->status = "Available";
                Transaction tx("Return", targetBook->id, targetBook->title, getTimestamp());
                transactionStack.push(tx);
                std::cout << "[Success] PUSHED TO STACK: Returned '" << targetBook->title << "'\n";
            }
        }
        else if (inputChoice == "6") {
            if (transactionStack.isEmpty()) {
                std::cout << "\n[Stack Status] Stack is empty. No transaction to undo.\n";
                continue;
            }

            Transaction lastTx = transactionStack.pop();
            Book* targetBook = nullptr;
            for (auto& b : libraryBooks) {
                if (b.id == lastTx.bookId) {
                    targetBook = &b;
                    break;
                }
            }

            std::cout << "\n[Stack POP] Popped last transaction: Undo " << lastTx.action 
                      << " of '" << lastTx.title << "'\n";

            if (targetBook) {
                if (lastTx.action == "Issue") {
                    targetBook->status = "Available";
                    std::cout << "  --> Book status restored: '" << targetBook->title << "' is now Available.\n";
                } else if (lastTx.action == "Return") {
                    targetBook->status = "Issued";
                    std::cout << "  --> Book status restored: '" << targetBook->title << "' is now Issued.\n";
                }
            } else {
                std::cout << "[Warning] Book associated with transaction no longer exists.\n";
            }
        }
        else if (inputChoice == "7") {
            std::cout << "\n--- LIBRARY INVENTORY ---\n";
            std::cout << "Sorted status: " << sortedStatus << "\n";
            std::cout << "Total Books: " << libraryBooks.size() << "\n";
            std::cout << std::string(75, '-') << "\n";
            for (size_t i = 0; i < libraryBooks.size(); ++i) {
                const auto& b = libraryBooks[i];
                std::cout << "[" << i << "] ID: " << std::left << std::setw(4) << b.id 
                          << " | Title: " << std::setw(24) << b.title 
                          << " | Author: " << std::setw(20) << b.author 
                          << " | Genre: " << std::setw(12) << b.genre 
                          << " | Status: " << b.status << "\n";
            }
            std::cout << std::string(75, '-') << "\n";
        }
        else if (inputChoice == "8") {
            std::cout << "\n--- TRANSACTION STACK (LIFO history) ---\n";
            if (transactionStack.isEmpty()) {
                std::cout << "Stack is empty.\n";
            } else {
                std::cout << "Stack size: " << transactionStack.size() << "\n";
                std::cout << "Top of Stack (LIFO)\n";
                std::cout << " |\n";
                std::cout << " v\n";
                auto history = transactionStack.getHistory();
                for (const auto& tx : history) {
                    std::cout << "  [Action: " << std::left << std::setw(6) << tx.action << "] "
                              << "'" << tx.title << "' (ID: " << tx.bookId << ") at " << tx.timestamp << "\n";
                }
                std::cout << " ---\n";
                std::cout << "Stack Base\n";
            }
        }
        else if (inputChoice == "9") {
            loadPresets(libraryBooks);
            sortedStatus = "UNSORTED";
        }
        else if (inputChoice == "0") {
            std::cout << "\nExiting AetherLib C++ DSA system. Goodbye!\n";
            break;
        }
        else {
            std::cout << "[Error] Invalid choice, please try again.\n";
        }
    }

    return 0;
}
