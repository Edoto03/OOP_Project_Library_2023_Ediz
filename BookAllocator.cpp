#include "BookAllocator.hpp"

void BookAllocator::resize()
{
    std::size_t newCapacity = this->capacity * 2;
    Book **temp = nullptr;
    try
    {
        temp = new Book *[newCapacity];
    }
    catch (const std::bad_alloc &e)
    {
        std ::cout << "Problem while allocating memory!" << std ::endl;
        delete[] temp;
        temp = nullptr;
    }

    for (std::size_t i = 0; i < this->sizeNow; ++i)
    {
        temp[i] = this->books[i];
    }

    delete[] this->books;
    this->books = temp;
    this->capacity = newCapacity;
}

void BookAllocator::deallocate()
{
    for (std::size_t i = 0; i < this->sizeNow; ++i)
    {
        delete this->books[i];
    }

    delete[] this->books;
}

BookAllocator::BookAllocator()
{
    this->capacity = 4;
    this->sizeNow = 0;

    try
    {
        this->books = new Book *[this->capacity];
    }
    catch (const std::bad_alloc &e)
    {
        std ::cout << "Problem while allocating memory!" << std ::endl;
        this->books = nullptr;
    }
}

BookAllocator::~BookAllocator()
{
    this->deallocate();
}

Book *BookAllocator::allocate(const string &author, const string &title, const string &genre, const string &description,
                              const unsigned &year, const vector<string> &tags, const double &rating, const unsigned &ID)
{

    Book *newBook = nullptr;

    try
    {
        newBook = new Book(author, title, genre, description, year, tags, rating, ID);
    }
    catch (const std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }

    for (size_t i = 0; i < this->sizeNow; i++)
    {
        if (this->books[i]->getID() == ID)
        {
            throw std::invalid_argument("There is a book with that ID already");
        }
    }

    if (this->sizeNow == this->capacity)
    {
        this->resize();
    }

    this->books[this->sizeNow] = newBook;
    this->sizeNow++;
    return newBook;
}