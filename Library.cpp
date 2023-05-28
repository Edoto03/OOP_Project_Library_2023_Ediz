#include "Library.hpp"

void Library::deallocate()
{
    delete[] this->libr;
}

void Library::resize()
{
    std::size_t newCapacity = this->capacity * 2;
    Book **temp = nullptr;
    try
    {
        temp = new Book *[newCapacity];
    }
    catch (const std::bad_alloc &e)
    {
        // Memory allocation failed
        // Handle the error as needed
        std ::cout << "Problem while allocating memory!" << std ::endl;
        delete[] temp;  // Deallocate the memory, if partially allocated
        temp = nullptr; // Set the pointer to nullptr
    }

    for (std::size_t i = 0; i < this->cntBooks; ++i)
    {
        temp[i] = this->libr[i];
    }

    delete[] this->libr;
    this->libr = temp;
    this->capacity = newCapacity;
}

Library::Library()
{
    this->cntBooks = 0;
    this->capacity = 4;
    try
    {
        this->libr = new Book *[this->capacity];
    }
    catch (const std::bad_alloc &e)
    {
        std ::cout << "Problem while allocating memory!" << std ::endl;
        this->libr = nullptr;
    }
}

Library::~Library()
{
    this->deallocate();
}

Book &Library::operator[](const size_t index)
{
    assert(index < this->cntBooks && this->libr[index] != nullptr);
    return *this->libr[index];
}
const Book &Library::operator[](const size_t index) const
{
    assert(index < this->cntBooks && this->libr[index] != nullptr);
    return *this->libr[index];
}

size_t Library::size() const
{
    return this->cntBooks;
}

void Library::clear()
{
    this->cntBooks = 0;
    this->capacity = 0;
}

bool Library::empty() const
{
    return this->cntBooks == 0;
}

void Library::addBook(Book &book)
{
    if (this->cntBooks == this->capacity)
        this->resize();
    this->libr[this->cntBooks++] = &book;
}

void Library::removeBook(const string &title)
{
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        if (this->libr[i]->getTitle().compare(title) == 0)
        {
            for (size_t j = i; j < this->cntBooks - 1; j++)
            {
                this->libr[j] = this->libr[j + 1];
            }
            std::cout << "Book with title " << title << " successfully removed." << std ::endl;
            this->cntBooks--;
            return;
        }
    }

    std::cout << "There is no such book." << std ::endl;
}

void Library::swapBooks(Book &book1, Book &book2)
{
    Book temp = book1;
    book1 = book2;
    book2 = temp;
}

void Library::findBookByTitle(const string &title) const
{
    bool flag = false;
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        if (this->libr[i]->getTitle().find(title) != -1)
        {
            this->libr[i]->printAllInfo();
            flag = true;
        }
    }
    if (flag == false)
    {
        std ::cout << "There is no such book." << std ::endl;
    }
    return;
}

void Library::findBookByAuthor(const string &author) const
{
    bool flag = false;
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        if (this->libr[i]->getAuthor().find(author) != -1)
        {
            this->libr[i]->printAllInfo();
            flag = true;
        }
    }
    if (flag == false)
    {
        std ::cout << "There is no such book." << std ::endl;
    }
}

void Library::findBookByTag(const string &tag) const
{
    bool flag = false;
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        if (this->libr[i]->hasTag(tag) == true)
        {
            this->libr[i]->printAllInfo();
            flag = true;
        }
    }
    if (flag == false)
    {
        std ::cout << "There is no such book." << std ::endl;
    }
}

void Library::bookFind(const string &option, const string &optionOfTheOption) const
{

    if (option == "title")
    {
        this->findBookByTitle(optionOfTheOption);
        return;
    }

    if (option == "author")
    {
        this->findBookByAuthor(optionOfTheOption);
        return;
    }

    if (option == "tag")
    {
        this->findBookByTag(optionOfTheOption);
        return;
    }

    std ::cout << "Option is invalid" << std ::endl;
}

void Library::sortByTitle(const bool way)
{
    // descending sorting
    if (way == false)
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getTitle() < this->libr[j]->getTitle())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }

    // ascending sort
    else
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getTitle() > this->libr[j]->getTitle())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }
}

void Library::sortByAuthor(const bool way)
{
    // descending sorting
    if (way == false)
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getAuthor() < this->libr[j]->getAuthor())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }

    // ascending sort
    else
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getAuthor() > this->libr[j]->getAuthor())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }
}

void Library::sortByYear(const bool way)
{
    // descending sorting
    if (way == false)
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getYear() < this->libr[j]->getYear())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }

    // ascending sort
    else
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getYear() > this->libr[j]->getYear())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }
}

void Library::sortByRating(const bool way)
{
    // descending sorting
    if (way == false)
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getRating() < this->libr[j]->getRating())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }

    // ascending sort
    else
    {
        for (size_t i = 0; i < this->cntBooks; i++)
        {
            for (size_t j = i + 1; j < this->cntBooks; j++)
            {
                if (this->libr[i]->getRating() > this->libr[j]->getRating())
                    swapBooks(*this->libr[i], *this->libr[j]);
            }
        }
    }
}

void Library::sort(const string &option, const bool way)
{
    if (option == "title")
    {
        this->sortByTitle(way);
        return;
    }

    if (option == "author")
    {
        this->sortByAuthor(way);
        return;
    }

    if (option == "year")
    {
        this->sortByYear(way);
        return;
    }

    if (option == "rating")
    {
        this->sortByRating(way);
        return;
    }

    std::cout << "Invalid option, please try again." << std ::endl;
}

void Library::printLibraryInFile(ofstream &out)
{
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        this->libr[i]->printBookInFile(out);
    }
}

void Library::booksAll() const
{
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        this->libr[i]->printCompressedInfo();
    }
}

int Library::booksInfo(const unsigned &ID) const
{
    for (size_t i = 0; i < this->cntBooks; i++)
    {
        if (this->libr[i]->getID() == ID)
        {
            this->libr[i]->printAllInfo();
            return 0;
        }
    }

    std ::cout << "There is no such book." << std ::endl;
    return 0;
}