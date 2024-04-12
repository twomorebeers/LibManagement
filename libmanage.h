#ifndef LIBMANAGE_H
#define LIBMANAGE_H

#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_LOANS 5
#define MAX_USERS 100 // Add for user management

typedef struct {
    char title[50];
    char author[50];
    int copies_available;
} Book;

typedef struct {
    char borrower_name[50];
    char borrower_surname[50];
    Book book;
    int copies_borrowed;
} Loan;

typedef struct {
    char name[50];
    char surname[50];
    char password[50];
    Loan loans[MAX_LOANS];
    int num_loans;
} User;

// Function prototypes
int login(User *user);
int register_user();
void load_books(Book books[], int *num_books);
void save_books(Book books[], int num_books);
void load_users(User users[], int *num_users);
void save_users(User users[], int num_users);
void borrow_book(Book books[], int *num_books, User *user);
void return_book(Book books[], int *num_books, User *user);
void donate_book(Book books[], int *num_books);
void view_loans(User user);
void search_books(Book books[], int num_books);

#endif
