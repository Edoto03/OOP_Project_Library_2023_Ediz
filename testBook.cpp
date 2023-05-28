#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Book.hpp"

TEST_CASE ("Test constructor with parameters")
{
    Book book("Ivan Vazov", "Pod Igoto", "Historical novel", "A romance of Bulgarian Liberty", 1894, {"war", "liberty"}, 5, 1000);

    REQUIRE(book.getAuthor() == "Ivan Vazov");
    REQUIRE(book.getTitle() == "Pod Igoto");
    REQUIRE(book.getYear() == 1894);
    REQUIRE(book.getRating() == 5);
    REQUIRE(book.getID() == 1000); 
}