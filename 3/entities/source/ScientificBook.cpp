//
// Created by vanish2 on 19.01.24.
//

#include "ScientificBook.h"

bool ScientificBook::isArrayFieldValid(const json &jsonObject, const std::string &targetFieldName) {
    bool result;
    auto fieldIterator = jsonObject.find(targetFieldName);
    if(fieldIterator != jsonObject.end()) {
        if(fieldIterator->is_array()) {
            result = true;
        }
    }
    return result;
}

std::vector<std::string> ScientificBook::getCourseNames() const { return this->courseNames_; }

void ScientificBook::setCourseNames(const std::vector<std::string> &newCourseNames) {
    if(newCourseNames.empty())
        throw std::invalid_argument("Gotten array data can not be set as new course names of scientific book, "
                                    "has not any data inside.");
    if(this->courseNames_.size() > MAX_NUMBER_OF_COURSES)
        throw std::invalid_argument("Gotten array data can not be set as new course names of educational book, "
                                    "has not any data inside.");
    this->courseNames_ = newCourseNames;
}

void ScientificBook::addCourseName(const std::string &newCourseName) {
    if(newCourseName.empty())
        throw std::invalid_argument("Gotten string data can not be added as new course name of educational book, "
                                    "has not any data inside.");
    if(this->courseNames_.size() == MAX_NUMBER_OF_COURSES)
        throw std::invalid_argument("Gotten string data can not be added as new course name of educational book, "
                                    "maximum number of course names has been already reached.");
    auto courseNameIterator = std::find(this->courseNames_.begin(), this->courseNames_.end(), newCourseName);
    if (courseNameIterator != this->courseNames_.end())
        throw std::invalid_argument("Course names collects gotten string data, has not any opportunity for adding.");
    this->courseNames_.push_back(newCourseName);
}

void ScientificBook::removeCourseName(const std::string &targetCourseName) {
    if (targetCourseName.empty())
        throw std::invalid_argument("Gotten string data can not be used for removing course name of educational book, "
                                    "has not any data inside.");
    if(this->courseNames_.empty())
        throw std::invalid_argument("Local array of course names has ont any data inside, have not any opportunity"
                                    "for deleting.");
    auto courseNameIterator = std::find(this->courseNames_.begin(), this->courseNames_.end(), targetCourseName);
    if (courseNameIterator == this->courseNames_.end())
        throw std::invalid_argument("Gotten string data does not collects in course name of educational book, "
                                    "has not any opportunity for removing.");
    this->courseNames_.erase(courseNameIterator);
}

void ScientificBook::changeCourseNames(const std::string &oldCourseName, const std::string &newCourseName) {
    if(oldCourseName.empty())
        throw std::invalid_argument("Gotten old course name can not be used for replacing, has not any data inside.");
    if(newCourseName.empty())
        throw std::invalid_argument("Gotten new course name can not be used for replacing, has not any data inside.");
    auto courseNameIterator = std::find(this->courseNames_.begin(), this->courseNames_.end(), oldCourseName);
    if (courseNameIterator == this->courseNames_.end())
        throw std::invalid_argument("Gotten old course name does not collects in course name of educational book, "
                                    "has not any opportunity for replacing.");
    std::replace(courseNameIterator, courseNameIterator + 1, oldCourseName, newCourseName);
}

void ScientificBook::loadFromJSON(const json &jsonObject) {
    auto stateBeforeLoading = *this;
    try {
        Book::loadFromJSON(jsonObject);
        if(!isArrayFieldValid(jsonObject, COURSE_NAMES))
            throw std::invalid_argument("Gotten JSON object does not collects course names, or it is wrong typed.");
        this->setCourseNames(jsonObject[COURSE_NAMES].get<std::vector<std::string>>());
    } catch (...) {
        *this = stateBeforeLoading;
        throw ;
    }
}

json ScientificBook::beSaved() const {
    json saveObject = Book::beSaved();
    saveObject[COURSE_NAMES] = this->courseNames_;
    return saveObject;
}


