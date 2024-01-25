//
// Created by vanish2 on 18.01.24.
//

#include "ArtBook.h"

std::string ArtBook::getTheme() const { return this->theme_; }

void ArtBook::setTheme(const std::string &newTheme) {
    if(newTheme.empty())
        throw std::invalid_argument("Gotten string can not be set as theme of art book, has not any data inside");
    this->theme_ = newTheme;
}

void ArtBook::loadFromJSON(const json &jsonObject) {
    auto stateBeforeLoading = *this;
    try {
        Book::loadFromJSON(jsonObject);
        if (!isStringFieldValid(jsonObject, THEME))
            throw std::invalid_argument("Gotten JSON object does not collects theme, or field wrong typed");
        this->setTheme(jsonObject[THEME].get<std::string>());
    } catch (...) {
        *this = stateBeforeLoading;
        throw ;
    }
}

json ArtBook::beSaved() const {
    json saveObject = Book::beSaved();
    saveObject[THEME] = this->theme_;
    return saveObject;
}
