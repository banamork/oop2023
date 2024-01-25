//
// Created by vanish2 on 21.01.24.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "ScientificBook.h"

TEST_CASE("ScientificBookTesting"){
    SECTION("Default") {
        ScientificBook b;
        REQUIRE(b.getCourseNames().empty());
    }
}

TEST_CASE("ScientificBookMethods") {
    SECTION("Setters") {
        ScientificBook b;
        std::vector<std::string> courseNames = {"A", "B", "C"};
        b.setCourseNames(courseNames);
        REQUIRE(b.getCourseNames() == courseNames);
    } SECTION("SettersExceptions") {
        ScientificBook b;
        REQUIRE_THROWS(b.setCourseNames({}));
        REQUIRE_THROWS(b.setCourseNames({}));
    } SECTION("Adding") {
        ScientificBook b;
        std::vector<std::string> courseNames = {"A", "B"};
        b.setCourseNames(courseNames);
        b.addCourseName("C");
        courseNames.emplace_back("C");
        REQUIRE(b.getCourseNames() == courseNames);
   } SECTION("AddingExceptions") {
        ScientificBook b;
        REQUIRE_THROWS(b.addCourseName(""));
        std::vector<std::string> courseNames = {"A", "B", "C"};
        b.setCourseNames(courseNames);
        REQUIRE_THROWS(b.addCourseName("D"));
        courseNames = {"A"};
        b.setCourseNames(courseNames);
        REQUIRE_THROWS(b.addCourseName("A"));
   } SECTION("Removing") {
        ScientificBook b;
        std::vector<std::string> courseNames = {"A", "B", "C"};
        b.setCourseNames(courseNames);
        courseNames = {"A", "B"};
        b.removeCourseName("C");
        REQUIRE(b.getCourseNames() == courseNames);
   } SECTION("RemovingExceptions") {
        ScientificBook b;
        REQUIRE_THROWS(b.removeCourseName(""));
        REQUIRE_THROWS(b.removeCourseName("A"));
        std::vector<std::string> courseNames = {"A", "B"};
        b.setCourseNames(courseNames);
        REQUIRE_THROWS(b.removeCourseName("C"));
   } SECTION("Changing") {
        ScientificBook b;
        std::vector<std::string> courseNames = {"A", "B"};
        b.setCourseNames(courseNames);
        b.changeCourseNames("A", "E");
        courseNames = {"E", "B"};
        REQUIRE(b.getCourseNames() == courseNames);
   } SECTION("ChangingExceptions") {
        ScientificBook b;
        REQUIRE_THROWS(b.changeCourseNames("", "A"));
        REQUIRE_THROWS(b.changeCourseNames("A", ""));
        std::vector<std::string> courseNames = {"A", "B"};
        b.setCourseNames(courseNames);
        REQUIRE_THROWS(b.changeCourseNames("F", "E"));
   }
}