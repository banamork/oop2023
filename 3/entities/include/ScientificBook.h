//
// Created by vanish2 on 19.01.24.
//

#ifndef LIBRARY_SCIENTIFICBOOK_H
#define LIBRARY_SCIENTIFICBOOK_H

#include "Book.h"
#include <vector>

#define MAX_NUMBER_OF_COURSES 3
#define COURSE_NAMES "course_names"

class ScientificBook: public Book{
private:
    std::vector<std::string> courseNames_;

    bool isArrayFieldValid(const json& jsonObject, const std::string& targetFieldName);

public:
    ScientificBook() = default;
    ~ScientificBook() override = default;

    /**
     * @brief Getter for course names
     * @return Course names
     */
    [[nodiscard]] std::vector<std::string> getCourseNames() const;

    /**
     * @brief Setter for course names
     * @param newCourseNames Course names
     */
    void setCourseNames(const std::vector<std::string>& newCourseNames);

    /**
     * @brief Adds new course name
     * @param newCourseName New course name
     */
    void addCourseName(const std::string& newCourseName);

    /**
     * @brief Removes course name
     * @param targetCourseName Target course name
     */
    void removeCourseName(const std::string& targetCourseName);

    /**
     * @brief Changes course name
     * @param oldCourseName old course name
     * @param newCourseName new course name
     */
    void changeCourseNames(const std::string& oldCourseName, const std::string& newCourseName);

    /**
     * @breif Loads information about book
     * @param jsonObject JSON object
     *
     * JSON example:
     * {
     *  "author_info": "Author A. A.",
     *  "book_title": "Book",
     *  "year_and_publisher": "2000 Publisher",
     *  "number_of_copies": 69,
     *  "course_names": ["Course 1", "Course 2"]
     * }
     *
     * @throws std::invalid_argument If gotten JSON object is empty
     * @throws std::invalid_argument If gotten JSON object has not required fields or it is wrong typed
     * @throws std::invalid_argument If there is not any opportunity to set value
     */
    void loadFromJSON(const json& jsonObject) override;

    /**
     * @breis Saves
     * @return JSON
     */
    json beSaved() const override;
};


#endif //LIBRARY_SCIENTIFICBOOK_H
