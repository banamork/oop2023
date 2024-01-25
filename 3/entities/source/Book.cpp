//
// Created by vanish2 on 18.01.24.
//

#include "../include/Book.h"

bool Book::isStringFieldValid(const json &jsonObject, const std::string &targetFieldName) {
    bool result;
    auto fieldIterator = jsonObject.find(targetFieldName);
    if(fieldIterator != jsonObject.end()) {
        if(fieldIterator->is_string()) {
            result = true;
        }
    }
    return result;
}

bool Book::isNumberFieldValid(const json &jsonObject, const std::string &targetFieldName) {
    bool result;
    auto fieldIterator = jsonObject.find(targetFieldName);
    if(fieldIterator != jsonObject.end()) {
        if(fieldIterator->is_number()) {
            result = true;
        }
    }
    return result;
}

std::string Book::getAuthorInfo() const { return this->authorInfo_;}

std::string Book::getBookTitle() const { return this->bookTitle_; }

std::string Book::getYearAndPublisher() const { return this->yearAndPublisher_; }

int Book::getNumberOfCopies() const { return this->numberOfCopies_; }

void Book::setAuthorInfo(const std::string &newAuthorInfo) {
    if(newAuthorInfo.empty())
        throw std::invalid_argument("Gotten string is empty and can not be set as new author information of this book.");
    this->authorInfo_ = newAuthorInfo;
}

void Book::setBookTitle(const std::string &newBookTitle) {
    if(newBookTitle.empty())
        throw std::invalid_argument("Gotten string is empty and can not be set as new title of this book.");
    this->bookTitle_ = newBookTitle;
}

void Book::setYearAndPublisher(const std::string &newYearAndPublisher) {
    if(newYearAndPublisher.empty())
        throw std::invalid_argument("Gotten string is empty and can not be set as new year and"
                                    "publisher of this book.");
    this->yearAndPublisher_ = newYearAndPublisher;
}

void Book::setNumberOfCopies(int newNumberOfCopies) {
    if(newNumberOfCopies < 1)
        throw std::invalid_argument("Gotten number of copies is less than zero and"
                                    " can not be set as new number of copies of this book.");
    this->numberOfCopies_ = newNumberOfCopies;
}

void Book::loadFromJSON(const json &jsonObject) {
    if(jsonObject.empty())
        throw std::invalid_argument("Gotten JSON object can not be read, it is empty");
    if(!isStringFieldValid(jsonObject, AUTHOR_INFO))
        throw std::invalid_argument("Gotten JSON object does not collects author information, or field wrong typed");
    if(!isStringFieldValid(jsonObject, BOOK_TITLE))
        throw std::invalid_argument("Gotten JSON object does not collects book title, or field wrong typed");
    if(!isStringFieldValid(jsonObject, YEAR_AND_PUBLISHER))
        throw std::invalid_argument("Gotten JSON object does not collects year and"
                                    "publisher, or field wrong typed");
    if(!isNumberFieldValid(jsonObject, NUMBER_OF_COPIES))
        throw std::invalid_argument("Gotten JSON object does not collects number of copies, or field wrong typed");
    auto stateBeforeLoading = *this;
    try {
        this->setAuthorInfo(jsonObject[AUTHOR_INFO].get<std::string>());
        this->setBookTitle(jsonObject[BOOK_TITLE].get<std::string>());
        this->setYearAndPublisher(jsonObject[YEAR_AND_PUBLISHER].get<std::string>());
        this->setNumberOfCopies(jsonObject[NUMBER_OF_COPIES].get<int>());
    } catch (...) {
        *this = stateBeforeLoading;
        throw;
    }
}

json Book::beSaved() const {
    json saveObject;
    saveObject[AUTHOR_INFO] = this->authorInfo_;
    saveObject[BOOK_TITLE] = this->bookTitle_;
    saveObject[YEAR_AND_PUBLISHER] = this->yearAndPublisher_;
    saveObject[NUMBER_OF_COPIES] = this->numberOfCopies_;
    return saveObject;
}

