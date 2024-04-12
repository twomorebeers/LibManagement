#include <stdio.h>
#include <stdlib.h>

#include "libmanage.h"



int login(User *user) {
    FILE *fp = fopen("user_data.csv", "r");
    if (fp == NULL) {
        printf("Error opening user data file.\n");
        return 0;
    }

    char name[50], surname[50], password[50];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter surname: ");
    scanf("%s", surname);
    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(fp, "%s %s %s", user->name, user->surname, user->password) != EOF) {
        if (strcmp(name, user->name) == 0 &&
            strcmp(surname, user->surname) == 0 &&
            strcmp(password, user->password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid credentials.\n");
    return 0;
}

int register_user() {
    FILE *fp = fopen("user_data.csv", "a");
    if (fp == NULL) {
        printf("Error opening user data file.\n");
        return 0;
    }

    char name[50], surname[50], password[50];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter surname: ");
    scanf("%s", surname);
    printf("Enter password: ");
    scanf("%s", password);

    fprintf(fp, "%s %s %s\n", name, surname, password);
    fclose(fp);

    printf("Registration successful!\n");
    return 1;
}

void load_books(Book books[], int *num_books) {
    FILE *fp = fopen("books.csv", "r");
    if (fp == NULL) {
        fp = fopen("books.csv", "w");
        if (fp == NULL) {
            printf("Error creating books file.\n");
            return;
        }
        fclose(fp);
    }

    *num_books = 0;
    while (fscanf(fp, "%[^,],%[^,],%d\n",
                  books[*num_books].title,
                  books[*num_books].author,
                  &books[*num_books].copies_available) == 3) {
        (*num_books)++;
    }

    fclose(fp);
}

void save_books(Book books[], int num_books) {
    FILE *fp = fopen("books.csv", "w");
    if (fp == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    for (int i = 0; i < num_books; i++) {
        fprintf(fp, "%s,%s,%d\n", books[i].title, books[i].author, books[i].copies_available);
    }

    fclose(fp);
}

void load_users(User users[], int *num_users) {
    FILE *fp = fopen("user_data.csv", "r");
    if (fp == NULL) {
        printf("Error opening user data file.\n");
        return;
    }

    *num_users = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  users[*num_users].name,
                  users[*num_users].surname,
                  users[*num_users].password) == 3) {

        (*num_users)++;
    }

    fclose(fp);
}

void save_users(User users[], int num_users) {
    FILE *fp = fopen("user_data.csv", "w");
    if (fp == NULL) {
        printf("Error opening user data file.\n");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%s,%s,%s\n", users[i].name, users[i].surname, users[i].password);
    }

    fclose(fp);
}


void borrow_book(Book books[], int *num_books, User *user) {
    if (user->num_loans >= MAX_LOANS) {
        printf("You cannot borrow more books.\n");
        return;
    }

    char title[50];
    printf("Enter the title of the book: ");
    scanf("%s", title);

    int found = 0;
    for (int i = 0; i < *num_books; i++) {
        if (strcmp(books[i].title, title) == 0) {
            if (books[i].copies_available > 0) {
                books[i].copies_available--;
                user->loans[user->num_loans].book = books[i];
                strcpy(user->loans[user->num_loans].borrower_name, user->name);
                strcpy(user->loans[user->num_loans].borrower_surname, user->surname);
                user->loans[user->num_loans].copies_borrowed = 1;  // Assume borrowing 1 at a time
                user->num_loans++;
                printf("Book borrowed successfully.\n");
            } else {
                printf("Book not available.\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

void return_book(Book books[], int *num_books, User *user) {
    char title[50];
    printf("Enter the title of the book to return: ");
    scanf("%s", title);

    int found = 0;
    for (int i = 0; i < user->num_loans; i++) {
        if (strcmp(user->loans[i].book.title, title) == 0) {
            for (int j = 0; j < *num_books; j++) {
                if (strcmp(books[j].title, title) == 0) {
                    books[j].copies_available++;
                    user->num_loans--;
                    for (int k = i; k < user->num_loans; k++) {
                        user->loans[k] = user->loans[k + 1];
                    }
                    printf("Book returned successfully.\n");
                    found = 1;
                    break;
                }
            }
        }
    }
    if (!found) {
        printf("You have not borrowed this book.\n");
    }
}

void donate_book(Book books[], int *num_books) {
    if (*num_books >= MAX_BOOKS) {
        printf("Library is full.\n");
        return;
    }

    printf("Enter book title: ");
    scanf("%s", books[*num_books].title);
    printf("Enter book author: ");
    scanf("%s", books[*num_books].author);
    printf("Enter number of copies: ");
    scanf("%d", &books[*num_books].copies_available);

    (*num_books)++;
    printf("Book donated successfully.\n");
}

void view_loans(User user) {
    if (user.num_loans == 0) {
        printf("You have no active loans.\n");
        return;
    }

    printf("Your Borrowed Books:\n");
    for (int i = 0; i < user.num_loans; i++) {
        printf("%d. Title: %s, Author: %s\n", i + 1,
               user.loans[i].book.title, user.loans[i].book.author);
    }
}

void search_books(Book books[], int num_books) {
    char search_term[50];
    printf("Enter search term: ");
    scanf("%s", search_term);

    for (int i = 0; i < num_books; i++) {
        if (strstr(books[i].title, search_term) || strstr(books[i].author, search_term)) {
            printf("Title: %s, Author: %s\n", books[i].title, books[i].author);
        }
    }
}

