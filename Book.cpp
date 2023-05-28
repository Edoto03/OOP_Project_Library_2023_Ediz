#include "Book.hpp"

Book::Book(const string &author, const string &title, const string &genre, const string &description,
           const unsigned &year, const vector<string> &tags, const double &rating, const unsigned &ID)
{
    if (author.empty())
    {
        throw std::invalid_argument("Invalid author.");
    }

    if (title.empty())
    {
        throw std::invalid_argument("Invalid title.");
    }

    if (genre.empty())
    {
        throw std::invalid_argument("Invalid genre.");
    }

    if (description.empty())
    {
        throw std::invalid_argument("Invalid description.");
    }

    if (year <= 0 || year > 2023)
    {
        throw std::invalid_argument("Invalid year.");
    }

    if (tags.empty())
    {
        throw std::invalid_argument("Invalid tags.");
    }

    if (rating < 0 || rating > 10)
    {
        throw std::invalid_argument("Invalid rating.");
    }

    if (ID < 0)
    {
        throw std::invalid_argument("Invalid ID.");
    }

    this->author = author;
    this->title = title;
    this->genre = genre;
    this->description = description;
    this->year = year;
    this->tags = tags;
    this->rating = rating;
    this->ID = ID;
}

void Book::printCompressedInfo() const
{
    std ::cout << "Title: " << this->title << std ::endl;
    std ::cout << "Author: " << this->author << std ::endl;
    std ::cout << "Genre: " << this->genre << std ::endl;
    std ::cout << "ID: " << this->ID << std ::endl;
}

void Book::printAllInfo() const
{
    std ::cout << "Title: " << this->title << std ::endl;
    std ::cout << "Author: " << this->author << std ::endl;
    std ::cout << "Genre: " << this->genre << std ::endl;
    std ::cout << "Description: " << this->description << std ::endl;
    std ::cout << "Year: " << this->year << std ::endl;
    std ::cout << "Tags: ";
    std ::cout << this->tags[0];
    for (int i = 1; i < this->tags.size(); i++)
    {
        std ::cout << ", " << this->tags[i];
    }
    std ::cout << std ::endl;
    std ::cout << "Rating: " << this->rating << std ::endl;
    std ::cout << "ID: " << this->ID << std ::endl;
}

void Book::printBookInFile(ofstream &out)
{
    out << this->author << "|" << this->title << "|" << this->genre << "|" << this->description << "|" << this->year << "|";
    for (int i = 0; i < this->tags.size(); i++)
    {
        out << this->tags[i];
        if (i != (this->tags.size() - 1))
            out << ",";
    }
    out << "|" << this->rating << "|" << this->ID << std ::endl;
}

bool Book::hasTag(const string &tag) const
{
    for (int i = 0; i < this->tags.size(); i++)
    {
        if (tag == this->tags[i])
            return true;
    }

    return false;
}

string Book::getAuthor() const
{
    return this->author;
}

string Book::getTitle() const
{
    return this->title;
}

unsigned Book::getYear() const
{
    return this->year;
}

double Book::getRating() const
{
    return this->rating;
}

unsigned Book::getID() const
{
    return this->ID;
}
