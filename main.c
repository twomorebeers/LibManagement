#include <stdio.h>
#include <stdlib.h>

#include "libmanage.h"

int main() {
    Book books[MAX_BOOKS];
    int num_books = 0;
    User users[MAX_USERS];
    int num_users = 0;

    load_books(books, &num_books);
    load_users(users, &num_users);

    int choice, inner_choice;
    do {
        printf("\n---Library Management System---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Login
                User user;
                if (login(&user)) {
                    printf("Login successful!\n");

                    do {
                        printf("\n--User Menu--\n");
                        printf("1. Borrow Book\n");
                        printf("2. Return Book\n");
                        printf("3. Donate Book\n");
                        printf("4. View Loans\n");
                        printf("5. Search Books\n");
                        printf("6. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &inner_choice);

                        switch (inner_choice) {
                            case 1: borrow_book(books, &num_books, &user); break;
                            case 2: return_book(books, &num_books, &user); break;
                            case 3: donate_book(books, &num_books); break;
                            case 4: view_loans(user); break;
                            case 5: search_books(books, num_books); break;
                            case 6: printf("Logging out...\n"); break;
                            default: printf("Invalid choice\n");
                        }
                    } while (inner_choice != 6); // Logout condition
                } else {
                    printf("Login failed.\n");
                }
                break;
            }
            case 2: { // Registration
                if (register_user()) {
                    printf("Registration successful!\n");
                } else {
                    printf("Registration failed.\n");
                }
                break;
            }
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    save_books(books, num_books);
    save_users(users, num_users);

    return 0;
}
