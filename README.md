# CLibrarySystem
A library database system written in C.

## Usage
On Linux or WSL, after compilation, the program can be run by inputting:
- "./addBook \<TITLE OF BOOK\>"
- "./findBook \<TITLE OF BOOK\>"
- "./removeBook \<TITLE OF BOOK\>"

Both findBook and removeBook ignore case. However, they both require correct spellling.

## Parts
This program is split into 3 parts:
- addBook
- findBook
- removeBook

## How to compile
On Linux or WSL, run "make all" to compile all of the programs.

Or run "make addBook", "make findBook", and "make removeBook" to compile each individually.

## How it works
The library "database" is simply a text file titled "books.txt." Each book is stored on a
different line.

addBook simply writes to this database using fprintf.

findBook iterates through the whole database to find the corresponding book. It skips past
any book that is a different length than the search query to be optimal.

removeBook similarly iterates through the database to find the book, writes to a temporary
file each line except the line we're trying to delete, replaces the old "books.txt"
with the temporary file, and renames the temporary file "books.txt."
