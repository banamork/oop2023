//
// Created by vanish2 on 19.01.24.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "EducationalBook.h"

TEST_CASE("EducationalBookConstructor") {
    SECTION("Default") {
        EducationalBook b;
        REQUIRE(b.getCourseName().empty());
        REQUIRE(b.getGroupIndexes().empty());
    }
}

TEST_CASE("EducationalBookMethods") {
    SECTION("Setters") {
        EducationalBook b;
        b.setCourseName("Course name");
        REQUIRE(b.getCourseName() == "Course name");
        std::vector<int> groupIndexes = {1,2,3,4};
        b.setGroupIndexes(groupIndexes);
        REQUIRE(b.getGroupIndexes() == groupIndexes);
    } SECTION("SettersExceptions") {
        EducationalBook b;
        REQUIRE_THROWS(b.setCourseName(""));
        REQUIRE_THROWS(b.setGroupIndexes({}));
    } SECTION("Loading") {
        json data = R"({
            "author_info": "Author",
            "book_title": "Title",
            "year_and_publisher": "Year Publisher",
            "number_of_copies": 100,
            "course_name": "Course name",
            "group_indexes": [1,2,3,4]
        })"_json;
       EducationalBook b;
       b.loadFromJSON(data);
        REQUIRE(b.getCourseName() == "Course name");
        std::vector<int> groupIndexes = {1,2,3,4};
        REQUIRE(b.getGroupIndexes() == groupIndexes);
    } SECTION("Saving") {
        json data = R"({
            "author_info": "Author",
            "book_title": "Title",
            "year_and_publisher": "Year Publisher",
            "number_of_copies": 100,
            "course_name": "Course name",
            "group_indexes": [1,2,3,4]
        })"_json;
        EducationalBook b;
        b.loadFromJSON(data);
        json save = b.beSaved();
        EducationalBook bSave;
        bSave.loadFromJSON(save);
        REQUIRE(b.getCourseName() == bSave.getCourseName());
        REQUIRE(b.getGroupIndexes() == bSave.getGroupIndexes());
    }
}