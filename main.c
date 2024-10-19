#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

// Structure for a user in the waiting list
typedef struct WaitingUser {
    int userId;
    struct WaitingUser* next;
} WaitingUser;

// Structure for a queue (waiting list)
typedef struct {
    WaitingUser* front;
    WaitingUser* rear;
} Queue;

// Structure for a book
typedef struct Book {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int available;
    Queue* waitingList;  // Pointer to a dynamically allocated queue
    struct Book* next;
} Book;

Book* bookList = NULL;
Book* borrowedBooks = NULL;

// Function prototypes
void addBook();
void displayBooks();
void searchBook();
void borrowBook();
void returnBook();
void displayWaitingLists();
void displayBorrowedBooks();
void enqueue(Queue* q, int userId);
int dequeue(Queue* q);
void addToBorrowedList(Book* book);
void removeFromBorrowedList(int id);

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Borrow a book\n");
        printf("5. Return a book\n");
        printf("6. Display waiting lists\n");
        printf("7. Display borrowed books\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: borrowBook(); break;
            case 5: returnBook(); break;
            case 6: displayWaitingLists(); break;
            case 7: displayBorrowedBooks(); break;
            case 8:
                printf("Thank you for using the Library Management System!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Memory allocation failed. Cannot add book.\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &newBook->id);
    printf("Enter book title: ");
    scanf(" %[^\n]", newBook->title);
    printf("Enter book author: ");
    scanf(" %[^\n]", newBook->author);
    newBook->available = 1;
    
    // Dynamically allocate the waiting list queue
    newBook->waitingList = (Queue*)malloc(sizeof(Queue));
    if (newBook->waitingList == NULL) {
        printf("Memory allocation failed for waiting list. Cannot add book.\n");
        free(newBook);
        return;
    }
    newBook->waitingList->front = newBook->waitingList->rear = NULL;
    
    newBook->next = NULL;

    if (bookList == NULL) {
        bookList = newBook;
    } else {
        Book* current = bookList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newBook;
    }

    printf("Book added successfully!\n");
}

void displayBooks() {
    if (bookList == NULL) {
        printf("No books in the library.\n");
        return;
    }

    printf("Books in the library:\n");
    printf("ID\tTitle\t\t\tAuthor\t\t\tAvailability\n");
    Book* current = bookList;
    while (current != NULL) {
        printf("%d\t%-20s\t%-20s\t%s\n", current->id, current->title, current->author,
               current->available ? "Available" : "Borrowed");
        current = current->next;
    }
}

void searchBook() {
    char searchTitle[MAX_TITLE_LENGTH];
    printf("Enter the title of the book to search: ");
    scanf(" %[^\n]", searchTitle);

    Book* current = bookList;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->title, searchTitle) == 0) {
            printf("Book found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nAvailability: %s\n",
                   current->id, current->title, current->author,
                   current->available ? "Available" : "Borrowed");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Book not found.\n");
    }
}

void borrowBook() {
    int id, userId;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    printf("Enter your user ID: ");
    scanf("%d", &userId);

    Book* current = bookList;
    while (current != NULL) {
        if (current->id == id) {
            if (current->available) {
                current->available = 0;
                addToBorrowedList(current);
                printf("Book borrowed successfully!\n");
            } else {
                enqueue(current->waitingList, userId);
                printf("Book is not available. You've been added to the waiting list.\n");
            }
            return;
        }
        current = current->next;
    }
    printf("Book not found.\n");
}

void returnBook() {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    Book* current = bookList;
    while (current != NULL) {
        if (current->id == id) {
            if (!current->available) {
                current->available = 1;
                removeFromBorrowedList(id);
                printf("Book returned successfully!\n");

                if (current->waitingList->front != NULL) {
                    int nextUserId = dequeue(current->waitingList);
                    printf("User %d can now borrow the book '%s'.\n", nextUserId, current->title);
                    current->available = 0;
                    addToBorrowedList(current);
                }
            } else {
                printf("This book is not borrowed.\n");
            }
            return;
        }
        current = current->next;
    }
    printf("Book not found.\n");
}

void displayWaitingLists() {
    int found = 0;
    Book* current = bookList;
    while (current != NULL) {
        if (current->waitingList->front != NULL) {
            found = 1;
            printf("Waiting list for book '%s' (ID: %d):\n", current->title, current->id);
            WaitingUser* waitingUser = current->waitingList->front;
            while (waitingUser != NULL) {
                printf("User ID: %d\n", waitingUser->userId);
                waitingUser = waitingUser->next;
            }
            printf("\n");
        }
        current = current->next;
    }

    if (!found) {
        printf("No waiting lists found.\n");
    }
}

void displayBorrowedBooks() {
    if (borrowedBooks == NULL) {
        printf("No books are currently borrowed.\n");
        return;
    }

    printf("Borrowed books:\n");
    Book* current = borrowedBooks;
    while (current != NULL) {
        printf("ID: %d, Title: %s, Author: %s\n", current->id, current->title, current->author);
        current = current->next;
    }
}

void enqueue(Queue* q, int userId) {
    WaitingUser* newUser = (WaitingUser*)malloc(sizeof(WaitingUser));
    if (newUser == NULL) {
        printf("Memory allocation failed. Cannot add to waiting list.\n");
        return;
    }
    newUser->userId = userId;
    newUser->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newUser;
    } else {
        q->rear->next = newUser;
        q->rear = newUser;
    }
}

int dequeue(Queue* q) {
    if (q->front == NULL) {
        return -1;  // Error: empty queue
    }

    WaitingUser* temp = q->front;
    int userId = temp->userId;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return userId;
}

void addToBorrowedList(Book* book) {
    Book* newNode = (Book*)malloc(sizeof(Book));
    if (newNode == NULL) {
        printf("Memory allocation failed. Cannot add to borrowed list.\n");
        return;
    }
    *newNode = *book;
    newNode->next = NULL;

    if (borrowedBooks == NULL) {
        borrowedBooks = newNode;
    } else {
        Book* current = borrowedBooks;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void removeFromBorrowedList(int id) {
    Book* current = borrowedBooks;
    Book* prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return;

    if (prev == NULL) {
        borrowedBooks = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}