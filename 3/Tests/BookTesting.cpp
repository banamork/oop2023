//
// Created by vanish2 on 18.01.24.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "Book.h"

TEST_CASE("BookConstructor") {
    SECTION("Default") {
        Book b;
        REQUIRE(b.getAuthorInfo().empty());
        REQUIRE(b.getBookTitle().empty());
        REQUIRE(b.getYearAndPublisher().empty());
        REQUIRE(b.getNumberOfCopies() == 0);
    }
}

TEST_CASE("BookMethods") {
    json data = R"({
            "author_info": "Author",
            "book_title": "Title",
            "year_and_publisher": "Year Publisher",
            "number_of_copies": 100
    })"_json;
    Book b;
    SECTION("Setters") {
        b.setAuthorInfo("Author");
        REQUIRE(b.getAuthorInfo() == "Author");

        b.setBookTitle("Title");
        REQUIRE(b.getBookTitle() == "Title");

        b.setYearAndPublisher("Year Publisher");
        REQUIRE(b.getYearAndPublisher() == "Year Publisher");

        b.setNumberOfCopies(10);
        REQUIRE(b.getNumberOfCopies() == 10);
    } SECTION("SettersExceptions") {
        REQUIRE_THROWS(b.setAuthorInfo(""));
        REQUIRE_THROWS(b.setBookTitle(""));
        REQUIRE_THROWS(b.setYearAndPublisher(""));
        REQUIRE_THROWS(b.setNumberOfCopies(0));
    } SECTION("Loading") {
        b.loadFromJSON(data);
        REQUIRE(b.getAuthorInfo() == "Author");
        REQUIRE(b.getBookTitle() == "Title");
        REQUIRE(b.getYearAndPublisher() == "Year Publisher");
        REQUIRE(b.getNumberOfCopies() == 100);
    } SECTION("Saving") {
        b.loadFromJSON(data);
        auto save = b.beSaved();
        Book bSave;
        bSave.loadFromJSON(save);
        REQUIRE(b.getAuthorInfo() == bSave.getAuthorInfo());
        REQUIRE(b.getBookTitle() == bSave.getBookTitle());
        REQUIRE(b.getYearAndPublisher() == bSave.getYearAndPublisher());
        REQUIRE(b.getNumberOfCopies() == bSave.getNumberOfCopies());
    }
}