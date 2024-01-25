//
// Created by vanish2 on 18.01.24.
//

#ifndef LIBRARY_ARTBOOK_H
#define LIBRARY_ARTBOOK_H

#include "Book.h"

#define THEME "theme"

class ArtBook: public Book{
private:
    std::string theme_;

public:
    ArtBook() = default;
    ~ArtBook() override = default;

    /**
     * @brief Getter for theme
     * @return Theme of book
     */
    [[nodiscard]] std::string getTheme() const;

    /**
     * @brief Setter for theme
     * @param newTheme Future theme (must be not an empty string)
     * @throws std::invalid_argument If gotten string data is empty
     */
    void setTheme(const std::string& newTheme);

    /**
     * @breif Loads information about book
     * @param jsonObject JSON object
     *
     * JSON example:
     * {
     *  "author_info": "Author A. A.",
     *  "book_title": "Book",
     *  "year_and_publisher": "2000 Publisher",
     *  "number_of_copies": 69
     *  "theme": "Theme"
     * }
     *
     * @throws std::invalid_argument If gotten JSON object is empty
     * @throws std::invalid_argument If gotten JSON object has not required fields or it is wrong typed
     * @throws std::invalid_argument If there is not any opportunity to set value
     */
    void loadFromJSON(const json& jsonObject) override;

    /**
     * @breif Saves information about book into JSON object
     * @return JSON object
     */
    [[nodiscard]] json beSaved() const override;
};


#endif //LIBRARY_ARTBOOK_H
