📚 Smart Library Management System (C++ DSA)
A console-based Library Management System developed in C++ using core Data Structures and Algorithms (DSA) concepts such as:
Bubble Sort
Binary Search
Stack (Linked List Implementation)
This project demonstrates how DSA concepts can be applied in a real-world application like a digital library system.
🚀 Features
✅ Add new books to library
✅ Sort books using Bubble Sort
✅ Search books using Binary Search
✅ Issue and return books
✅ Undo last transaction using Stack (LIFO)
✅ Display library inventory
✅ Display transaction history
✅ Load preset mock data
🛠️ Technologies Used
Language: C++
Concepts: DSA, OOP, STL
Compiler: g++ / VS Code / CodeBlocks
📂 Data Structures Used
Data Structure	Purpose
Vector	Store books dynamically
Stack (Linked List)	Store transaction history
Structures	Store book & transaction data
📖 Algorithms Used
🔹 Bubble Sort
Used to sort books:
Alphabetically by title
Numerically by book ID
Time Complexity
Best Case: O(n)
Worst Case: O(n²)
🔹 Binary Search
Used for fast searching of books by title.
Requirement
Books must be sorted alphabetically before searching.
Time Complexity
Best Case: O(1)
Worst Case: O(log n)
🔹 Stack (LIFO)
Custom linked-list stack implementation used for:
Storing issue/return transactions
Undoing the latest transaction
Operations
Push
Pop
Display history
📦 Project Structure
library_system.cpp
⚙️ How to Run
🔹 Compile
g++ library_system.cpp -o library_system
🔹 Run
./library_system
🖥️ Menu Options
1. Add Book
2. Sort Books using Bubble Sort
3. Search Book using Binary Search
4. Issue a Book
5. Return a Book
6. Undo Last Transaction
7. Display Inventory
8. Display Transaction History
9. Load Mock Data
0. Exit
📚 Preset Books Included
Java Programming
C Language
Python Basics
Data Structures
Computer Networks
Database Systems
Artificial Intelligence
🔄 Example Workflow
Load preset books
Sort books alphabetically
Search a book using Binary Search
Issue a book
Undo transaction using Stack
🎯 Learning Outcomes
This project helps understand:
Real-world implementation of DSA
Searching and sorting algorithms
Stack using linked list
CLI-based application development
Object-oriented programming in C++
🔮 Future Improvements
File handling for permanent storage
Login authentication
GUI version
Fine calculation system
Student management
Queue for waiting list
Database integration
👨‍💻 Author
Developed as a DSA Mini Project in C++ for academic learning and practical implementation of algorithms.
📜 License
This project is open-source and free to use for educational purposes.
