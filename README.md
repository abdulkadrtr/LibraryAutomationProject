# LibraryAutomationProject
All functions of a library automation system are implemented in the C language, while CSV files are used as the database. 
This system allows for efficient management of library operations and resources, such as books, borrowers, and transactions.


## About the project

In this project, a library automation system has been implemented using the C language, with heavy use of linked lists, 
dynamic memory management, and file I/O operations. The project's database is comprised of CSV files located within the project folder.

You can find detailed descriptions of the project functions, such as adding, deleting, and updating records for students, authors, and books, as well as processes for students to borrow and return books, penalizing students for late book returns, and querying the status of books. Additionally, parallel processes are implemented in the database to update all records when a new book is added. For example, if the author of a new book is not already in the database, they will be added as a new author, allowing users to view all books written by a particular author or all authors who have contributed to a specific book. To explore these functions and many more, please refer to the `doc.pdf` document.

## How does it work

Compile and run the `main.c` file located in the project folder.

## Docs

You can review the `doc.pdf` document in the project file for further details about the project functions. This document provides detailed descriptions of the project functions.


