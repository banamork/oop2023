//
// Created by vanish2 on 19.01.24.
//

#ifndef LIBRARY_EDUCATIONALBOOK_H
#define LIBRARY_EDUCATIONALBOOK_H

#include "Book.h"
#include <vector>

#define MAX_NUMBER_OF_GROUP_INDEXES 8
#define COURSE_NAME "course_name"
#define GROUP_INDEXES "group_indexes"

class EducationalBook: public Book {
private:
    std::string courseName_;
    std::vector<int> groupIndexes_;

    bool isArrayFieldValid(const json& jsonObject, const std::string& targetFieldName);

public:
    EducationalBook() = default;
    ~EducationalBook() override = default;

    /**
     * @brief Getter for course name
     * @return Course name
     */
    [[nodiscard]] std::string getCourseName() const;

    /**
     * @brief Setter for course name
     * @param newCourseName Future course name (must be not an empty string)
     * @throws std::invalid_argument If gotten string data is empty
     */
    void setCourseName(const std::string& newCourseName);

    /**
     * @breif Getter for group indexes
     * @return Group indexes
     */
    [[nodiscard]] std::vector<int> getGroupIndexes() const;

    /**
     * @brief Setter for group indexes
     * @param newGroupIndexes Future group indexes
     * @throws std::invalid_argument If gotten data is empty
     * @throws std::invalid_argument If it is over limit
     */
    void setGroupIndexes(const std::vector<int>& newGroupIndexes);

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
    *  "course_name": "Course name",
    *  "group_indexes": [1,2,3,4,5]
    * }
    *
    * @throws std::invalid_argument If gotten JSON object is empty
    * @throws std::invalid_argument If gotten JSON object has not required fields or it is wrong typed
    * @throws std::invalid_argument If there is not any opportunity to set value
    */
    void loadFromJSON(const json& jsonObject) override;

    /**
     * @brief Saves information into JSON object
     * @return JSON object
     */
    [[nodiscard]] json beSaved() const override;
};


#endif //LIBRARY_EDUCATIONALBOOK_H
