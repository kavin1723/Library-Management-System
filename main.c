#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE 50
#define MAX_AUTHOR 50

struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isAvailable;
};

struct Book library[MAX_BOOKS];
int bookCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }

    struct Book newBook;
    newBook.id = bookCount + 1;
    newBook.isAvailable = 1;

    printf("Enter book title: ");
    getchar(); // Clear buffer
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline

    printf("Enter author name: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove newline

    library[bookCount] = newBook;
    bookCount++;
    printf("Book added successfully!\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books in library!\n");
        return;
    }

    printf("\nLibrary Books:\n");
    printf("ID\tTitle\t\tAuthor\t\tStatus\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].isAvailable ? "Available" : "Borrowed");
    }
}

void searchBook() {
    char searchTitle[MAX_TITLE];
    printf("Enter book title to search: ");
    getchar(); // Clear buffer
    fgets(searchTitle, MAX_TITLE, stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0; // Remove newline

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, searchTitle) != NULL) {
            printf("Book found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStatus: %s\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].isAvailable ? "Available" : "Borrowed");
            found = 1;
        }
    }
    if (!found) {
        printf("Book not found!\n");
    }
}

void borrowBook() {
    int bookId;
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bookId) {
            if (library[i].isAvailable) {
                library[i].isAvailable = 0;
                printf("Book borrowed successfully!\n");
            } else {
                printf("Book is already borrowed!\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}

void returnBook() {
    int bookId;
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == bookId) {
            if (!library[i].isAvailable) {
                library[i].isAvailable = 1;
                printf("Book returned successfully!\n");
            } else {
                printf("Book is already in library!\n");
            }
            return;
        }
    }
    printf("Book not found!\n");
}

void menu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Display All Books\n");
    printf("3. Search Book\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                borrowBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                printf("Thank you for using Library Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}