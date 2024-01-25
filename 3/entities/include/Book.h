//
// Created by vanish2 on 18.01.24.
//

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define AUTHOR_INFO "author_info"
#define BOOK_TITLE "book_title"
#define YEAR_AND_PUBLISHER "year_and_publisher"
#define NUMBER_OF_COPIES "number_of_copies"

class Book {
protected:
    /// Information about author
    std::string authorInfo_;
    /// Book title
    std::string bookTitle_;
    /// Year and publisher
    std::string yearAndPublisher_;
    /// Number of copies
    int numberOfCopies_{};

    /**
     * @biref Checks if target field in JSON object is valid
     * @param jsonObject JSON object
     * @param targetFieldName Target field name
     * @return True if is valid else returns false
     */
    bool isStringFieldValid(const json& jsonObject, const std::string& targetFieldName);

    /**
     * @brief Checks if target field in JSON object is valid
     * @param jsonObject JSON object
     * @param targetFieldName Target field name
     * @return True if is valid else returns false
     */
    bool isNumberFieldValid(const json& jsonObject, const std::string& targetFieldName);

public:
    Book() = default;
    virtual ~Book() = default;

    /**
     * @brief Getter for information about author
     * @return Information about author
     */
    [[nodiscard]] std::string getAuthorInfo() const;

    /**
     * @brief Getter for book title
     * @return Book title
     */
    [[nodiscard]] std::string getBookTitle() const;

    /**
     * @brief Getter for year and publisher
     * @return Year and publisher
     */
    [[nodiscard]] std::string getYearAndPublisher() const;

    /**
     * @brief Getter for number of copies
     * @return Number of copies
     */
    [[nodiscard]] int getNumberOfCopies() const;

    /**
     * @brief Setter for author information
     * @param newAuthorInfo Future author information (must be not an empty string)
     * @throws std::invalid_argument If gotten string data is empty
     */
    void setAuthorInfo(const std::string& newAuthorInfo);

    /**
     * @breif Setter for book title
     * @param newBookTitle Future book title (must ne not an empty string)
     * @throws std::invalid_argument If gotten string data is empty
     */
    void setBookTitle(const std::string& newBookTitle);

    /**
     * @brief Setter for year and publisher
     * @param newYearAndPublisher Future year and publisher (must be not an empty string)
     * @throws std::invalid_argument If gotten string data is empty
     */
    void setYearAndPublisher(const std::string& newYearAndPublisher);

    /**
     * @brief Setter for number of copies
     * @param newNumberOfCopies Future number of copies (must be more than 0)
     * @throws std::invalid_argument If gotten integer is less than 1
     */
    void setNumberOfCopies(int newNumberOfCopies);

    /**
     * @brief Loads information about author
     * @param jsonObject JSON object
     *
     * JSON example:
     * {
     *  "author_info": "Author A. A.",
     *  "book_title": "Book",
     *  "year_and_publisher": "2000 Publisher",
     *  "number_of_copies": 69
     * }
     *
     * @throws std::invalid_argument If gotten JSON object is empty
     * @throws std::invalid_argument If gotten JSON object has not required fields or it is wrong typed
     * @throws std::invalid_argument If there is not any opportunity to set value
     */
    virtual void loadFromJSON(const json& jsonObject);

    /**
     * @brief Saves information into JSON object
     * @return JSON object
     */
    [[nodiscard]] virtual json beSaved() const;
};


#endif //LIBRARY_BOOK_H
