#pragma once

#include "Book.hpp"
#include <cassert>

/**
 * @class Library
 * @brief Represents a library of books.
 */
class Library
{
private:
    Book **libr;     /**< Array of Book pointers */
    size_t cntBooks; /**< Count of books in the library */
    size_t capacity; /**< Capacity of the library */

    /**
     * @brief Deallocates memory for the library.
     */
    void deallocate();

    /**
     * @brief Resizes the library by doubling its capacity.
     */
    void resize();

public:
    /**
     * @brief Constructs a Library object with default capacity.
     */
    Library();

    /**
     * @brief Destroys the Library object and deallocates memory.
     */
    ~Library();

    /**
     * @brief Overloads the indexing operator for accessing books in the library.
     * @param index The index of the book.
     * @return Reference to the book.
     */
    Book &operator[](const size_t index);

    /**
     * @brief Overloads the indexing operator for accessing books in the library (const version).
     * @param index The index of the book.
     * @return Const reference to the book.
     */
    const Book &operator[](const size_t index) const;

    /**
     * @brief Returns the size of the library.
     * @return The number of books in the library.
     */
    size_t size() const;

    /**
     * @brief Clears the library by setting the book count and capacity to zero.
     */
    void clear();

    /**
     * @brief Checks if the library is empty.
     * @return True if the library is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Adds a book to the library.
     * @param book The book to be added.
     */
    void addBook(Book &book);

    /**
     * @brief Removes a book from the library by title.
     * @param title The title of the book to be removed.
     */
    void removeBook(const string &title);

    /**
     * @brief Swaps the positions of two books in the library.
     * @param book1 The first book.
     * @param book2 The second book.
     */
    void swapBooks(Book &book1, Book &book2);

    /**
     * @brief Finds books in the library by title.
     * @param title The title to search for.
     */
    void findBookByTitle(const string &title) const;

    /**
     * @brief Finds books in the library by author.
     * @param author The author to search for.
     */
    void findBookByAuthor(const string &author) const;

    /**
     * @brief Finds books in the library by tag.
     * @param tag The tag to search for.
     */
    void findBookByTag(const string &tag) const;

    /**
     * @brief Finds books in the library based on a given option.
     * @param option The search option ("title", "author", or "tag").
     * @param optionOfTheOption The option value to search for.
     */
    void bookFind(const string &option, const string &optionOfTheOption) const;

    /**
     * @brief Sorts the books in the library by title.
     *
     * @param way Boolean value indicating the sorting order. False for descending, true for ascending.
     */
    void sortByTitle(const bool way);

    /**
     * @brief Sorts the books in the library by author.
     *
     * @param way Boolean value indicating the sorting order. False for descending, true for ascending.
     */
    void sortByAuthor(const bool way);

    /**
     * @brief Sorts the books in the library by year.
     *
     * @param way Boolean value indicating the sorting order. False for descending, true for ascending.
     */
    void sortByYear(const bool way);

    /**
     * @brief Sorts the books in the library by rating.
     *
     * @param way Boolean value indicating the sorting order. False for descending, true for ascending.
     */
    void sortByRating(const bool way);

    /**
     * @brief Sorts the books in the library by title, author, year, or rating.
     * @param option The sorting option ("title", "author", "year", or "rating").
     * @param way The sorting order (true for ascending, false for descending).
     */
    void sort(const string &option, const bool way);

    /**
     * @brief Prints the library to a file.
     * @param out The output file stream.
     */
    void printLibraryInFile(ofstream &out);

    /**
     * @brief Prints all the books in the library.
     */
    void booksAll() const;

    /**
     * @brief Prints detailed information about a specific book.
     * @param ID The ID of the book.
     * @return 0 if the book is found, otherwise -1.
     */
    int booksInfo(const unsigned &ID) const;
};