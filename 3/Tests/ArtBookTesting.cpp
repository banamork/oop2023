//
// Created by vanish2 on 18.01.24.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "ArtBook.h"

TEST_CASE("ArtBookConstructor") {
    SECTION("Default") {
        ArtBook b;
        REQUIRE(b.getTheme().empty());
    }
}

TEST_CASE("ArtBookMethods") {
    json data = R"({
            "author_info": "Author",
            "book_title": "Title",
            "year_and_publisher": "Year Publisher",
            "theme": "theme",
            "number_of_copies": 100
    })"_json;
    ArtBook b;
    SECTION("Setters") {
        b.setTheme("theme");
        REQUIRE(b.getTheme() == "theme");
    } SECTION("Loading"){
        b.loadFromJSON(data);
        REQUIRE(b.getTheme() == "theme");
    } SECTION("Saving") {
        b.loadFromJSON(data);
        json save = b.beSaved();
        ArtBook bSave;
        bSave.loadFromJSON(save);
        REQUIRE(b.getTheme() == bSave.getTheme());
    }
}