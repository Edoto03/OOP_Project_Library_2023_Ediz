#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdexcept>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

/**
 * @class Book
 * @brief Represents a book with various attributes.
 */
class Book
{
private:
    string author;       /**< The author of the book. */
    string title;        /**< The title of the book. */
    string genre;        /**< The genre of the book. */
    string description;  /**< The description of the book. */
    unsigned year;       /**< The year of publication of the book. */
    vector<string> tags; /**< The tags associated with the book. */
    double rating;       /**< The rating of the book. */
    unsigned ID;         /**< The unique ID of the book. */

public:
    /**
     * @brief Deleted default constructor.
     * It prevents accidental instantiation of `Book` objects without any initialization.
     */
    Book() = delete;

    /**
     * @brief Constructor for the Book class.
     * @param author The author of the book.
     * @param title The title of the book.
     * @param genre The genre of the book.
     * @param description The description of the book.
     * @param year The year of publication of the book.
     * @param tags The tags associated with the book.
     * @param rating The rating of the book.
     * @param ID The unique ID of the book.
     * @throw std::invalid_argument if any of the input parameters are invalid.
     */
    Book(const string &author, const string &title, const string &genre, const string &description,
         const unsigned &year, const vector<string> &tags, const double &rating, const unsigned &ID);

    /**
     * @brief Prints the compressed information of the book.
     */
    void printCompressedInfo() const;

    /**
     * @brief Prints all the information of the book.
     */
    void printAllInfo() const;

    /**
     * @brief Prints the book information into a file.
     * @param out The output file stream to write the book information.
     */
    void printBookInFile(ofstream &out);

    /**
     * @brief Checks if the book has a specific tag.
     * @param tag The tag to check.
     * @return True if the book has the tag, false otherwise.
     */
    bool hasTag(const string &tag) const;

    /**
     * @brief Get the author of the book.
     * @return The author of the book.
     */
    string getAuthor() const;

    /**
     * @brief Get the title of the book.
     * @return The title of the book.
     */
    string getTitle() const;

    /**
     * @brief Get the year of publication of the book.
     * @return The year of publication of the book.
     */
    unsigned getYear() const;

    /**
     * @brief Get the rating of the book.
     * @return The rating of the book.
     */
    double getRating() const;

    /**
     * @brief Get the unique ID of the book.
     * @return The unique ID of the book.
     */
    unsigned getID() const;
};