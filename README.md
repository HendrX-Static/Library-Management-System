# Library Management System

## Overview
This Library Management System is a C-based console application that demonstrates proficiency in Data Structures and Algorithms (DSA). The project implements a robust system for managing books, borrowing processes, and waiting lists in a library setting.

## Key Features
- Add new books to the library
- Display all books in the collection
- Search for books by title
- Borrow and return books
- Manage waiting lists for borrowed books
- View currently borrowed books

## Data Structures Implemented
1. **Linked Lists**: Used for storing the main book collection and the list of borrowed books.
2. **Queues**: Implemented for managing waiting lists for each book.
3. **Structs**: Custom structures for Books and Waiting Users to encapsulate related data.

## Algorithms and Concepts Demonstrated
- **Dynamic Memory Allocation**: Utilizing `malloc()` for creating new nodes in linked lists and queues.
- **Searching**: Implemented book search functionality.
- **Queue Operations**: Enqueue and Dequeue operations for managing waiting lists.
- **Linked List Traversal**: For displaying books and managing the borrowed books list.
- **Basic File I/O**: (Note: While not implemented in the current version, this could be a potential enhancement)

## Skills Showcased
- **Data Structure Design**: Creating and managing complex data structures.
- **Memory Management**: Proper allocation and deallocation of memory.
- **Algorithm Implementation**: Efficient searching and list management.
- **System Design**: Designing a complete system with multiple interconnected components.

## How to Run
1. **Clone the Repository**:
   ```sh
   https://github.com/HendrX-Static/Library-Management-System
   ```   
2. Compile the program using a C compiler. For example:
   ```bash
   gcc -o library_system main.c
   ```
3. Run the compiled executable:
   ```bash
   ./library_system
   ```

## Future Enhancements
- [ ] Implement file I/O for persistent storage of library data
- [ ] Add user authentication and management
- [ ] Implement more advanced searching algorithms (e.g., binary search for sorted lists)
- [ ] Create a graphical user interface

## Contributing
This project is a personal showcase, but suggestions and feedback are welcome. Please open an issue to discuss potential changes or improvements.

## License
[MIT License](https://opensource.org/licenses/MIT)
