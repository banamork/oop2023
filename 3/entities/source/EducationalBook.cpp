//
// Created by vanish2 on 19.01.24.
//

#include "EducationalBook.h"

bool EducationalBook::isArrayFieldValid(const json &jsonObject, const std::string &targetFieldName) {
    bool result;
    auto fieldIterator = jsonObject.find(targetFieldName);
    if(fieldIterator != jsonObject.end()) {
        if(fieldIterator->is_array()) {
            result = true;
        }
    }
    return result;
}

std::string EducationalBook::getCourseName() const { return this->courseName_; }

void EducationalBook::setCourseName(const std::string &newCourseName) {
    if(newCourseName.empty())
        throw std::invalid_argument("Gotten string data can not be set as new course name of educational book,"
                                    "has not any data inside");
    this->courseName_ = newCourseName;
}


std::vector<int> EducationalBook::getGroupIndexes() const { return this->groupIndexes_; }

void EducationalBook::setGroupIndexes(const std::vector<int>& newGroupIndexes) {
    if(newGroupIndexes.empty())
        throw std::invalid_argument("Gotten array data can not be set as new group indexes of educational book,"
                                    "has not any data inside");
    if(newGroupIndexes.size() > MAX_NUMBER_OF_GROUP_INDEXES)
        throw std::invalid_argument("Gotten array data can not be set as new group indexes of educational book,"
                                    "has not any data inside.");
    this->groupIndexes_ = newGroupIndexes;
}

void EducationalBook::loadFromJSON(const json &jsonObject) {
    auto stateBeforeLoading = *this;
    try {
        Book::loadFromJSON(jsonObject);
        if(!isStringFieldValid(jsonObject, COURSE_NAME))
            throw std::invalid_argument("Gotten JSON object does not collects course name, or it is wrong typed.");
        if(!isArrayFieldValid(jsonObject, GROUP_INDEXES))
            throw std::invalid_argument("Gotten JSON object does not collects group indexes, or it is wrong typed.");
        this->setCourseName(jsonObject[COURSE_NAME].get<std::string>());
        this->setGroupIndexes(jsonObject[GROUP_INDEXES].get<std::vector<int>>());
    } catch (...) {
        *this = stateBeforeLoading;
        throw ;
    }
}

json EducationalBook::beSaved() const {
    json saveObject = Book::beSaved();
    saveObject[COURSE_NAME] = this->courseName_;
    saveObject[GROUP_INDEXES] = this->groupIndexes_;
    return saveObject;
}

