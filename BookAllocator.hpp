#pragma once

#include "Book.hpp"

/**
 * @class BookAllocator
 * @brief Manages the allocation and deallocation of Book objects.
 *
 * The BookAllocator class manages the dynamic allocation and deallocation of Book objects.
 * It provides methods to resize the internal storage, allocate new Book objects, and deallocate all Book objects.
 */
class BookAllocator
{
private:
    Book **books;         /**< The array of Book pointers. */
    std::size_t capacity; /**< The current capacity of the internal storage. */
    std::size_t sizeNow;  /**< The current size (number of allocated books) in the internal storage. */

    /**
     * @brief Resizes the internal storage to accommodate more books.
     *
     * This function resizes the internal storage by doubling its capacity.
     * It allocates a new temporary array, copies the existing books into it, and then updates the internal storage.
     * If memory allocation fails, it deallocates the temporary array and sets the internal storage pointer to nullptr.
     */
    void resize();

    /**
     * @brief Deallocates all Book objects and frees the internal storage memory.
     *
     * This function iterates through all the allocated books, deletes them, and then frees the memory of the internal storage.
     */
    void deallocate();

public:
    /**
     * @brief Default constructor.
     *
     * The default constructor initializes the BookAllocator object with a default capacity and size of zero.
     * It also allocates memory for the internal storage.
     * If memory allocation fails, it sets the internal storage pointer to nullptr.
     */
    BookAllocator();

    /**
     * @brief Destructor.
     *
     * The destructor deallocates all the Book objects and frees the internal storage memory.
     */
    ~BookAllocator();

    /**
     * @brief Allocates a new Book object.
     * @param author The author of the book.
     * @param title The title of the book.
     * @param genre The genre of the book.
     * @param description The description of the book.
     * @param year The year of publication of the book.
     * @param tags The tags associated with the book.
     * @param rating The rating of the book.
     * @param ID The unique ID of the book.
     * @return A pointer to the newly allocated Book object, or nullptr if allocation fails or if a book with the same ID already exists.
     *
     * This function allocates a new Book object with the provided information.
     * If memory allocation fails or if a book with the same ID already exists in the allocator, it returns nullptr.
     * Otherwise, it adds the new book to the internal storage and returns a pointer to the newly allocated Book object.
     */
    Book *allocate(const string &author, const string &title, const string &genre, const string &description,
                   const unsigned &year, const vector<string> &tags, const double &rating, const unsigned &ID);
};